# MEMGUARD: Memory Security in RISC-V Systems

Projeto Integrador em Engenharia Eletrónica Industrial e Computadores (PI3), University of Minho, Master's in Industrial Electronics and Computer Engineering, Braga, June 2026.

Authors: João Mendes, Tiago Oliveira. Advisors: Luís Cunha, Manuel Rodriguez, Tiago Gomes.

Full report: docs/MEMGUARD_Relatorio.pdf. Proposal: docs/MEMGUARD_Proposta.pdf.

## What the project is

On microcontrollers (MCUs) there is no MMU, so there is no virtual memory or address translation. All physical memory is shared by every task: in practice, any task can read or write to the memory of another task or of the kernel itself. In a real application this is a safety risk (a bug in one task corrupts another) and a security risk (a malicious task accesses data that does not belong to it).

The RISC-V architecture offers two tools to address this:

Privilege levels (M-Mode, S-Mode, U-Mode): the kernel runs in M-Mode with full access; tasks should run in U-Mode, with no access to privileged instructions.
PMP (Physical Memory Protection): privileged software defines physical memory regions with per-task R/W/X permissions. An access outside the region triggers an access fault that is routed to the kernel.

The central point of this project is that having the hardware is not enough: what matters is how the RTOS uses these mechanisms. To prove this, the same set of attacks was implemented on two RTOS, running on the same core (the RISC-V CVA6 in the RV32IMAC variant with Sv32 MMU and 16 PMP entries):

| | FreeRTOS (base configuration) | Zephyr |
|---|---|---|
| Kernel mode | M-Mode | M-Mode |
| Task mode | M-Mode | U-Mode |
| PMP on context switch | Does not reconfigure | Reconfigures per task |
| Isolation between tasks | None | Per physical region |
| Response to a violation | Silent (corrupts and continues) | Store Access Fault, system halted |

The practical conclusion: on base FreeRTOS the attacks go through undetected; on Zephyr the PMP intercepts each one before any damage occurs. Validation was carried out in simulation (Verilator) and on real hardware (Genesys2 FPGA), including a physical demonstration in which the target is the speed of a DC motor driven by PWM.

## Main contributions

Adversarial demos in Zephyr and FreeRTOS. A mirrored set of tasks: the same attack is implemented on both RTOS to isolate the effect of the PMP. See zephyr_apps/ and FreeRTOS/demos_seguranca/.

Extension of FreeRTOS to U-Mode. The original RISC-V port runs everything in M-Mode. It was modified to launch tasks in U-Mode (MPP=00 in mstatus, a full-access PMP entry before the first mret, and handling of the U-Mode ecall, mcause=8, in the exception handler). Shows that separating privileges without configuring the PMP is not enough: the address space remains fully accessible.

Fix for a bug in CVA6's RTL. See the section below.

## The attack scenarios

Each scenario is implemented equivalently on both RTOS, changing only the presence or absence of PMP isolation. This allows the effect of the configuration to be seen side by side.

| # | Scenario | Target | FreeRTOS (no PMP) | Zephyr (with PMP) |
|---|---|---|---|---|
| 1 | Writing to another task's stack | private stack | Write accepted, password corrupted undetected | Store Access Fault, system halted |
| 2 | Writing to a kernel global variable | kernel space | Data corrupted undetected | Store Access Fault, system halted |
| 3 | TCB corruption (stack pointer) | task control structure | Scheduler uses an invalid SP, system fails | Store Access Fault, system halted |
| 4 | Accidental bug (array overflow) | another task's memory | Silent overflow corrupts another task | Store Access Fault, bug contained within the task |

Scenario 4 matters because PMP isolation is independent of intent: it protects against both an attack and a simple programming error, the most common class of failure in embedded C.

## Fix to CVA6's RTL (Load Store Unit)

During validation, a vulnerability was found in the core itself. Illegal stores were reported as Load Access Fault (mcause=0x5) instead of Store Access Fault (mcause=0x7), and mtval ended up with the wrong address. The serious case: an sw to a read-and-execute-only region (R|X, for example the kernel's .text) was authorized and executed, silently corrupting privileged code.

Cause: a timing desynchronization in cva6/core/load_store_unit.sv. With the MMU present, the signals lsu_valid_i, lsu_paddr_i, and lsu_exception_i reach pmp_data_if already registered (one cycle of delay), but lsu_is_store_i and lsu_vaddr_i were connected to the combinational signals st_translation_req and mmu_vaddr, which had already changed state in the cycle where the PMP evaluates the access. Result: the PMP saw is_store=0 and treated the write as a read.

Fix (in cva6/core/load_store_unit.sv): register st_translation_req and mmu_vaddr (into the pmp_is_store and pmp_vaddr signals) in sync with the rest, and connect pmp_data_if to the new registered signals. After this, all write violations correctly generate mcause=0x7 with the correct mtval, and stores to R|X regions are properly blocked, as required by the RISC-V specification. Full detail in Chapter 5.2 of the report.

## Repository structure

```
PI3/
├── README.md                     (this file)
├── docs/
│   ├── MEMGUARD_Relatorio.pdf     (final report, 29 pages)
│   └── MEMGUARD_Proposta.pdf      (original project proposal)
│
├── zephyr_apps/                   CONTRIBUTION: Zephyr applications (U-Mode + PMP)
│   ├── README.md
│   ├── two_tasks/                 base example: 2 tasks in U-Mode
│   └── demos_seguranca/           attack demos + tests for the RTL bug
│
├── FreeRTOS/
│   ├── demos_seguranca/           CONTRIBUTION: M-Mode attack demos
│   │   └── README.md
│   └── FreeRTOS/                  upstream FreeRTOS (uses the RISC-V_cva6 port)
│
├── cva6/                          upstream CVA6 + fix in core/load_store_unit.sv
└── zephyrproject/                 upstream Zephyr + SDK (see .gitignore)
```

The cva6/, zephyrproject/, and FreeRTOS/FreeRTOS/ folders are, for the most part, upstream code (OpenHW Group, Zephyr Project, FreeRTOS). This project's own work is in zephyr_apps/, FreeRTOS/demos_seguranca/, and the targeted fix to cva6/core/load_store_unit.sv.

## How to build and run

Two complementary environments (detail in Section 5.1 of the report):

### Simulation (Verilator)

CVA6's RTL is converted by Verilator into a cycle-accurate C++ model. The FreeRTOS and Zephyr binaries run directly on top of that model. Gives fast iterations and full visibility into internal signals, which was decisive for diagnosing the PMP bug.

### Hardware (Genesys2 FPGA, Xilinx Kintex-7)

CVA6's bitstream is generated with Vivado and loaded onto the FPGA. The ELF is loaded and debugged over JTAG with OpenOCD and GDB. Output is read via UART. The physical demo uses a GPIO pin generating PWM, an L298N H-bridge driver, and a DC motor.

### Choosing a demo

Zephyr: see zephyr_apps/README.md. The demo is chosen in the target_sources of CMakeLists.txt.
FreeRTOS: see FreeRTOS/demos_seguranca/README.md. Each demo replaces the main_blinky.c of the RISC-V_cva6 port.

## Future work

Per-task PMP isolation in FreeRTOS, reconfiguring the entries at each context switch, similarly to Zephyr.
Full U-Mode support in FreeRTOS, with system calls mediating access to CSRs, so that primitives such as vTaskDelay work from tasks running in U-Mode.
Fault tolerance in Zephyr, terminating only the offending task instead of halting the entire system.

## Main references

RISC-V International, The RISC-V Instruction Set Manual, Vol. II: Privileged Architecture (2024)
OpenHW Group, CVA6
FreeRTOS, Zephyr Project
Verilator, OpenOCD, Genesys 2

Full bibliography in the report.

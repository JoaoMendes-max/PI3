Zephyr Applications: isolated by U-Mode + PMP

Zephyr applications for CVA6 (RV32IMAC, Sv32) that demonstrate native isolation on Zephyr with RISC-V. The demos show memory-safety tasks for Zephyr under RISC-V, using U-Mode + PMP (flag `K_USER`), and provide an example of a user-space application that uses an isolated stack. The Store Access Fault mechanism is used to show illegal accesses.

These demos are intended to complement the FreeRTOS demos. See `../FreeRTOS/demos_seguranca/` for the FreeRTOS versions.

Getting started

- The zephyr_apps directory includes `two_tasks/` (example base: two tasks in U-Mode that attempt privileged operations) and `demos_seguranca/` with security-related demos and tests.
- To compile Zephyr demos you may need a basic `CMakeLists.txt` and toolchain setup for the CVA6/Cores that you use. The repo includes example build instructions and references to how to integrate these demos with a local bare-metal boot environment or an emulator.

How to construct and run an app

- There is guidance for creating a Zephyr project and linking in the Store Access Fault handler to demonstrate illegal memory access traps (configured via PMP or kernel configuration).
- Many demos require board-specific configuration (`board_name`) and a basic UART/console configuration for observing output.

Notes and configuration warnings

- Some settings in `prj.conf` and `K_USER`/PMP configuration are required for proper isolation; ensure PMP regions are set up per-task and that the kernel is kept outside user-accessible ranges.
- Examples show how to enable Store Access Fault and configure the system to reboot or halt upon faults — check the demo notes for each example.

Tests and developer notes

- The repository includes simple test programs that reproduce RTM/Store Access Fault behaviors and confirm the platform configuration results (basic tests for illegal accesses, PMP-triggered faults, etc.).
- Follow the README inside each demo directory for build and run instructions per-target board/emulator.

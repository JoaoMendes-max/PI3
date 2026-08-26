# MEMGUARD: Memory Security in RISC-V Systems

Integrative Project in Industrial Electronic Engineering and Computers (PI3)
University of Minho, Master in Industrial Electronic Engineering and Computers, Braga, June 2026.

Authors: João Mendes, Tiago Oliveira
Supervisors: Luís Cunha, Manuel Rodrigues, Tiago Gomes

> Full report: `docs/MEMGUARD_Relatorio.pdf`. Proposal: `docs/MEMGUARD_Proposta.pdf`.

---

## What the project is

On microcontrollers (MCUs) there is no MMU, so there is no virtual memory or address translation. All physical memory is shared by software. This makes it easy for tasks to access memory belonging to other tasks or to the kernel, and security or safety bugs can lead to privilege escalation and memory corruption.

MEMGUARD is a RISC-V memory-security architecture that provides two frameworks to address these issues:

1. Kernel-level primitives (M-Mode, S-Mode, U-Mode): the kernel runs in M-Mode and uses M-Mode features to enforce isolation between the kernel and user tasks.
2. PMP (Physical Memory Protection): hardware feature used to define memory regions and restrict access on the physical memory level, configured to enforce access rules per task.
3. FreeRTOS configuration for U-Mode: the original RISC-V port runs in M-Mode; MEMGUARD provides a configuration and modifications so that tasks run in U-Mode and the kernel remains protected. This includes supporting RV32IMAC with the CMU Sv32 and 16 PMP entries.

| Kernel mode | M-Mode | M-Mode | M-Mode |
| Tasks mode  | M-Mode | U-Mode | U-Mode |
| PMP not *context switch* | No reconfiguration | *Reconfiguration per task* |
| Isolation between *tasks* | None | Yes | For physical memory regions |
| Response to a critical fault | Silence (and continue) | Store Access Fault, system panic | Store Access Fault, system panic |

A short practical note: the FreeRTOS base and Zephyr or PMP interaction is not trivial — some Zephyr or PMP integration may be required depending on the platform and tests.

Conventions and prerequisites:
- The repository contains code and demos for both Zephyr and FreeRTOS, with examples that demonstrate memory-safety attacks and defenses.
- There are build instructions and notes in the docs and in the demos directories.
- See the docs folder for the full report and proposal.

Licenses and references:
- The project uses several open-source components and references (RISC-V International, OpenHW Group, Zephyr Project, FreeRTOS, etc.). Please consult the referenced licenses and upstream projects.

Security demos: FreeRTOS (M-Mode, semi-isolation

Tasks: demonstrations aimed at FreeRTOS, not CVA6 (RV32IMAC, Sv32). These demos focus on configuring the FreeRTOS base so that the kernel is protected while tasks execute in different modes and demonstrate common attacks and protections.

- The demos show configuration examples for the FreeRTOS base and how tasks are executed either in M-Mode or U-Mode, and how PMP and kernel/hardware protections can be used.
- Each demo includes code and instructions to reproduce the scenario and observe the attack or mitigation.

How to run a demo on the board

Each demo contains a short main script (`main_blinky`) that runs tasks used by the demo. For building and running, check the specific demo directory (e.g., FreeRTOS/demos_seguranca/). The demos use a Store Access Fault mechanism to show illegal accesses and kernel protections.

How to integrate a demo into the port

Add your demo to the `main_blinky()` build setup so it can be run as a FreeRTOS demo. For board ports that use a UART for output (for example `gp_my_uart` or `UART_poled_tx_string`) configure the output appropriately.

Structure and primitive descriptions

- FreeRTOS configuration and board-specific patches are included. Some demos are designed to demonstrate: stack/control-flow attacks, stack exposure, global variable corruption, TCB corruption, accidental bugs, motor PWM example, TCB-related motor example, and CSR demo.
- The demos show how to provoke and detect faults (Store Access Fault, PMP violations) and how to observe kernel behavior when tasks attempt illegal memory operations.

Build notes
- Example build lines and main Makefile entries are included in the repo. Follow the demo-specific README sections to build and flash.

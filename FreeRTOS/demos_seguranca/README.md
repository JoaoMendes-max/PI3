# Security demos: FreeRTOS (M-Mode, no isolation)

Adversarial tasks for FreeRTOS on CVA6 (RV32IMAC, Sv32). These demos run on the base FreeRTOS configuration, where the kernel and all tasks execute in M-Mode, with no PMP configured. They are the reference scenario with no protection: every attack succeeds and the corruption is silent, because the hardware neither detects nor blocks anything.

Each demo has an equivalent counterpart in Zephyr (U-Mode + PMP), where the same access triggers a Store Access Fault. See ../../zephyr_apps/demos_seguranca/.

## How to integrate a demo into the port

Each file defines its own main_blinky() with the scenario's tasks. To run a demo, replace the main_blinky.c of the FreeRTOS CVA6 port with the demo's content (or adjust main.c to call the corresponding main_blinky()). The port is located at:

FreeRTOS/FreeRTOS/Demo/ThirdParty/Partner-Supported-Demos/RISC-V_cva6/
The demos use the port's UART (gp_my_uart, UART_polled_tx_string) for all output.

## Available demos

freertos_demo1_controlo_fluxo.c, control-flow hijacking. The Adv Task sets a global flag and directly calls Task A's function. In M-Mode the flag is accessible to any task and the call has no barrier, so Task A ends up executing the Adv's code. Shows that without isolation a task's flow can be hijacked by another. Counterpart: main_z_attack1_hijack.c.

freertos_demo2_stack_expose.c, stack address exposure. Task A prints the address of a password it holds on the stack. There is no attack yet: it just shows that, in M-Mode, having the address visible is enough for that memory to be within reach of any task (the concrete exploit is in demo 3).

freertos_demo3_stack_write.c, writing to another task's stack. A two-phase attack. Task A exposes the password's address in a global (simulating a debug log); the Adv Task reads that address and writes to it, corrupting the password to 0xDEAD. Shows the full exploitation of the leak from demo 2. Counterpart: main_z_attack2_stack.c.

freertos_demo4_global.c, global variable corruption. The Adv Task writes directly to a global variable of Task A. In M-Mode globals are accessible to all tasks, so Task A ends up reading corrupted data with no warning at all. Counterpart: main_z_attack3_global.c.

freertos_demo5_tcb.c, TCB corruption. The Adv Task obtains Task A's handle and writes to the first field of the TCB (the stack pointer). The scheduler ends up operating with an invalid SP and the system enters an undefined state (crash). Shows the highest-damage target: the task's own control structure. Counterpart: main_z_attack4_tcb.c.

freertos_demo6_bug_acidental.c, accidental bug. No malware involved: a task with a local array overflows due to an indexing error and reaches another task's local data. In M-Mode the corruption across stacks goes undetected. Shows that "local" does not mean "protected". Counterpart: main_z_bug_acidental.c.

freertos_demo7_motor_pwm.c, physical demonstration (motor PWM). The Motor Task keeps pwm_duty (speed) on the stack and generates the PWM. When SW0 is pressed, the Adv Task reads the exposed address and corrupts pwm_duty from 70% to 30%. The motor slows down, with no detection at all. Makes the attack visible on a real actuator. Counterpart: demo_fpga_pwm.c.

freertos_demo8_motor_tcb.c, physical demonstration (motor TCB). A variant of the previous one: when SW0 is pressed, the Adv Task corrupts the TCB of the motor task. The scheduler loses control and the motor stops being commanded correctly.

Demo_csr.c, CSR access. A task attempts to read mstatus (csrr instruction). In M-Mode it works; in U-Mode it would trigger an Illegal Instruction (mcause=2). Serves to confirm the privilege difference between the two scenarios.

## Details of the physical demos (DC motor)

Demos 7 and 8 drive a DC motor through a GPIO pin generating PWM, an L298N H-bridge driver, and an external power source. The duty cycle (pwm_duty), defined in software, controls the speed. The attack is triggered by the FPGA's SW0 switch. They make visible, on a real actuator, the impact of a memory violation that FreeRTOS does not detect, unlike Zephyr, which blocks it before any damage occurs.

| Signal | Pin |
|---|---|
| IN1 (motor) | JD1, bit 3 of GPIO channel 1 |
| IN2 (motor) | JD2, bit 4 of GPIO channel 1 |
| SW0 (trigger) | bit 4 of GPIO channel 2 |

AXI GPIO at 0x40000000, PWM period of 10 ms.

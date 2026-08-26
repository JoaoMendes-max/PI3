# Zephyr applications: isolation via U-Mode + PMP

Zephyr applications for CVA6 (RV32IMAC, Sv32) demonstrating Zephyr's native memory isolation on RISC-V. All tasks run in U-Mode (K_USER flag), each with a PMP entry dedicated to its own stack. Any access outside the authorized region triggers a Store Access Fault (mcause=0x7) and the system halts in a controlled way, logging the cause and the address.

These demos are the "with protection" counterpart to FreeRTOS's M-Mode demos: ../FreeRTOS/demos_seguranca/.

## Structure

zephyr_apps/
├── two_tasks/            base example: two U-Mode tasks that print their privilege mode
└── demos_seguranca/      attack demos (mirroring the FreeRTOS ones) + tests for the PMP RTL bug

## How to build and choose the application

Each folder is a self-contained Zephyr project. The demo to compile is chosen in CMakeLists.txt, on the line target_sources(app PRIVATE src/<file>.c). Only one main_* or test_* file is compiled at a time, since each one defines its own threads (via K_THREAD_DEFINE or main()).

```
# with the Zephyr environment active and the CVA6 board configured
west build -b <board_cva6> zephyr_apps/demos_seguranca
```

## Configuration notes (prj.conf)

CONFIG_USERSPACE=y: enables U-Mode and per-task PMP. It is the foundation of all the isolation.
CONFIG_PMP_UNLOCK_ROM_FOR_DEBUG=y: on CVA6, a PMP entry with TOR+Lock blocks reads in M-Mode even with the R bit set. This option removes the ROM lock to allow debugging.
CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC: MTIME in the CVA6 APU runs at the RTC rate, not the CPU clock rate (see two_tasks/prj.conf).

## two_tasks/: base example

Two tasks (task_a, task_b) in U-Mode that, in a loop, print their privilege level by reading the MPP field of mstatus. It is not an attack: it serves as a sanity check to confirm that the tasks start up even in U-Mode and that the base isolation is set up correctly. The files iti.traces and encaps.traces are tracing outputs captured during execution.

## demos_seguranca/: attacks and tests

### Attack demos

Each demo creates a legitimate task (Task A) and an adversary task (Task Adv). In every case, the Adv Task's illegal write is blocked by the PMP and Task A is unaffected.

main_z_attack1_hijack.c, control-flow hijacking. The Adv Task tries to alter a global kernel flag and then call Task A's function as if it were its own, forcing execution of unauthorized code. Shows that the first write (to the flag, which sits in kernel space) already triggers a Store Access Fault, so the hijack never actually happens.

main_z_attack2_stack.c, writing to another task's stack. Task A stores a password on its stack and publishes the address in a shared partition (simulating a debug log left exposed). The Adv Task reads that address and tries to write to it. Shows that a local variable is not protected just by being on the stack: the PMP gives each task an exclusive entry, and the Adv's access triggers a Store Access Fault with the password left intact.

main_z_attack3_global.c, writing to a kernel global variable. The Adv Task writes directly to a global variable of Task A, referenced by symbol (with no need for an exposed address). Shows that kernel global memory is out of reach for a U-Mode task: the write triggers a Store Access Fault.

main_z_attack4_tcb.c, TCB corruption. The Adv Task obtains the reference to Task A's struct k_thread (the control block) and tries to write to the first field (the stack pointer), the highest-damage target since it is the state the scheduler depends on. Shows that even the kernel's internal structures are protected: Store Access Fault before any corruption occurs.

main_z_bug_acidental.c, accidental bug (no malicious intent). A task declares char config[8] but, due to a constant error, loops through 512 iterations writing out of bounds. Shows that isolation also protects against honest programming mistakes: the PMP cuts off the write as soon as it moves past the stack region, containing the bug within that task without affecting Task A.

demo_fpga_pwm.c, physical demonstration with a motor. The Motor Task keeps pwm_duty (speed) on its stack and generates the PWM on a GPIO pin. The Adv Task, when SW0 is pressed, tries to corrupt pwm_duty. Shows the attack made visible on a real actuator: on Zephyr the PMP triggers a Store Access Fault and the legitimate speed value is preserved.

### PMP RTL bug tests

These files were written to diagnose the anomaly described in Section 5.2 of the report (illegal stores being reported as Load Access Fault). They remain documented for their verification value:

test_lw_no_entry.c (Test 1): lw from a region with no PMP entry. Confirmation baseline, should yield mcause=0x5 (Load access fault).
test_sw_no_entry.c (Test 2): sw to a region with no PMP entry. Should yield mcause=0x7 (Store), but yielded 0x5 before the fix, which was the key clue to the bug.
test_sw_has_entry.c (Test 3): sw to .text (PMP entry R|X, no W). Distinguishes the "no match" path from the "match with wrong permission" path; both should yield mcause=0x7.
main_z_test_stores.c: sequence of sw to the same protected address, to force mcause=0x7.
main_z_teste_false_store.c: sw to several forbidden kernel addresses, to confirm that mepc points to the correct instruction.
main_z_test_nop.c: sw with NOPs beforehand, which break the RAW hazard, to distinguish between the scoreboard theory and the hazard theory as the source of the desynchronization.

# Demos de segurança — FreeRTOS (M-Mode, sem isolamento)

Conjunto de *tasks* adversariais para o FreeRTOS sobre o CVA6. Estas demos correm na **configuração
base do FreeRTOS**, em que o kernel **e todas as *tasks* executam em M-Mode, sem PMP configurado**.
Servem de **cenário de referência sem isolamento**: cada ataque é bem-sucedido e a corrupção é
**silenciosa** — o hardware não deteta nem bloqueia nada.

Cada demo tem uma contraparte equivalente em Zephyr (U-Mode + PMP), onde o mesmo acesso gera um
`Store Access Fault`. Ver [`../../zephyr_apps/demos_seguranca/`](../../zephyr_apps/demos_seguranca).

## Como integrar uma demo no port

Cada ficheiro define a sua própria `main_blinky()` com as *tasks* do cenário. Para correr uma demo,
substitui-se o `main_blinky.c` do port CVA6 do FreeRTOS pelo conteúdo da demo (ou ajusta-se o
`main.c` para chamar a `main_blinky()` correspondente):

```
FreeRTOS/FreeRTOS/Demo/ThirdParty/Partner-Supported-Demos/RISC-V_cva6/
```

As demos usam a UART do port (`gp_my_uart` / `UART_polled_tx_string`) para todo o *output*.

## Demos disponíveis

| Ficheiro | Cenário | Resultado em FreeRTOS (M-Mode) | Contraparte Zephyr |
|----------|---------|--------------------------------|--------------------|
| `freertos_demo1_controlo_fluxo.c` | *Hijack* de fluxo: a Adv ativa uma flag global e chama a função da Task A | Ataque bem-sucedido; Task A executa código da Adv | `main_z_attack1_hijack.c` |
| `freertos_demo2_stack_expose.c`   | Exposição do endereço de uma *password* na *stack* | Endereço visível; sem proteção | — |
| `freertos_demo3_stack_write.c`    | Exploração: ler o endereço exposto e escrever na *stack* da Task A | *password* corrompida (`0xDEAD`) sem deteção | `main_z_attack2_stack.c` |
| `freertos_demo4_global.c`         | Corromper variável global da Task A | Dados corrompidos sem deteção | `main_z_attack3_global.c` |
| `freertos_demo5_tcb.c`            | Escrever no 1.º campo do TCB (*stack pointer*) da Task A | *Scheduler* com SP inválido → crash | `main_z_attack4_tcb.c` |
| `freertos_demo6_bug_acidental.c`  | Bug honesto: *overflow* de *array* local atinge dados de outra *task* | *Overflow* silencioso; outra *task* corrompida | `main_z_bug_acidental.c` |
| `freertos_demo7_motor_pwm.c`      | Demo física: a Adv corrompe o `pwm_duty` do motor na *stack* da task (disparada por SW0) | Motor abranda de 70% → 30% sem deteção | `demo_fpga_pwm.c` |
| `freertos_demo8_motor_tcb.c`      | Demo física: a Adv corrompe o TCB da task do motor (SW0) | *Scheduler* perde o controlo do motor | — |
| `Demo_csr.c`                      | *Task* tenta ler `mstatus` (CSR) | Funciona (M-Mode); em U-Mode daria *Illegal Instruction* | — |

## Demos físicas (motor DC)

As demos 7 e 8 controlam um **motor DC** através de um pino GPIO a gerar PWM, um *driver* de ponte H
**L298N** e uma fonte externa. O *duty cycle* (`pwm_duty`), definido em software, determina a
velocidade. O ataque é disparado pelo *switch* **SW0** da FPGA. Tornam visível, num atuador real, o
impacto de uma violação de memória que o FreeRTOS não deteta — ao passo que o Zephyr a bloqueia
antes de qualquer dano.

| Sinal | Pino |
|-------|------|
| `IN1` (motor) | JD1 — bit 3 do canal 1 GPIO |
| `IN2` (motor) | JD2 — bit 4 do canal 1 GPIO |
| `SW0` (trigger) | bit 4 do canal 2 GPIO |

GPIO AXI em `0x40000000`; período de PWM de 10 ms.

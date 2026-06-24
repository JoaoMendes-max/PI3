# Demos de segurança: FreeRTOS (M-Mode, sem isolamento)

*Tasks* adversariais para o FreeRTOS no CVA6 (RV32IMAC, Sv32). Estas demos correm na **configuração base
do FreeRTOS**, em que o kernel **e todas as *tasks* executam em M-Mode, sem PMP configurado**. São o
**cenário de referência sem proteção**: cada ataque é bem-sucedido e a corrupção é **silenciosa**, porque
o hardware não deteta nem bloqueia nada.

Cada demo tem uma contraparte equivalente em Zephyr (U-Mode + PMP), onde o mesmo acesso gera um
`Store Access Fault`. Ver [`../../zephyr_apps/demos_seguranca/`](../../zephyr_apps/demos_seguranca).

## Como integrar uma demo no port

Cada ficheiro define a sua própria `main_blinky()` com as *tasks* do cenário. Para correr uma demo,
substitui-se o `main_blinky.c` do port CVA6 do FreeRTOS pelo conteúdo da demo (ou ajusta-se o `main.c`
para chamar a `main_blinky()` correspondente). O port fica em:

```
FreeRTOS/FreeRTOS/Demo/ThirdParty/Partner-Supported-Demos/RISC-V_cva6/
```

As demos usam a UART do port (`gp_my_uart`, `UART_polled_tx_string`) para todo o *output*.

## Demos disponíveis

- **`freertos_demo1_controlo_fluxo.c`, desvio de fluxo de controlo.**
  A Task Adv ativa uma flag global e chama diretamente a função da Task A. Em M-Mode a flag é acessível
  a qualquer *task* e o `call` não tem barreira, por isso a Task A acaba a executar código da Adv. Mostra
  que sem isolamento o fluxo de uma *task* pode ser desviado por outra.
  Contraparte: `main_z_attack1_hijack.c`.

- **`freertos_demo2_stack_expose.c`, exposição de endereço de *stack*.**
  A Task A imprime o endereço de uma *password* que tem na *stack*. Não há ataque ainda: serve para
  mostrar que, em M-Mode, basta o endereço ficar visível para a memória ficar ao alcance de qualquer
  *task* (a exploração concreta está na demo 3).

- **`freertos_demo3_stack_write.c`, escrita na *stack* de outra *task*.**
  Ataque em duas fases. A Task A expõe o endereço da *password* numa global (a simular um *log* de
  *debug*); a Task Adv lê esse endereço e escreve lá, corrompendo a *password* para `0xDEAD`. Mostra a
  exploração completa do leak da demo 2.
  Contraparte: `main_z_attack2_stack.c`.

- **`freertos_demo4_global.c`, corrupção de variável global.**
  A Task Adv escreve diretamente numa variável global da Task A. Em M-Mode as globais são acessíveis a
  todas as *tasks*, por isso a Task A passa a ler dados corrompidos sem qualquer aviso.
  Contraparte: `main_z_attack3_global.c`.

- **`freertos_demo5_tcb.c`, corrupção do TCB.**
  A Task Adv obtém o *handle* da Task A e escreve no primeiro campo do TCB (o *stack pointer*). O
  *scheduler* passa a operar com um SP inválido e o sistema entra em estado indefinido (crash). Mostra o
  alvo de maior dano: a estrutura de controlo da própria *task*.
  Contraparte: `main_z_attack4_tcb.c`.

- **`freertos_demo6_bug_acidental.c`, bug acidental.**
  Não há malware: uma *task* com um *array* local faz *overflow* por erro de índice e atinge dados locais
  de outra *task*. Em M-Mode a corrupção entre *stacks* passa sem deteção. Mostra que "local" não
  significa "protegido".
  Contraparte: `main_z_bug_acidental.c`.

- **`freertos_demo7_motor_pwm.c`, demonstração física (PWM do motor).**
  A Task Motor guarda o `pwm_duty` (velocidade) na *stack* e gera o PWM. Ao carregar no SW0, a Task Adv
  lê o endereço exposto e corrompe o `pwm_duty` de 70% para 30%. O motor abranda, sem qualquer deteção.
  Torna o ataque visível num atuador real.
  Contraparte: `demo_fpga_pwm.c`.

- **`freertos_demo8_motor_tcb.c`, demonstração física (TCB do motor).**
  Variante da anterior: ao carregar no SW0, a Task Adv corrompe o TCB da *task* do motor. O *scheduler*
  perde o controlo e o motor deixa de ser comandado corretamente.

- **`Demo_csr.c`, acesso a CSR.**
  Uma *task* tenta ler o `mstatus` (instrução `csrr`). Em M-Mode funciona; em U-Mode daria *Illegal
  Instruction* (`mcause=2`). Serve para confirmar a diferença de privilégios entre os dois cenários.

## Detalhes das demos físicas (motor DC)

As demos 7 e 8 comandam um **motor DC** através de um pino GPIO a gerar PWM, um *driver* de ponte H
**L298N** e uma fonte externa. O *duty cycle* (`pwm_duty`), definido em software, controla a velocidade.
O ataque é disparado pelo *switch* **SW0** da FPGA. Tornam visível, num atuador real, o impacto de uma
violação de memória que o FreeRTOS não deteta, ao contrário do Zephyr, que a bloqueia antes do dano.

| Sinal | Pino |
|-------|------|
| `IN1` (motor) | JD1, bit 3 do canal 1 GPIO |
| `IN2` (motor) | JD2, bit 4 do canal 1 GPIO |
| `SW0` (trigger) | bit 4 do canal 2 GPIO |

GPIO AXI em `0x40000000`, período de PWM de 10 ms.

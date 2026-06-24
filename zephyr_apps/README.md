# Aplicações Zephyr: isolamento por U-Mode + PMP

Aplicações Zephyr para o CVA6 (RV32IMAC, Sv32) que demonstram o **isolamento de memória nativo** do
Zephyr em RISC-V. Todas as *tasks* correm em **U-Mode** (flag `K_USER`), cada uma com uma entrada PMP
dedicada à sua *stack*. Qualquer acesso fora da região autorizada gera um **`Store Access Fault`
(`mcause=0x7`)** e o sistema para de forma controlada, registando a causa e o endereço.

Estas demos são a contraparte "com proteção" das demos em M-Mode do FreeRTOS:
[`../FreeRTOS/demos_seguranca/`](../FreeRTOS/demos_seguranca).

## Estrutura

```
zephyr_apps/
├── two_tasks/            exemplo base: duas tasks em U-Mode que imprimem o seu modo de privilégio
└── demos_seguranca/      demos de ataque (espelham as do FreeRTOS) + testes do bug RTL do PMP
```

## Como construir e escolher a aplicação

Cada pasta é um projeto Zephyr autónomo. A demo a compilar é escolhida no `CMakeLists.txt`, na linha
`target_sources(app PRIVATE src/<ficheiro>.c)`. Só **um** ficheiro `main_*` ou `test_*` é compilado de
cada vez, porque cada um define as suas próprias *threads* (via `K_THREAD_DEFINE` ou `main()`).

```bash
# com o ambiente Zephyr ativo e a board CVA6 configurada
west build -b <board_cva6> zephyr_apps/demos_seguranca
```

### Notas de configuração (`prj.conf`)

- `CONFIG_USERSPACE=y`: ativa o U-Mode e o PMP por *task*. É a base de todo o isolamento.
- `CONFIG_PMP_UNLOCK_ROM_FOR_DEBUG=y`: no CVA6, uma entrada PMP com TOR+Lock bloqueia leituras em
  M-Mode mesmo com o bit R ativo. Esta opção remove o *lock* da ROM para permitir depuração.
- `CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC`: o MTIME no APU do CVA6 corre ao ritmo do RTC, não do CPU
  clock (ver `two_tasks/prj.conf`).

---

## `two_tasks/`: exemplo base

Duas *tasks* (`task_a`, `task_b`) em U-Mode que, em ciclo, imprimem o seu nível de privilégio lendo o
campo MPP do `mstatus`. Não é um ataque: serve de *sanity check* para confirmar que as *tasks* arrancam
mesmo em U-Mode e que o isolamento base está montado. Os ficheiros `iti.traces` e `encaps.traces` são
saídas de *tracing* capturadas durante a execução.

---

## `demos_seguranca/`: ataques e testes

### Demos de ataque

Cada demo cria uma *task* legítima (Task A) e uma *task* adversária (Task Adv). Em todos os casos, a
escrita ilegal da Task Adv é bloqueada pelo PMP e a Task A não é afetada.

- **`main_z_attack1_hijack.c`, desvio de fluxo de controlo.**
  A Task Adv tenta alterar uma flag global do kernel e depois chamar a função da Task A como se fosse
  sua, forçando a execução de código não autorizado. Serve para mostrar que a primeira escrita (na flag,
  que está no espaço do kernel) já dispara `Store Access Fault`, pelo que o desvio nunca chega a acontecer.

- **`main_z_attack2_stack.c`, escrita na *stack* de outra *task*.**
  A Task A guarda uma *password* na sua *stack* e publica o endereço numa partição partilhada (a simular
  um registo de *debug* deixado exposto). A Task Adv lê esse endereço e tenta escrever lá. Serve para
  mostrar que uma variável local **não** está protegida só por estar na *stack*: o PMP dá uma entrada
  exclusiva por *task*, e o acesso da Adv gera `Store Access Fault` com a *password* intacta.

- **`main_z_attack3_global.c`, escrita em variável global do kernel.**
  A Task Adv escreve diretamente numa variável global da Task A, referenciada por símbolo (sem precisar
  de endereço exposto). Serve para mostrar que a memória global do kernel está fora do alcance de uma
  *task* em U-Mode: a escrita gera `Store Access Fault`.

- **`main_z_attack4_tcb.c`, corrupção do TCB.**
  A Task Adv obtém a referência para o `struct k_thread` (o bloco de controlo) da Task A e tenta escrever
  no primeiro campo (o *stack pointer*), o alvo de maior dano por ser o estado de que o *scheduler*
  depende. Serve para mostrar que mesmo as estruturas internas do kernel estão protegidas: `Store Access
  Fault` antes de qualquer corrupção.

- **`main_z_bug_acidental.c`, bug acidental (sem intenção maliciosa).**
  Uma *task* declara `char config[8]` mas, por erro de constante, percorre 512 iterações a escrever fora
  dos limites. Serve para mostrar que o isolamento protege também contra erros honestos de programação: o
  PMP corta a escrita assim que ela passa a região da *stack*, contendo o bug nessa *task* sem afetar a
  Task A.

- **`demo_fpga_pwm.c`, demonstração física com motor.**
  A Task Motor mantém o `pwm_duty` (velocidade) na sua *stack* e gera o PWM num pino GPIO. A Task Adv,
  ao carregar no *switch* SW0, tenta corromper o `pwm_duty`. Serve para tornar o ataque visível num
  atuador real: no Zephyr o PMP gera `Store Access Fault` e o valor legítimo da velocidade é preservado.

### Testes do bug RTL do PMP

Estes ficheiros foram escritos para **diagnosticar** a anomalia da Secção 5.2 do relatório (*stores*
ilegais a serem reportados como `Load Access Fault`). Ficam documentados pelo valor de verificação:

- **`test_lw_no_entry.c`** (Teste 1): `lw` de uma região sem entrada PMP. *Baseline* de confirmação,
  deve dar `mcause=0x5` (Load access fault).
- **`test_sw_no_entry.c`** (Teste 2): `sw` para uma região sem entrada PMP. Deve dar `mcause=0x7`
  (Store), mas **dava `0x5` antes da correção**, que foi a pista chave para o bug.
- **`test_sw_has_entry.c`** (Teste 3): `sw` para o `.text` (entrada PMP `R|X`, sem `W`). Distingue o
  caminho "sem *match*" do caminho "*match* com permissão errada"; ambos devem dar `mcause=0x7`.
- **`main_z_test_stores.c`**: sequência de `sw` no mesmo endereço protegido, para forçar `mcause=0x7`.
- **`main_z_teste_false_store.c`**: `sw` para vários endereços proibidos do kernel, para confirmar que o
  `mepc` aponta a instrução certa.
- **`main_z_test_nop.c`**: `sw` com NOPs antes, que quebram o RAW *hazard*, para isolar entre a teoria do
  *scoreboard* e a do *hazard* como origem da dessincronização.

# Aplicações Zephyr — Isolamento por U-Mode + PMP

Aplicações Zephyr para o CVA6 que demonstram o **isolamento de memória nativo** do Zephyr em
RISC-V. Todas as *tasks* correm em **U-Mode** (`K_USER`), cada uma com uma entrada PMP dedicada à
sua *stack*. Qualquer acesso fora da região autorizada gera um **`Store Access Fault` (`mcause=0x7`)** e
o sistema para de forma controlada.

Contraparte em M-Mode (sem isolamento): [`../FreeRTOS/demos_seguranca/`](../FreeRTOS/demos_seguranca).

## Estrutura

```
zephyr_apps/
├── two_tasks/            ← exemplo base: duas tasks em U-Mode que imprimem o seu modo de privilégio
└── demos_seguranca/      ← demos de ataque (espelham as do FreeRTOS) + testes do bug RTL do PMP
```

## Como construir / escolher uma aplicação

Cada aplicação é um projeto Zephyr autónomo. A demo a compilar é escolhida no `CMakeLists.txt`, na
linha `target_sources(app PRIVATE src/<ficheiro>.c)` — só **um** ficheiro `main_*`/`test_*` é compilado
de cada vez (cada um define as suas próprias *threads* via `K_THREAD_DEFINE` ou `main()`).

```bash
# a partir da raiz do zephyrproject, com o ambiente Zephyr ativo
west build -b <board_cva6> path/to/zephyr_apps/demos_seguranca
```

### Notas de configuração (`prj.conf`)

- `CONFIG_USERSPACE=y` — ativa o U-Mode e o PMP por *task* (base de todo o isolamento).
- `CONFIG_PMP_UNLOCK_ROM_FOR_DEBUG=y` — o CVA6 com TOR+Lock bloqueia leituras em M-Mode mesmo
  com o bit R ativo; esta opção remove o *lock* da ROM para permitir depuração.
- `CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC` — o MTIME no APU do CVA6 corre ao ritmo do RTC, não do
  CPU clock (ver `two_tasks/prj.conf`).

---

## `two_tasks/` — exemplo base

Duas *tasks* (`task_a`, `task_b`) em U-Mode que imprimem o seu nível de privilégio lendo o campo MPP
do `mstatus`. Serve de *sanity check* ao arranque em U-Mode. Os ficheiros `iti.traces` e `encaps.traces`
são saídas de *tracing* capturadas durante a execução.

---

## `demos_seguranca/` — ataques e testes

### Demos de ataque (espelham o FreeRTOS)

| Ficheiro | Cenário | Resultado esperado em Zephyr (U-Mode) |
|----------|---------|----------------------------------------|
| `main_z_attack1_hijack.c`   | *Hijack* de fluxo: escrever numa flag global do kernel e chamar a função de outra *task* | `Store Access Fault` na escrita da global |
| `main_z_attack2_stack.c`    | Escrever na *stack* de outra *task* (endereço exposto via partição partilhada) | `Store Access Fault`; *password* da Task A intacta |
| `main_z_attack3_global.c`   | Escrever diretamente numa variável global do kernel | `Store Access Fault` |
| `main_z_attack4_tcb.c`      | Corromper o `k_thread` (TCB) de outra *task* | `Store Access Fault` antes de qualquer corrupção |
| `main_z_bug_acidental.c`    | Bug honesto: `for` itera 512× num `array[8]` | `Store Access Fault`; bug contido, Task A não é afetada |
| `demo_fpga_pwm.c`           | Demo física: Task A controla o PWM de um motor; a Task Adv tenta corromper o `pwm_duty` na *stack* da Task A (disparada por SW0) | `Store Access Fault`; `pwm_duty` legítimo preservado |

A partilha de endereços entre *tasks* (quando o cenário exige coordenação) usa o mecanismo de
**partições** do Zephyr: uma `K_APPMEM_PARTITION_DEFINE(shared_part)` atribuída aos domínios das
duas *tasks*, mantendo privadas as restantes regiões. O padrão usado é **criar as *threads* suspensas
(`K_FOREVER`), configurar o domínio e só depois `k_thread_start`**, garantindo que as entradas PMP
estão prontas antes da primeira instrução em U-Mode.

> Nota: em `shared_part` usam-se dois `uint32_t` (8 bytes) porque é o mínimo NAPOT do RISC-V (2³).
> Com apenas 4 bytes, o PMP NAPOT não cria uma entrada válida.

### Testes do bug RTL do PMP

Estes ficheiros foram usados para **diagnosticar** a anomalia descrita na Secção 5.2 do relatório
(*stores* ilegais reportados como `Load Access Fault`). Documentam-se aqui por valor histórico/de
verificação:

| Ficheiro | O que testa | `mcause` esperado |
|----------|-------------|-------------------|
| `test_lw_no_entry.c`        | `lw` de região sem entrada PMP (*default deny*) — *baseline* | `0x5` (Load) |
| `test_sw_no_entry.c`        | `sw` de região sem entrada PMP | `0x7` (Store) — **dava `0x5` antes da correção** |
| `test_sw_has_entry.c`       | `sw` para `.text` (entrada `R|X`, sem `W`) — *match com permissão errada* | `0x7` (Store) |
| `main_z_test_stores.c`      | sequência de `sw` no mesmo endereço protegido | `0x7` (Store) |
| `main_z_teste_false_store.c`| `sw` para múltiplos endereços proibidos do kernel | `0x7` (Store) |
| `main_z_test_nop.c`         | `sw` com NOPs antes (quebra RAW *hazard*) para isolar a teoria do *scoreboard* | `0x7` (Store) |

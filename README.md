# MEMGUARD — Memory Security in RISC-V Systems

Projeto Integrador em Engenharia Eletrónica Industrial e Computadores (PI3)
Universidade do Minho · Mestrado em Engenharia Eletrónica Industrial e Computadores · Braga, junho de 2026

**Autores:** João Mendes (PG60206) · Luís Cunha · Manuel Rodriguez
**Orientadores:** Tiago Gomes · Tiago Oliveira

> Relatório completo: [`docs/MEMGUARD_Relatorio.pdf`](docs/MEMGUARD_Relatorio.pdf) · Proposta: [`docs/MEMGUARD_Proposta.pdf`](docs/MEMGUARD_Proposta.pdf)

---

## Resumo

Em microcontroladores (MCUs), a ausência de uma MMU faz com que toda a memória física seja
partilhada por todas as *tasks*: qualquer *task* pode ler ou escrever arbitrariamente na memória de
outra *task* ou do próprio kernel. A arquitetura RISC-V oferece dois mecanismos para mitigar isto —
os **níveis de privilégio** (M/S/U) e a primitiva **PMP (Physical Memory Protection)** — mas a sua
eficácia depende de como cada RTOS os utiliza.

Este trabalho compara **experimentalmente** dois RTOS sobre o **mesmo hardware** (o core RISC-V
**CVA6**, variante 32 bits, 16 entradas PMP):

| | **FreeRTOS** (base) | **Zephyr** |
|---|---|---|
| Modo do kernel | M-Mode | M-Mode |
| Modo das *tasks* | M-Mode | **U-Mode** |
| PMP no *context switch* | Não reconfigura | **Reconfigura por *task*** |
| Isolamento entre *tasks* | Nenhum | Por região física |
| Resposta a violação | Silenciosa (corrupção) | **Store Access Fault → halt** |

A validação foi feita em **simulação (Verilator)** e em **hardware real (FPGA Genesys2)**, incluindo
uma demonstração física com um **motor DC** controlado por PWM.

---

## Principais contribuições

1. **Demos adversariais em Zephyr e FreeRTOS** — conjunto espelhado de *tasks* que materializam o
   mesmo ataque nos dois RTOS, isolando o efeito do PMP. Ver [`zephyr_apps/`](zephyr_apps) e
   [`FreeRTOS/demos_seguranca/`](FreeRTOS/demos_seguranca).
2. **Extensão do FreeRTOS para U-Mode** — o port RISC-V original corre tudo em M-Mode; foi
   modificado para lançar *tasks* em U-Mode (MPP=00 no `mstatus`, entrada PMP total antes do
   primeiro `mret`, e tratamento de `ecall` de U-Mode, `mcause=8`, no *handler* de exceções).
   Demonstra que **a separação de privilégios sem PMP é insuficiente** para garantir isolamento.
3. **Correção de uma anomalia no RTL do CVA6** — ver secção abaixo.

---

## Os quatro cenários de ataque

Cada cenário é implementado de forma equivalente nos dois RTOS, diferindo apenas na presença/ausência
de isolamento PMP.

| # | Cenário | Alvo | FreeRTOS (sem PMP) | Zephyr (com PMP) |
|---|---------|------|--------------------|------------------|
| 1 | Escrita na *stack* de outra *task* | *stack* privada | Escrita bem-sucedida; *password* corrompida sem deteção | `Store Access Fault` (mcause=0x7); sistema parado |
| 2 | Escrita em variável global do kernel | espaço do kernel | Dados corrompidos sem deteção | `Store Access Fault`; sistema parado |
| 3 | Corrupção do TCB (*stack pointer*) | estrutura de controlo | *Scheduler* opera com SP inválido; sistema falha | `Store Access Fault`; sistema parado |
| 4 | Bug acidental (*array overflow*) | memória de outra *task* | *Overflow* silencioso corrompe outra *task* | `Store Access Fault`; bug contido na *task* |

O cenário 4 mostra que **o isolamento PMP é independente da intenção**: protege tanto contra ataques
como contra erros de programação (classe de falhas frequente em C embebido).

---

## Correção ao RTL do CVA6 (Load Store Unit)

Durante a validação foi identificada uma **vulnerabilidade no próprio core**: *stores* ilegais eram
classificados como `Load Access Fault` (`mcause=0x5`) em vez de `Store Access Fault` (`mcause=0x7`), e
o `mtval` continha um endereço errado. Pior: um `sw` para uma região só de leitura/execução (`R|X`,
ex.: o `.text` do kernel) era **erroneamente autorizado e executado**, corrompendo código privilegiado
de forma silenciosa.

**Causa:** dessincronização temporal em `cva6/core/load_store_unit.sv`. Com a MMU presente, os
sinais `lsu_valid_i`, `lsu_paddr_i` e `lsu_exception_i` chegam ao `pmp_data_if` registados (1 ciclo de
atraso), mas `lsu_is_store_i` e `lsu_vaddr_i` estavam ligados diretamente aos sinais combinacionais
`st_translation_req` e `mmu_vaddr`, já alterados no ciclo em que o PMP avalia o acesso.

**Correção** (em [`cva6/core/load_store_unit.sv`](cva6/core/load_store_unit.sv)): registar
`st_translation_req` e `mmu_vaddr` (sinais `pmp_is_store` / `pmp_vaddr`) em sincronia com os
restantes, e ligar o `pmp_data_if` aos novos sinais registados. Após a correção, todas as violações por
escrita passam a gerar `mcause=0x7` com `mtval` correto, e os *stores* para regiões `R|X` são
bloqueados, conforme a especificação RISC-V. Detalhe completo no Capítulo 5.2 do relatório.

---

## Estrutura do repositório

```
PI3/
├── README.md                     ← este ficheiro
├── docs/
│   ├── MEMGUARD_Relatorio.pdf     ← relatório final (29 pág.)
│   └── MEMGUARD_Proposta.pdf      ← proposta original do projeto
│
├── zephyr_apps/                   ← CONTRIBUIÇÃO: aplicações Zephyr (U-Mode + PMP)
│   ├── README.md
│   ├── two_tasks/                 ← exemplo base: 2 tasks em U-Mode
│   └── demos_seguranca/           ← demos de ataque + testes do bug RTL
│
├── FreeRTOS/
│   ├── demos_seguranca/           ← CONTRIBUIÇÃO: demos de ataque em M-Mode
│   │   └── README.md
│   └── FreeRTOS/                  ← upstream FreeRTOS (port RISC-V_cva6 usado)
│
├── cva6/                          ← upstream CVA6 + correção em core/load_store_unit.sv
└── zephyrproject/                 ← upstream Zephyr + SDK (ver .gitignore)
```

As pastas `cva6/`, `zephyrproject/` e `FreeRTOS/FreeRTOS/` são, na sua maioria, código *upstream*
(OpenHW Group, Zephyr Project, FreeRTOS). O trabalho próprio deste projeto está em **`zephyr_apps/`**,
**`FreeRTOS/demos_seguranca/`** e na **correção pontual** ao `cva6/core/load_store_unit.sv`.

---

## Como compilar e correr

Dois ambientes complementares (detalhe na Secção 5.1 do relatório):

### Simulação (Verilator)
O RTL do CVA6 é convertido pelo Verilator num modelo *cycle-accurate* em C++; os binários do
FreeRTOS / Zephyr correm diretamente sobre esse modelo. Permite iterações rápidas e visibilidade total
dos sinais internos — foi o que permitiu diagnosticar o bug do PMP.

### Hardware (FPGA Genesys2, Xilinx Kintex-7)
O *bitstream* do CVA6 é gerado com o Vivado e carregado na FPGA. O ELF é carregado e depurado via
JTAG com OpenOCD + GDB; o *output* é observado por UART. A demo física usa um pino GPIO a gerar
PWM, um *driver* de ponte H **L298N** e um **motor DC**.

### Selecionar uma demo
- **Zephyr:** ver [`zephyr_apps/README.md`](zephyr_apps/README.md) (escolhe-se o ficheiro em `target_sources` do `CMakeLists.txt`).
- **FreeRTOS:** ver [`FreeRTOS/demos_seguranca/README.md`](FreeRTOS/demos_seguranca/README.md) (cada demo substitui o `main_blinky.c` do port `RISC-V_cva6`).

---

## Trabalho futuro

1. **Isolamento PMP por *task* no FreeRTOS** — reconfigurar as entradas PMP a cada *context switch*, à
   semelhança do Zephyr.
2. **Suporte integral a U-Mode no FreeRTOS** — *system calls* para mediar o acesso a CSRs, permitindo
   que primitivas como `vTaskDelay` funcionem a partir de *tasks* em U-Mode.
3. **Tolerância a falhas no Zephyr** — terminar apenas a *task* ofensora em vez de parar todo o sistema.

---

## Referências principais

- RISC-V International — *The RISC-V Instruction Set Manual, Vol. II: Privileged Architecture* (2024)
- OpenHW Group — [CVA6](https://github.com/openhwgroup/cva6)
- [FreeRTOS](https://www.freertos.org) · [Zephyr Project](https://github.com/zephyrproject-rtos/zephyr)
- [Verilator](https://www.veripool.org/verilator/) · [OpenOCD](https://openocd.org) · [Genesys 2](https://digilent.com/reference/programmable-logic/genesys-2/start)

Bibliografia completa no relatório.

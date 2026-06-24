# MEMGUARD: Memory Security in RISC-V Systems

Projeto Integrador em Engenharia Eletrónica Industrial e Computadores (PI3)
Universidade do Minho, Mestrado em Engenharia Eletrónica Industrial e Computadores, Braga, junho de 2026.

**Autores:** João Mendes (PG60206), Luís Cunha, Manuel Rodriguez
**Orientadores:** Tiago Gomes, Tiago Oliveira

> Relatório completo: [`docs/MEMGUARD_Relatorio.pdf`](docs/MEMGUARD_Relatorio.pdf). Proposta: [`docs/MEMGUARD_Proposta.pdf`](docs/MEMGUARD_Proposta.pdf).

---

## O que é o projeto

Em microcontroladores (MCUs) não existe MMU, por isso não há memória virtual nem tradução de
endereços. Toda a memória física é partilhada por todas as *tasks*: na prática, qualquer *task* consegue
ler ou escrever na memória de outra *task* ou do próprio kernel. Numa aplicação real isto é um risco de
*safety* (um bug numa *task* corrompe outra) e de *security* (uma *task* maliciosa acede a dados que não
lhe pertencem).

A arquitetura RISC-V oferece duas ferramentas para resolver isto:

1. **Níveis de privilégio** (M-Mode, S-Mode, U-Mode): o kernel corre em M-Mode com acesso total; as
   *tasks* deviam correr em U-Mode, sem acesso a instruções privilegiadas.
2. **PMP (Physical Memory Protection)**: o software privilegiado define regiões de memória física com
   permissões R/W/X por *task*. Um acesso fora da região gera um *access fault* que é encaminhado para
   o kernel.

O ponto central deste projeto é que **ter o hardware não chega: o que decide é como o RTOS usa estes
mecanismos.** Para o provar, o mesmo conjunto de ataques foi implementado em dois RTOS, a correr no
**mesmo core** (o RISC-V **CVA6** na variante **RV32IMAC com MMU Sv32 e 16 entradas PMP**):

| | **FreeRTOS** (configuração base) | **Zephyr** |
|---|---|---|
| Modo do kernel | M-Mode | M-Mode |
| Modo das *tasks* | M-Mode | **U-Mode** |
| PMP no *context switch* | Não reconfigura | **Reconfigura por *task*** |
| Isolamento entre *tasks* | Nenhum | Por região física |
| Resposta a uma violação | Silenciosa (corrompe e continua) | **`Store Access Fault`, sistema parado** |

A conclusão prática: no FreeRTOS base os ataques passam sem deteção; no Zephyr o PMP intercepta cada
um antes de causar dano. A validação foi feita em **simulação (Verilator)** e em **hardware real (FPGA
Genesys2)**, incluindo uma demonstração física em que o alvo é a velocidade de um **motor DC** comandado
por PWM.

---

## Contribuições principais

1. **Demos adversariais em Zephyr e FreeRTOS.** Um conjunto espelhado de *tasks*: o mesmo ataque é
   implementado nos dois RTOS para isolar o efeito do PMP. Ver [`zephyr_apps/`](zephyr_apps) e
   [`FreeRTOS/demos_seguranca/`](FreeRTOS/demos_seguranca).
2. **Extensão do FreeRTOS para U-Mode.** O port RISC-V original corre tudo em M-Mode. Foi modificado
   para lançar *tasks* em U-Mode (MPP=00 no `mstatus`, uma entrada PMP de acesso total antes do
   primeiro `mret`, e tratamento do `ecall` de U-Mode, `mcause=8`, no *handler* de exceções). Serve para
   mostrar que **separar privilégios sem configurar o PMP não chega**: o espaço de endereçamento continua
   todo acessível.
3. **Correção de um bug no RTL do CVA6.** Ver a secção abaixo.

---

## Os cenários de ataque

Cada cenário é implementado de forma equivalente nos dois RTOS, mudando só a presença ou ausência de
isolamento PMP. Assim vê-se lado a lado o efeito da configuração.

| # | Cenário | Alvo | FreeRTOS (sem PMP) | Zephyr (com PMP) |
|---|---------|------|--------------------|------------------|
| 1 | Escrita na *stack* de outra *task* | *stack* privada | Escrita aceite, *password* corrompida sem deteção | `Store Access Fault`, sistema parado |
| 2 | Escrita em variável global do kernel | espaço do kernel | Dados corrompidos sem deteção | `Store Access Fault`, sistema parado |
| 3 | Corrupção do TCB (*stack pointer*) | estrutura de controlo da *task* | *Scheduler* usa um SP inválido, sistema falha | `Store Access Fault`, sistema parado |
| 4 | Bug acidental (*overflow* de *array*) | memória de outra *task* | *Overflow* silencioso corrompe outra *task* | `Store Access Fault`, bug contido na *task* |

O cenário 4 é importante porque **o isolamento do PMP é independente da intenção**: protege tanto contra
um ataque como contra um simples erro de programação, a classe de falhas mais comum em C embebido.

---

## Correção ao RTL do CVA6 (Load Store Unit)

Durante a validação foi encontrada uma vulnerabilidade no próprio core. *Stores* ilegais eram reportados
como `Load Access Fault` (`mcause=0x5`) em vez de `Store Access Fault` (`mcause=0x7`), e o `mtval` ficava
com um endereço errado. O caso grave: um `sw` para uma região só de leitura e execução (`R|X`, por
exemplo o `.text` do kernel) era **autorizado e executado**, corrompendo código privilegiado em silêncio.

**Causa:** uma dessincronização temporal em `cva6/core/load_store_unit.sv`. Com a MMU presente, os
sinais `lsu_valid_i`, `lsu_paddr_i` e `lsu_exception_i` chegam ao `pmp_data_if` já registados (um ciclo de
atraso), mas `lsu_is_store_i` e `lsu_vaddr_i` estavam ligados aos sinais combinacionais
`st_translation_req` e `mmu_vaddr`, que já tinham mudado de estado no ciclo em que o PMP avalia o
acesso. Resultado: o PMP via `is_store=0` e tratava a escrita como leitura.

**Correção** (em [`cva6/core/load_store_unit.sv`](cva6/core/load_store_unit.sv)): registar
`st_translation_req` e `mmu_vaddr` (nos sinais `pmp_is_store` e `pmp_vaddr`) em sincronia com os
restantes, e ligar o `pmp_data_if` aos novos sinais registados. Depois disto, todas as violações por
escrita passam a gerar `mcause=0x7` com `mtval` correto, e os *stores* para regiões `R|X` passam a ser
bloqueados, conforme a especificação RISC-V. Detalhe completo no Capítulo 5.2 do relatório.

---

## Estrutura do repositório

```
PI3/
├── README.md                     (este ficheiro)
├── docs/
│   ├── MEMGUARD_Relatorio.pdf     (relatório final, 29 páginas)
│   └── MEMGUARD_Proposta.pdf      (proposta original do projeto)
│
├── zephyr_apps/                   CONTRIBUIÇÃO: aplicações Zephyr (U-Mode + PMP)
│   ├── README.md
│   ├── two_tasks/                 exemplo base: 2 tasks em U-Mode
│   └── demos_seguranca/           demos de ataque + testes do bug RTL
│
├── FreeRTOS/
│   ├── demos_seguranca/           CONTRIBUIÇÃO: demos de ataque em M-Mode
│   │   └── README.md
│   └── FreeRTOS/                  upstream FreeRTOS (usa-se o port RISC-V_cva6)
│
├── cva6/                          upstream CVA6 + correção em core/load_store_unit.sv
└── zephyrproject/                 upstream Zephyr + SDK (ver .gitignore)
```

As pastas `cva6/`, `zephyrproject/` e `FreeRTOS/FreeRTOS/` são, na maioria, código *upstream* (OpenHW
Group, Zephyr Project, FreeRTOS). O trabalho próprio deste projeto está em **`zephyr_apps/`**,
**`FreeRTOS/demos_seguranca/`** e na **correção pontual** ao `cva6/core/load_store_unit.sv`.

---

## Como compilar e correr

Dois ambientes complementares (detalhe na Secção 5.1 do relatório):

### Simulação (Verilator)
O RTL do CVA6 é convertido pelo Verilator num modelo *cycle-accurate* em C++. Os binários do FreeRTOS
e do Zephyr correm diretamente sobre esse modelo. Dá iterações rápidas e visibilidade total dos sinais
internos, o que foi decisivo para diagnosticar o bug do PMP.

### Hardware (FPGA Genesys2, Xilinx Kintex-7)
O *bitstream* do CVA6 é gerado com o Vivado e carregado na FPGA. O ELF é carregado e depurado via
JTAG com OpenOCD e GDB. O *output* é lido pela UART. A demo física usa um pino GPIO a gerar PWM,
um *driver* de ponte H **L298N** e um **motor DC**.

### Escolher uma demo
- **Zephyr:** ver [`zephyr_apps/README.md`](zephyr_apps/README.md). A demo é escolhida no
  `target_sources` do `CMakeLists.txt`.
- **FreeRTOS:** ver [`FreeRTOS/demos_seguranca/README.md`](FreeRTOS/demos_seguranca/README.md). Cada
  demo substitui o `main_blinky.c` do port `RISC-V_cva6`.

---

## Trabalho futuro

1. **Isolamento PMP por *task* no FreeRTOS**, reconfigurando as entradas a cada *context switch*, à
   semelhança do Zephyr.
2. **Suporte integral a U-Mode no FreeRTOS**, com *system calls* a mediar o acesso a CSRs, para que
   primitivas como `vTaskDelay` funcionem a partir de *tasks* em U-Mode.
3. **Tolerância a falhas no Zephyr**, terminando apenas a *task* ofensora em vez de parar todo o sistema.

---

## Referências principais

- RISC-V International, *The RISC-V Instruction Set Manual, Vol. II: Privileged Architecture* (2024)
- OpenHW Group, [CVA6](https://github.com/openhwgroup/cva6)
- [FreeRTOS](https://www.freertos.org), [Zephyr Project](https://github.com/zephyrproject-rtos/zephyr)
- [Verilator](https://www.veripool.org/verilator/), [OpenOCD](https://openocd.org), [Genesys 2](https://digilent.com/reference/programmable-logic/genesys-2/start)

Bibliografia completa no relatório.

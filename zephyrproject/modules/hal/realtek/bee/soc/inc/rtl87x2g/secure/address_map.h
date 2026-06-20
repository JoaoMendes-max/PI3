/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ADDRESS_MAP_H
#define ADDRESS_MAP_H

/* ================================================================================ */
/* ================                  Address Map                   ================ */
/* ======== Reference: RTL87x2G_AddrMap_IRQs_DmaPorts_20220913v0.xlsx   ============ */
/* ================================================================================ */

#define SYSTEM_REG_BASE                    0x50000000UL
#define RTC_REG_BASE                       0x50001800UL
#define LPC_REG_BASE                       0x50001850UL
#define LPC0_REG_BASE                      0x50001850UL
#define PAD_REG_BASE                       0x50001900UL
#define PAD_STS_REG_BASE                   0x50001AA0UL
#define AON_WDT_REG_BASE                   0x50001B60UL
#define AUXADC_REG_BASE                    0x50001B90UL
#define QUAD_DECODER_REG_BASE              0x50001BD0UL
#define PERI_ON_REG_BASE                   0x50002000UL
#define PERI_ON_RCC_REG_BASE               0x50002300UL
#define GPIOA_DEB_REG_BASE                 0x5000234CUL
#define GPIOB_DEB_REG_BASE                 0x50002360UL
#define TIMER_PWM_REG_BASE                 0x5000233CUL
#define PINMUX_REG_BASE                    0x50002500UL
#define QDEC_REG_BASE                      0x50009000UL
#define SPI0_REG_BASE                      0x50013000UL
#define SPI1_REG_BASE                      0x50013500UL
#define SPI_SLAVE_REG_BASE                 0x50013800UL
#define ENHANCED_TIMER_REG_BASE            0x50017000UL
#define MODEMRFCPI_REG_BASE                0x50018000UL
#define I2S0_REG_BASE                      0x50020000UL
#define I2S1_REG_BASE                      0x50021000UL
#define SPI_CODEC_REG_BASE                 0x50022000UL
#define DISPLAY_CTRL_REG_BASE              0x50023000UL
#define RXI350_DMAC0_CFG_REG_BASE          0x50025000UL
#define PPE_CFG_REG_BASE                   0x50025000UL
#define ISO7816_REG_BASE                   0x50026000UL
#define SEGCOM_CTL_REG_BASE                0x50027000UL
#define CAN_REG_BASE                       0x50028000UL
#define SPIC_PHY_REG_BASE                  0x50029000UL

#define PUBLIC_KEY_ENGINE_REG_BASE         0x50080000UL
#define FLASH_SEC_REG_BASE                 0x500C0000UL
#define AES_REG_BASE                       0x500C1000UL
#define SHA256_REG_BASE                    0x500C2000UL
#define TRNG_REG_BASE                      0x500C2500UL
#define EFUSE_CONTROLLER_REG_BASE          0x500C2800UL
#define USB_OTG_CFG_REG_BASE               0x50100000UL
#define SPIC0_REG_BASE                     0x50150000UL
#define SDHC_REG_BASE                      0x50150000UL
#define SPIC1_REG_BASE                     0x50160000UL
#define SPIC2_REG_BASE                     0x50170000UL
#define GPIOA_REG_BASE                     0x50030000UL
#define GPIOB_REG_BASE                     0x50030800UL
#define TIMER_REG_BASE                     0x50031000UL
#define SAR_ADC_REG_BASE                   0x50032000UL
#define HRADC_REG_BASE                     0x50033000UL
#define UART0_REG_BASE                     0x50035000UL
#define UART1_REG_BASE                     0x50034500UL
#define UART2_REG_BASE                     0x50034800UL
#define UART3_REG_BASE                     0x50034C00UL
#define UART4_REG_BASE                     0x50035000UL
#define UART5_REG_BASE                     0x50035500UL
#define I2C0_REG_BASE                      0x50035800UL
#define I2C1_REG_BASE                      0x50035C00UL
#define I2C2_REG_BASE                      0x50036000UL
#define I2C3_REG_BASE                      0x50036500UL
#define SPI3W_REG_BASE                     0x50036800UL
#define KEYSCAN_REG_BASE                   0x50037000UL
#define IR_RC_REG_BASE                     0x50038000UL
#define ETH_CTRL_REG_BASE                  0x50050000UL
#define BLUEWIZ_REG_BASE                   0x50050000UL
#define BT_DMA_UART_BASE                   0x50051000UL
#define BT_DMA_BASE                        0x50055000UL
#define BT_VENDOR_REG_BASE                 0x50058000UL
#define ZIGBEE_REG_BASE                    0x5005C000UL
#define SPI0_HS_REG_BASE                   0x50060000UL
#define IDU_REG_BASE                       0x50070000UL


#endif //#define ADDRESS_MAP_H 

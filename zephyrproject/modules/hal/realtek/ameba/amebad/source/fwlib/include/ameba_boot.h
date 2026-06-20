/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HAL_AMEBA_BOOT_
#define _HAL_AMEBA_BOOT_

extern u8 __image1_validate_code__[];
extern u8 __image1_bss_start__[];
extern u8 __image1_bss_end__[];

extern u8 __image2_entry_func__[];
extern u8 __bss_start__[];
extern u8 __bss_end__[];

extern u8 __cmd_table_start__[];
extern u8 __cmd_table_end__[];
extern u8 __psram_bss_start__[];
extern u8 __psram_bss_end__[];
extern u8 __ram_nocache_start__[];
extern u8 __ram_nocache_end__[];
extern u8 __image3_bss_start__[];
extern u8 __image3_bss_end__[];

extern u8 __ipc_table_start__[];
extern u8 __ipc_table_end__[];
extern u8 __git_ver_table_start__[];
extern u8 __git_ver_table_end__[];

extern u8 __bdram_heap_buffer_start__[];
extern u8 __bdram_heap_buffer_size__[];
extern u8 __psram_heap_buffer_start__[];
extern u8 __psram_heap_buffer_size__[];
extern u8 __psram_heap_extend_start__[];
extern u8 __psram_heap_extend_size__[];

extern u8 __rom_bss_start__[];
extern u8 __rom_bss_end__[];
extern u8 __rom_bss_start_s__[];
extern u8 __rom_bss_end_s__[];
extern u8 __rom_bss_start_ns__[];
extern u8 __rom_bss_end_ns__[];
extern u8 __ram_image3_start__[];
extern u8 __ram_image3_end__[];
extern u8 __psram_image3_start__[];
extern u8 __psram_image3_end__[];

extern u8 __ls_flash_text_start__[];
extern u8 __hs_flash_text_start__[];
extern u8 __flash_sec_text_start__[];
extern u8 __ram_start_table_start__[];

extern u8  __rom_entry_ns_start__[];
extern u8 __retention_entry_func__[];

enum _BOOT_TYPE_ {
	BOOT_FROM_FLASH = 0,
	BOOT_FROM_SDIO  = 1,
	BOOT_FROM_USB   = 2,
	BOOT_FROM_UART0   = 3,
	BOOT_FROM_UART1   = 4,
	BOOT_FROM_SPI   = 5,
	BOOT_FROM_RSVD  = 6,
};

/* security boot */
typedef struct {
	int (*ed25519_verify_signature)(const unsigned char sig[],
									const unsigned char *m, unsigned long long mlen,
									const unsigned char pk[]);
	void (*clear_ns_rom_bss)(void);
} ROM_SECURE_CALL_NS_ENTRY;

enum _CPU_PWRSEQ_ {
	CPU_PWRSEQ_CMD_READ = 0xFFFFFF00,
	CPU_PWRSEQ_CMD_WRITE  = 0xFFFFFF01,
	CPU_PWRSEQ_CMD_POLLING   = 0xFFFFFF02,
	CPU_PWRSEQ_CMD_DELAY   = 0xFFFFFF03,
	CPU_PWRSEQ_CMD_LOGE   = 0xFFFFFF08,
	CPU_PWRSEQ_CMD_END   = 0xFFFFFFFF,
};

typedef struct {
	u32 address;
	u32 cmd; /* read/write/polling/delay/end */
	u32 bitsc; /* bit mask clear or polling target */
	u32 bitss; /* bit mask set or polling mask */
} CPU_PWR_SEQ;

typedef enum {
	IMG_LS_BOOT = 0,
	IMG_BACKUP = 1,
	IMG_SYSDATA =  2,
	IMG_HS_BOOT = 3,
	IMG_LS_IMG2_OTA1 = 4,
	IMG_HS_IMG_COMB_OTA1 = 5,
	IMG_LS_IMG2_OTA2 = 6,
	IMG_HS_IMG_COMB_OTA2 = 7,
} Image_Type;

typedef struct {
	u32 VAddrStart;
	u32 VAddrEnd;
	u32 PAddrStart;
	u32 PAddrEnd;
} MMU_ConfDef;

#define OTA_INDEX_1			0
#define OTA_INDEX_2			1

#define SECURE_BOOT_CHECK	0x28

/* CHECK STATUS */
#define BIT_KM0_SIGN_OK					BIT(0) /* KM0 signature check OK */
#define BIT_KM0_SIGN_FAIL					BIT(1)
#define BIT_KM4_RUN							BIT(2)

typedef struct {
	void (*rdp_decrypt_func)(u32 addr, u8 *key, u8  cnt, u8 *buf);
	u32 psram_s_start_addr;
} BOOT_EXPORT_SYMB_TABLE;

typedef struct {
	void (*RamStartFun)(void);
	void (*RamWakeupFun)(void);
	u32 VectorNS;
} RAM_START_FUNCTION, *PRAM_START_FUNCTION;

typedef struct _RAM_FUNCTION_START_TABLE_ {
	void (*RamStartFun)(void);
	void (*RamWakeupFun)(void);
	void (*RamPatchFun0)(void);
	void (*RamPatchFun1)(void);
	void (*RamPatchFun2)(void);
	void (*FlashStartFun)(void);
	u32 Img1ValidCode;
	BOOT_EXPORT_SYMB_TABLE *ExportTable;
} RAM_FUNCTION_START_TABLE, *PRAM_FUNCTION_START_TABLE;

typedef struct _DSLP_RETENTION_FUNC_TABLE_ {
	void (*DSLPPatchFun0)(void);
	u32	PatchLen;
} DSLP_RETENTION_FUNC_TABLE, *PDSLP_RETENTION_FUNC_TABLE;

struct _driver_call_os_func_map {
	void (*driver_enter_critical)(void);
	void (*driver_exit_critical)(void);
};


typedef struct {
	u32 MaskAddr; /*start address for RSIP Mask, should be 4KB aligned*/
	u8 MaskSize; /*size of the mask area, unit is 4KB, Max Size 255*4KB */
} RSIP_MaskDef;

#if defined (__ARM_FEATURE_CMSE)
#define NS_ENTRY    __attribute__((cmse_nonsecure_entry))
#if defined (CONFIG_ARM_CORE_CM4)
typedef void __attribute__((cmse_nonsecure_call)) nsfunc(void);
#endif
#endif

typedef u8(*FuncPtr)(void);

extern void SysTick_Handler(void);
extern void SVC_Handler(void);
extern void PendSV_Handler(void);

extern u32 BOOT_ROM_CM4PON(u32 pwr_cmd_addr);
extern void BOOT_FLASH_Image1(void);
extern void BOOT_FLASH_Image1_2nd(void);
extern void BOOT_FLASH_WakeFromPG(void);
extern void BOOT_RAM_FuncEnable(void);
extern u32 BOOT_RAM_FLASH_Calibration(u8 read_mode);
extern void BOOT_FLASH_Invalidate_Auto_Write(void);

extern u32 ROM_SIM_ENABLE;
extern u32 IS_FPGA_VERIF; /* set in boot flash, based on MACRO, can not be used in ROM code */
extern RAM_START_FUNCTION Img2EntryFun0; //RamWakeupFun

#define EXC_RETURN_PREFIX          (0xFF000000UL)     /* bits [31:24] set to indicate an EXC_RETURN value                     */
#define EXC_RETURN_S               (0x00000040UL)     /* bit [6] stack used to push registers: 0=Non-secure 1=Secure          */
#define EXC_RETURN_DCRS            (0x00000020UL)     /* bit [5] stacking rules for called registers: 0=skipped 1=saved       */
#define EXC_RETURN_FTYPE           (0x00000010UL)     /* bit [4] allocate stack for floating-point context: 0=done 1=skipped  */
#define EXC_RETURN_MODE            (0x00000008UL)     /* bit [3] processor mode for return: 0=Handler mode 1=Thread mode      */
#define EXC_RETURN_SPSEL           (0x00000004UL)     /* bit [2] stack pointer used to restore context: 0=MSP 1=PSP           */
#define EXC_RETURN_ES              (0x00000001UL)     /* bit [0] security state exception was taken to: 0=Non-secure 1=Secure */

#define IS_FLASH_ADDR(addr)			((addr >= SPI_FLASH_BASE) && (addr <= 0x0FFFFFFF))


#define KM0_CPU_ID 0
#define KM4_CPU_ID 1

/**
  * @brief  Get Current CPU
  * @param  None
  * @retval CPU ID.
  *		 0: CPU_KM0
  *		 1: CPU_KM4
  */
__STATIC_INLINE u32 SYS_CPUID(void)
{
	/* same as IPC_CPUID() */
#ifdef CONFIG_ARM_CORE_CM4
	return KM4_CPU_ID;
#else
	return KM0_CPU_ID;
#endif
}

#endif   //_HAL_AMEBA_BOOT_

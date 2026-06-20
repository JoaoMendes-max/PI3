/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _IMAGE_HEADER_H_
#define _IMAGE_HEADER_H_

#include <stdbool.h>
#include <stdint.h>

/*============================================================================*
  *                                   Constants
  *============================================================================*/
#define DEFAULT_HEADER_SIZE           (0x400)
#define CMAC_BYTE_SIZE                (16)
#define RSA_2048_PUBLIC_KEY_BYTE_SIZE (256)
#define RSA_2048_SIGNATURE_BYTE_SIZE  (RSA_2048_PUBLIC_KEY_BYTE_SIZE)
#define RSA_3072_PUBLIC_KEY_BYTE_SIZE (384)
#define RSA_3072_SIGNATURE_BYTE_SIZE  (RSA_3072_PUBLIC_KEY_BYTE_SIZE)
#define SHA256_BYTE_SIZE              (32)
#define SIGNATURE_APP_CB              0x0e85d101 /**< patch callback app signature definition*/
#define UUID_SIZE                     16

#define IMG_IC_TYPE          0x10

#define DFU_HEADER_SIZE          12  /*currently, first 12 byte only will be treated as image header*/
#define IMG_HEADER_SIZE          1024
#define OTA_HEADER_SIZE          (4 * 1024)
#define DECODE_OFFSET            (sizeof(T_COMPRESS_IMG_HEADER_FORMAT))

#define FSBL_EXT_PATTERN         0x736c

#define UP_ALIGN(size, align)    (((size) + (align) - 1) & ~(align - 1))

#define SYS_CFG_SIGNATURE           0x12345bb3
#define FLASH_TABLE_MAGIC_PATTERN   (0x5A5A12A5)

/*============================================================================*
  *                                   Types
  *============================================================================*/

typedef enum
{
    IMAGE_FIRST = 0x278D,
    SCCD        = 0x278D,
    OCCD        = 0x278E,
    FactoryCode = 0x278F,
    OTA         = 0x2790, /**< OTA header */
    SecureBoot  = 0x2791,
    RomPatch    = 0x2792,
    AppPatch    = 0x2793,
    AppData1    = 0x2794,
    AppData2    = 0x2795,
    AppData3    = 0x2796,
    AppData4    = 0x2797,
    AppData5    = 0x2798,
    AppConfigFile = 0x2799,
    UpperStack  = 0x279a,
    IMG_BT_STACKPATCH = 0x279b,
    IMAGE_MAX,

    IMAGE_USER_DATA2 = 0xFFFD,  /**< the image only supports unsafe single bank OTA */
    IMAGE_USER_DATA = 0xFFFE,  /**< the image only supports unsafe single bank OTA */
} T_IMG_ID;

typedef enum
{
    ENC_KEY_SCEK = 0,
    ENC_KEY_SCEK_WITH_RTKCONST,
    ENC_KEY_OCEK,
    ENC_KEY_OCEK_WITH_OEMCONST,
    ENC_KEY_ON_FLASH,
    ENC_KEY_MAX,
} T_ENC_KEY_SELECT;

typedef struct
{
    union
    {
        struct
        {
            uint8_t N[RSA_2048_PUBLIC_KEY_BYTE_SIZE];
            uint8_t E[4];
        } rsa_2048_pub_key;

        struct
        {
            uint8_t N[RSA_3072_PUBLIC_KEY_BYTE_SIZE];
            uint8_t E[4];
        } rsa_3072_pub_key;
    };

} T_RSA_PUBLIC_KEY;

typedef enum _APP_IMAGE_TYPE
{
    IMAGE_NORMAL              = 0,
    IMAGE_COMPRESSED          = 1,
    //2-7 are reserved
} T_IMAGE_TYPE;

typedef struct _IMG_CTRL_HEADER_FORMAT
{
    uint16_t crc16;
    uint8_t ic_type;
    uint8_t secure_version;
    union
    {
        uint16_t value;
        struct
        {
            uint16_t xip: 1; // payload is executed on flash
            uint16_t enc: 1; // all the payload is encrypted
            uint16_t load_when_boot: 1; // load image when boot
            uint16_t enc_load: 1; // encrypt load part or not
            uint16_t enc_key_select: 3; // referenced to ENC_KEY_SELECT
            uint16_t not_ready: 1; // for copy image in OTA
            uint16_t not_obsolete: 1; // for copy image in OTA
            uint16_t integrity_check_en_in_boot: 1; // enable image integrity check in boot flow
            uint16_t compressed_not_ready: 1;
            uint16_t compressed_not_obsolete: 1;
            uint16_t rsvd: 1;
            uint16_t image_type: 3; /* for app 000b: normal image, 001b:compressed image, other for more types
            for patch in temp bank consist of 001b: patch+fsbl, 010b: patch+app, 011b: patch+fsbl+app*/
        } flag_value;
    } ctrl_flag;
    uint16_t image_id;
    uint32_t payload_len;
} T_IMG_CTRL_HEADER_FORMAT;

typedef struct _COMPRESS_IMG_HEADER_FORMAT //96 bytes
{
    T_IMG_CTRL_HEADER_FORMAT ctrl_header; //12 bytes
    uint8_t uuid[16];
    uint32_t version;
    uint32_t compress_algo;
    uint8_t sha256[32];
    uint8_t reserved[28];
} T_COMPRESS_IMG_HEADER_FORMAT;

typedef struct
{
    union
    {
        uint32_t version;
        struct
        {
            uint32_t _version_reserve: 8;   //!< reserved
            uint32_t _version_revision: 8; //!< revision version
            uint32_t _version_minor: 8;     //!< minor version
            uint32_t _version_major: 8;     //!< major version
        } header_sub_version; //!< ota header sub version
        struct
        {
            uint32_t _version_major: 4;     //!< major version
            uint32_t _version_minor: 8;     //!< minor version
            uint32_t _version_revision: 15; //!< revision version
            uint32_t _version_reserve: 5;   //!< reserved
        } img_sub_version; //!< other image sub version including patch, app, app data 1-6

    } ver_info;
} T_IMAGE_VERSION;

typedef struct
{
    union
    {
        uint32_t version;
        struct
        {
            uint32_t _version_major: 4;     //!< major version
            uint32_t _version_minor: 8;     //!< minor version
            uint32_t _version_revision: 15; //!< revision version
            uint32_t _version_reserve: 5;   //!< reserved
        } sub_version;
    } ver_info;
    uint32_t _version_commitid;     //!< git commit id
    uint8_t _customer_name[8];      //!< branch name for customer patch
} T_VERSION_FORMAT;

typedef struct _AUTH_HEADER_FORMAT
{
    uint8_t image_mac[CMAC_BYTE_SIZE];
    union
    {
        uint8_t rsa_image_2048_signature[RSA_2048_SIGNATURE_BYTE_SIZE];
        uint8_t rsa_image_3072_signature[RSA_3072_SIGNATURE_BYTE_SIZE];
    } sig;
    uint8_t image_hash[SHA256_BYTE_SIZE];
} T_AUTH_HEADER_FORMAT;

typedef union
{
    uint8_t bytes[24];
    struct
    {
        uint32_t itcm_heap_addr;
        uint32_t app_ram_data_size;
        uint32_t app_heap_data_on_size;
    } app_ram_info;
} T_EXTRA_INFO_FORMAT;

typedef struct _FLASH_SEC_FORMAT
{
    union
    {
        uint32_t value;
        struct
        {
            uint32_t enable: 1;
            uint32_t mode: 2; // gcm mode:0b00, ctr mode:0b01, mix mode:0b10
            uint32_t key_select: 3;
            uint32_t rsvd: 26;
        };
    } ctrl_flag;
    uint32_t base_addr;
    uint32_t region_size;
    uint8_t iv_high[4];
    uint8_t iv_low[4];
} T_FLASH_SEC_FORMAT;

typedef union _IMG_HEADER_FORMAT
{
    uint8_t bytes[DEFAULT_HEADER_SIZE];
    struct
    {
        T_AUTH_HEADER_FORMAT auth;   //16 +384 +32
        T_IMG_CTRL_HEADER_FORMAT ctrl_header;
        uint8_t uuid[16];
        uint32_t exe_base;
        uint32_t load_src;
        uint32_t load_len;
        uint32_t image_base;
        uint16_t dev_id; // for AMZN
        uint16_t flash_layout_size_4k; // ex. 1MB flash used size => flash_layout_size_4k = 1MB/4KB = 256
        uint32_t magic_pattern;
        uint8_t dec_key[16];
        uint32_t load_dst;
        T_EXTRA_INFO_FORMAT ex_info;
        T_VERSION_FORMAT git_ver;
        T_RSA_PUBLIC_KEY PubKey;
        union
        {
            uint8_t reserved_data[92];
            struct
            {
                uint32_t ver_val;
                uint32_t image_info[(IMAGE_MAX - SecureBoot) * 2];
            };
            struct __attribute__((packed))
            {
                uint16_t tool_version;
                uint32_t timestamp;
                T_FLASH_SEC_FORMAT flash_sec_cfg;
                uint16_t fsbl_ext_img_id;
                uint16_t fsbl_ext_load_pattern;
                uint8_t reserved1[62];
            };
        };
    };
} T_IMG_HEADER_FORMAT;

typedef struct _ROM_HEADER_FORMAT
{
    uint8_t uuid[UUID_SIZE];
    void *init_ptr;
    void *entry_ptr;
} T_ROM_HEADER_FORMAT;

#endif /* _IMAGE_HEADER_H_ */

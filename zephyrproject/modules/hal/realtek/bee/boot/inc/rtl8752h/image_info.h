/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PATCH_HEADER_CHECK_H_
#define _PATCH_HEADER_CHECK_H_

#include <stdbool.h>
#include <stdint.h>
#include "rtl876x.h"
#include "flash_nor_device.h"
#include "image_header.h"
#include "image_check.h"

/*============================================================================*
  *                                   Functions
 *============================================================================*/

/**
 * @brief  Get image address in OTA header
 *
 * @param[in]  ota_addr: valid OTA header address
 * @param[in]  image_id: image ID
 *
 * @return Image address in OTA header
*/
extern uint32_t *get_image_addr_in_bank(uint32_t ota_addr, T_IMG_ID image_id);

/**
 * @brief  Get image size in OTA header
 *
 * @param[in]  ota_addr: valid OTA header address
 * @param[in]  image_id: image ID
 *
 * @return Image size in OTA header
*/
extern uint32_t *get_image_size_in_bank(uint32_t ota_addr, T_IMG_ID image_id);

/**
 * @brief  Get start address of active OTA bank
 *
 * @return Start address of active OTA bank
*/
extern uint32_t get_active_ota_bank_addr(void);

/**
 * @brief  Check configured flash layout support bank switch
 *
 * @return Check result
 * @retval true Support bank switch
 * @retval false Otherwise
*/
extern bool is_ota_support_bank_switch(void);

/**
 * @brief  Calculate checksum (CRC16 or SHA256 determined by image) over the image, and compare
 *         with given checksum value.
 *
 * @param  p_header Image header info of the given image.
 *
 * @return Check result
 * @retval true If image integrity check passes via checksum compare
 * @retval false Otherwise
*/
extern bool check_image_chksum(T_IMG_HEADER_FORMAT *p_header);

/**
 * @brief  Get specified image header address in active bank
 *
 * @param[in]  image_id Specify the image
 *
 * @return Specified image header address
*/
extern uint32_t get_header_addr_by_img_id(T_IMG_ID image_id);

/**
 * @brief  Get image size of specified image which is located in OTA active bank
 *
 * @param[in]  image_id Specify the image which is located in OTA active bank
 * @return Image size of specified image which is located in OTA active bank
*/
extern uint32_t get_active_bank_image_size_by_img_id(T_IMG_ID image_id);
/**
 * @brief  Get start address of specified image which is located in OTA temp bank
 *
 * @param[in]  image_id Specify the image
 * @return Start address of specified image which is located in OTA temp bank
*/
static uint32_t get_temp_ota_bank_addr_by_img_id(T_IMG_ID image_id);

/**
 * @brief  Get the size of the specified image located in the OTA temp bank.
 *
 * @param[in]  image_id Specify the image.
 * @return The size of the specified image located in the OTA temp bank.
*/
static uint32_t get_temp_ota_bank_size_by_img_id(T_IMG_ID image_id);

/**
 * @brief  Get version info of the specified image located in the active bank.
 *
 * @param[in]  image_id Specify the image.
 * @return Version info of the specified image located in the active bank.
*/
extern bool get_active_bank_image_version(T_IMG_ID image_id, T_IMAGE_VERSION *p_image_version);

static inline uint32_t get_temp_ota_bank_addr_by_img_id(T_IMG_ID image_id)
{
    uint32_t image_addr = 0;
    if (image_id < OTA || ((image_id >= IMAGE_MAX)))
    {
        return image_addr;
    }
    if (!is_ota_support_bank_switch())
    {
        if (image_id == OTA)
        {
            return 0;
        }
        image_addr = flash_nor_get_bank_addr(FLASH_OTA_TMP);
    }
    else
    {
        uint32_t ota_bank0_addr = flash_nor_get_bank_addr(FLASH_OTA_BANK_0);
        uint32_t temp_bank_addr;
        if (ota_bank0_addr == get_active_ota_bank_addr())
        {
            temp_bank_addr = flash_nor_get_bank_addr(FLASH_OTA_BANK_1);
        }
        else
        {
            temp_bank_addr = ota_bank0_addr;
        }
        if (image_id == OTA)
        {
            image_addr = temp_bank_addr;
        }
        else if (image_id >= SecureBoot && image_id < IMAGE_MAX)
        {
            if (IMG_CHECK_PASS != check_header_valid(temp_bank_addr, OTA))
            {
                return 0;
            }
            image_addr = *get_image_addr_in_bank(temp_bank_addr, image_id);
        }
    }
    if (image_addr == 0xffffffff)
    {
        return 0;
    }
    return image_addr;
}

static inline uint32_t get_temp_ota_bank_size_by_img_id(T_IMG_ID image_id)
{
    uint32_t image_size = 0;

    if (image_id < OTA || ((image_id >= IMAGE_MAX)))
    {
        return image_size;
    }

    if (!is_ota_support_bank_switch())
    {
        if (image_id == OTA)
        {
            return 0;
        }

        image_size = flash_nor_get_bank_size(FLASH_OTA_TMP);
    }
    else
    {
        uint32_t ota_bank0_addr = flash_nor_get_bank_addr(FLASH_OTA_BANK_0);
        uint32_t temp_bank_addr;

        if (ota_bank0_addr == get_active_ota_bank_addr())
        {
            temp_bank_addr = flash_nor_get_bank_addr(FLASH_OTA_BANK_1);
        }
        else
        {
            temp_bank_addr = ota_bank0_addr;
        }

        if (image_id == OTA)
        {
            image_size = OTA_HEADER_SIZE;
        }
        else if (image_id >= SecureBoot && image_id < IMAGE_MAX)
        {
            if (IMG_CHECK_PASS != check_header_valid(temp_bank_addr, OTA))
            {
                return 0;
            }

            image_size = *get_image_size_in_bank(temp_bank_addr, image_id);
        }
    }

    return image_size;
}

#endif /* _PATCH_HEADER_CHECK_H_ */

/**
 * @file    flash_hal_stm32f103xb.c
 * @brief
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2019, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "flash_hal.h"        // FlashOS Structures
#include "target_config.h"    // target_device
#include "stm32f2xx.h"
#include "util.h"
#include "string.h"
#include "target_board.h"

#define FLASH_PAGE_SIZE         ((uint32_t)0x4000)
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
static uint32_t GetSector(uint32_t Address)
{
    uint32_t sector = 0;

    if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0)) {
        sector = FLASH_SECTOR_0;  
    } else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1)) {
        sector = FLASH_SECTOR_1;  
    } else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2)) {
        sector = FLASH_SECTOR_2;  
    } else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3)) {
        sector = FLASH_SECTOR_3;  
    } else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4)) {
        sector = FLASH_SECTOR_4;  
    } else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5)) {
        sector = FLASH_SECTOR_5;  
    } else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6)) {
        sector = FLASH_SECTOR_6;  
    } else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7)) {
        sector = FLASH_SECTOR_7;  
    } else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8)) {
        sector = FLASH_SECTOR_8;  
    } else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9)) {
        sector = FLASH_SECTOR_9;  
    } else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10)) {
        sector = FLASH_SECTOR_10;  
    } else {
        sector = FLASH_SECTOR_11;  
    }

    return sector;
}

uint32_t Init(uint32_t adr, uint32_t clk, uint32_t fnc)
{
    //
    // No special init required
    //
    return (0);
}

uint32_t UnInit(uint32_t fnc)
{
    //
    // No special uninit required
    //
    return (0);
}

uint32_t EraseChip(void)
{
    FLASH_EraseInitTypeDef erase_init;
    uint32_t error;
    uint32_t ret = 0;  // O.K.
    if (g_board_info.target_cfg) {
        HAL_FLASH_Unlock();
        //bootloader, interface flashing only concerns 1 flash region
        util_assert((g_board_info.target_cfg->flash_regions[0].end - g_board_info.target_cfg->flash_regions[0].start) %
                    FLASH_PAGE_SIZE == 0);
        memset(&erase_init, 0, sizeof(erase_init));
        erase_init.TypeErase = FLASH_TYPEERASE_MASSERASE;
        erase_init.Sector = GetSector(g_board_info.target_cfg->flash_regions[0].start);
		erase_init.NbSectors = GetSector(g_board_info.target_cfg->flash_regions[0].end) - GetSector(g_board_info.target_cfg->flash_regions[0].start) + 1;
        if (HAL_FLASHEx_Erase(&erase_init, &error) != HAL_OK) {
            ret = 1;
        }
        
        HAL_FLASH_Lock();
    }else{
        ret = 1;
    }
    return ret;
}

uint32_t EraseSector(uint32_t adr)
{
	static uint32_t back_buffer[32768 / 4];
    FLASH_EraseInitTypeDef erase_init;
    uint32_t error;
    uint32_t ret = 0;  // O.K.

	if(adr >= 0x08028000)
		memcpy(back_buffer, (void*)0x08020000, sizeof(back_buffer));
	else if(adr >= 0x08020000)
		memcpy(back_buffer, (void*)0x08028000, sizeof(back_buffer));
	else if(adr >= 0x08018000)
		memcpy(back_buffer, (void*)0x08010000, sizeof(back_buffer));
	else if(adr >= 0x08010000)
		memcpy(back_buffer, (void*)0x08018000, sizeof(back_buffer));
	
    HAL_FLASH_Unlock();
	
    memset(&erase_init, 0, sizeof(erase_init));
    erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
    erase_init.Sector = GetSector(adr);
    erase_init.NbSectors = 1;
    if (HAL_FLASHEx_Erase(&erase_init, &error) != HAL_OK) {
        ret = 1;
    }
	
    HAL_FLASH_Lock();

	if(adr >= 0x08028000)
		ProgramPage(0x08020000, sizeof(back_buffer), back_buffer);
	else if(adr >= 0x08020000)
		ProgramPage(0x08028000, sizeof(back_buffer), back_buffer);
	else if(adr >= 0x08018000)
		ProgramPage(0x08010000, sizeof(back_buffer), back_buffer);
	else if(adr >= 0x08010000)
		ProgramPage(0x08018000, sizeof(back_buffer), back_buffer);
	
    return ret;
}

uint32_t ProgramPage(uint32_t adr, uint32_t sz, uint32_t *buf)
{
    uint32_t i;
    uint32_t ret = 0;  // O.K.

    HAL_FLASH_Unlock();

    util_assert(sz % 4 == 0);
    for (i = 0; i < sz / 4; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, adr + i * 4, buf[i]) != HAL_OK) {
            ret = 1;
            break;
        }
    }

    HAL_FLASH_Lock();
    return ret;
}

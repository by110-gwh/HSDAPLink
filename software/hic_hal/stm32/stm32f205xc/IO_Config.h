/**
 * @file    IO_Config.h
 * @brief
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
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

#ifndef __IO_CONFIG_H__
#define __IO_CONFIG_H__

#include "stm32f2xx.h"
#include "compiler.h"
#include "daplink.h"

COMPILER_ASSERT(DAPLINK_HIC_ID == DAPLINK_HIC_ID_STM32F205XC);

//Connected LED
#define CONNECTED_LED_PORT           GPIOB
#define CONNECTED_LED_PIN            GPIO_PIN_15
#define CONNECTED_LED_PIN_Bit        15

//When bootloader, disable the target port
#define POWER_EN_PIN_PORT            GPIOB
#define POWER_EN_PIN                 GPIO_PIN_3
#define POWER_EN_Bit                 3

// nRESET OUT Pin
#define nRESET_PIN_PORT              GPIOC
#define nRESET_PIN                   GPIO_PIN_5
#define nRESET_PIN_Bit               5

// nTRST Pin
#define nTRST_PIN_PORT               GPIOB
#define nTRST_PIN                    GPIO_PIN_14
#define nTRST_PIN_Bit                14

//SWD
#define SWCLK_TCK_PIN_PORT           GPIOA
#define SWCLK_TCK_PIN                GPIO_PIN_2
#define SWCLK_TCK_PIN_Bit            2

#define SWDIO_OUT_PIN_PORT           GPIOC
#define SWDIO_OUT_PIN                GPIO_PIN_1
#define SWDIO_OUT_PIN_Bit            1

#define SWDIO_IN_PIN_PORT            GPIOC
#define SWDIO_IN_PIN                 GPIO_PIN_13
#define SWDIO_IN_PIN_Bit             13

// JTAG-TCK
#define JTAG_TCK_PIN_PORT            SWCLK_TCK_PIN_PORT
#define JTAG_TCK_PIN                 SWCLK_TCK_PIN
#define JTAG_TCK_PIN_Bit             SWCLK_TCK_PIN_Bit

// JTAG-TMS
#define JTAG_TMS_PIN_PORT            SWDIO_OUT_PIN_PORT
#define JTAG_TMS_PIN                 SWDIO_OUT_PIN
#define JTAG_TMS_PIN_Bit             SWDIO_OUT_PIN_Bit

// JTAG-TDI
#define JTAG_TDI_PIN_PORT            GPIOA
#define JTAG_TDI_PIN                 GPIO_PIN_7
#define JTAG_TDI_PIN_Bit             7

// JTAG-TDO
#define JTAG_TDO_PIN_PORT            GPIOA
#define JTAG_TDO_PIN                 GPIO_PIN_4
#define JTAG_TDO_PIN_Bit             4

//LEDs
//USB status LED
#define RUNNING_LED_PORT             GPIOB
#define RUNNING_LED_PIN              GPIO_PIN_9
#define RUNNING_LED_Bit              9

#define PIN_HID_LED_PORT             GPIOC
#define PIN_HID_LED                  GPIO_PIN_11
#define PIN_HID_LED_Bit              11

#define PIN_CDC_LED_PORT             GPIOC
#define PIN_CDC_LED                  GPIO_PIN_10
#define PIN_CDC_LED_Bit              10

#define PIN_MSC_LED_PORT             GPIOA
#define PIN_MSC_LED                  GPIO_PIN_15
#define PIN_MSC_LED_Bit              15


#endif

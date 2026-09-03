/*---------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include  CMSIS_device_header

#include "ext_init.h"

#include "Driver_IO.h"
#include "board_defs.h"

/* Camera reset GPIO port */
extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(BOARD_CAMERA_RESET_GPIO_PORT);
static ARM_DRIVER_GPIO *IO_Driver_CAM_RST =
                        &ARM_Driver_GPIO_(BOARD_CAMERA_RESET_GPIO_PORT);

/* Camera power GPIO port */
extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(BOARD_CAMERA_POWER_GPIO_PORT);
static ARM_DRIVER_GPIO *IO_Driver_CAM_PWR =
                        &ARM_Driver_GPIO_(BOARD_CAMERA_POWER_GPIO_PORT);

/* Touch-controller reset GPIO port */
extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(BOARD_TOUCH_RESET_GPIO_PORT);
static ARM_DRIVER_GPIO *IO_Driver_TOUCH_RST =
                        &ARM_Driver_GPIO_(BOARD_TOUCH_RESET_GPIO_PORT);

/* LCD reset GPIO port */
extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(BOARD_LCD_RESET_GPIO_PORT);
static ARM_DRIVER_GPIO *IO_Driver_LCD_RST =
                        &ARM_Driver_GPIO_(BOARD_LCD_RESET_GPIO_PORT);

/*
  Initialize reset and power I/Os to the external devices.
*/
void ext_init (void) {
  IO_Driver_CAM_PWR->Initialize(BOARD_CAMERA_POWER_GPIO_PIN, NULL);
  IO_Driver_CAM_PWR->PowerControl(BOARD_CAMERA_POWER_GPIO_PIN, ARM_POWER_FULL);
  IO_Driver_CAM_PWR->SetValue(BOARD_CAMERA_POWER_GPIO_PIN, GPIO_PIN_OUTPUT_STATE_LOW);
  IO_Driver_CAM_PWR->SetDirection(BOARD_CAMERA_POWER_GPIO_PIN, GPIO_PIN_DIRECTION_OUTPUT);

  IO_Driver_CAM_RST->Initialize(BOARD_CAMERA_RESET_GPIO_PIN, NULL);
  IO_Driver_CAM_RST->PowerControl(BOARD_CAMERA_RESET_GPIO_PIN, ARM_POWER_FULL);
  IO_Driver_CAM_RST->SetValue(BOARD_CAMERA_RESET_GPIO_PIN, GPIO_PIN_OUTPUT_STATE_LOW);
  IO_Driver_CAM_RST->SetDirection(BOARD_CAMERA_RESET_GPIO_PIN, GPIO_PIN_DIRECTION_OUTPUT);

  IO_Driver_TOUCH_RST->Initialize(BOARD_TOUCH_RESET_GPIO_PIN, NULL);
  IO_Driver_TOUCH_RST->PowerControl(BOARD_TOUCH_RESET_GPIO_PIN, ARM_POWER_FULL);
  IO_Driver_TOUCH_RST->SetValue(BOARD_TOUCH_RESET_GPIO_PIN, GPIO_PIN_OUTPUT_STATE_LOW);
  IO_Driver_TOUCH_RST->SetDirection(BOARD_TOUCH_RESET_GPIO_PIN, GPIO_PIN_DIRECTION_OUTPUT);

  IO_Driver_LCD_RST->Initialize(BOARD_LCD_RESET_GPIO_PIN, NULL);
  IO_Driver_LCD_RST->PowerControl(BOARD_LCD_RESET_GPIO_PIN, ARM_POWER_FULL);
  IO_Driver_LCD_RST->SetValue(BOARD_LCD_RESET_GPIO_PIN, GPIO_PIN_OUTPUT_STATE_LOW);
  IO_Driver_LCD_RST->SetDirection(BOARD_LCD_RESET_GPIO_PIN, GPIO_PIN_DIRECTION_OUTPUT);
}

/*
 * AMW0x7 - Library to manage AMW007/AMW037 Wi-Fi module based on libohiboard
 * Copyright (C) 2020 Marco Giammarini <http://www.warcomeb.it>
 *
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*!
 * \file  /amw0x7.h
 * \brief
 */

#ifndef __WARCOMEB_AMW0x7_H
#define __WARCOMEB_AMW0x7_H

#ifdef __cplusplus
extern "C" {
#endif

#define WARCOMEB_AMW0x7_LIBRARY_VERSION_MAJOR   (0x1ul)
#define WARCOMEB_AMW0x7_LIBRARY_VERSION_MINOR   (0x0ul)
#define WARCOMEB_AMW0x7_LIBRARY_VERSION_BUG     (0x0ul)
#define WARCOMEB_AMW0x7_LIBRARY_VERSION         ((WARCOMEB_AMW0x7_LIBRARY_VERSION_MAJOR << 16)\
                                                |(WARCOMEB_AMW0x7_LIBRARY_VERSION_MINOR << 8 )\
                                                |(WARCOMEB_AMW0x7_LIBRARY_VERSION_BUG        ))
#define WARCOMEB_BGX13P_LIBRARY_TIME            0

#include "amw0x7type.h"

#if !defined (WARCOMEB_AMW0x7_RX_BUFFER)
#define WARCOMEB_AMW0x7_RX_BUFFER               128
#endif

/*!
 * AMW0x7 device class.
 */
typedef struct _AMW0x7_Device_t
{
    Uart_DeviceHandle        device;
    Uart_Config              uartConfig;

    bool                     isAwake;
    bool                     isConnected;

    uint8_t                  rxBuffer[WARCOMEB_AMW0x7_RX_BUFFER];
    UtilityBuffer_Descriptor rxDescriptor;

    Gpio_Pins                pinReset;

} AMW0x7_Device_t, *AMW0x7_DeviceHandle_t;

/*!
 * AMW0x7 configuration struct.
 * An object of this class must be used to save all module configurations.
 */
typedef struct _AMW0x7_Config_t
{
    char deviceName[16];

} AMW0x7_Config_t;

void BGX13P_init (AMW0x7_DeviceHandle_t dev, AMW0x7_Config_t* config);

/*!
 * This function resets the module.
 * There are two ways:
 *   \li by the use of the hardware pin,
 *   \li or via software command.
 *
 * \param[in]  dev:
 * \param[in] type:
 */
AMW0x7_Errors_t AMW0x7_reset (AMW0x7_DeviceHandle_t dev, AMW0x7_ResetType_t type);

AMW0x7_Errors_t AMW0x7_sleep (AMW0x7_DeviceHandle_t dev);

AMW0x7_Errors_t AMW0x7_wake (AMW0x7_DeviceHandle_t dev);

bool AMW0x7_isAwake (AMW0x7_DeviceHandle_t dev);

/*!
 * This function ask to the module the current firmware version.
 */
AMW0x7_Errors_t AMW0x7_getFirmwareVersion (AMW0x7_DeviceHandle_t dev, char* data);

#ifdef __cplusplus
}
#endif

#endif // __WARCOMEB_AMW0x7_H

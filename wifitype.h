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
 * \file  /amw0x7type.h
 * \brief
 */

#ifndef __WARCOMEB_WIFI_TYPE_H
#define __WARCOMEB_WIFI_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NO_PROFILES
#include "board.h"
#include "firmware.h"
#endif

/*!
 * WiFi configuration struct.
 */
typedef struct _WiFi_Config_t
{
    uint8_t ip[4];
    uint8_t mask[4];
    uint8_t gatway[4];
    uint8_t dns[4];

    uint8_t mac[6];

} WiFi_Config_t;

typedef void *WiFi_LowLevelDriver_t  ;

/*!
 * List of possible errors.
 */
typedef enum _WiFi_Errors
{
    WIFI_ERRORS_NO_ERROR = 0,
} WiFi_Errors_t;

#ifdef __cplusplus
}
#endif

#endif // __WARCOMEB_WIFI_TYPE_H

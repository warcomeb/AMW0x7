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

#ifndef __WARCOMEB_AMW0x7_TYPE_H
#define __WARCOMEB_AMW0x7_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NO_PROFILES
#include "board.h"
#include "firmware.h"
#endif

/*!
 * Maximum length of a SSID
 */
#define AMW0x7_SSID_MAX_LENGTH                   32
/*!
 * Maximum length of WPA passphrase.
 * Valid lengths are 8-63.
 */
#define AMW0x7_WPA_KEY_MAX_LENGTH                63

/*!
 * List of possible module errors.
 */
typedef enum _AMW0x7_Errors
{
    AMW0x7_ERRORS_NO_ERROR,
    AMW0x7_ERRORS_COMMAND_FAIL,
    AMW0x7_ERRORS_COMMAND_TIMEOUT,
    AMW0x7_ERRORS_CONNECTION_FAIL,
} AMW0x7_Errors_t;

/*!
 * List module reset type.
 */
typedef enum _AMW0x7_ResetType
{
    AMW0x7_RESETTYPE_HARDWARE = 0,
    AMW0x7_RESETTYPE_SOFTWARE = 1,
} AMW0x7_ResetType_t;


#ifdef __cplusplus
}
#endif

#endif // __WARCOMEB_AMW0x7_TYPE_H

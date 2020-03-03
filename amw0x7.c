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
 * \file  /amw0x7.c
 * \brief
 */

#include "amw0x7.h"
#include <string.h>

#define AMW0x7_COMMAND_END_LINE                  "\r\n"
#define AMW0x7_COMMAND_DONE                      "> "

#define AMW0x7_READ_COMMAND_TIMEOUT              1000

/*!
 * List of specific module commands.
 */
typedef enum _AMW0x7_Command
{
    AMW0x7_COMMAND_NONE = 0,
    AMW0x7_COMMAND_VERSION,
    AMW0x7_COMMAND_SET_WLAN_SSID,
    AMW0x7_COMMAND_SET_WLAN_PASSKEY,
    AMW0x7_COMMAND_REBOOT,
} AMW0x7_Command_t;

void AMW0x7_uartRxInterrupt (Uart_DeviceHandle dev, void* obj)
{
    AMW0x7_DeviceHandle_t module = (AMW0x7_DeviceHandle_t)obj;

    uint8_t c = 0;
    Uart_read(dev,&c,100);

    UtilityBuffer_push(&module->rxDescriptor,c);
}

void AMW0x7_uartErrorInterrupt (Uart_DeviceHandle dev, void* obj)
{
    (void)dev;
    (void)obj;
}

static void initPins (AMW0x7_DeviceHandle_t dev)
{
    if (dev->pinReset != GPIO_PINS_NONE)
    {
        Gpio_config(dev->pinReset, GPIO_PINS_INPUT);
    }
}

static inline void getStingCommand (AMW0x7_Command_t command, char* text)
{
    switch (command)
    {
    case AMW0x7_COMMAND_VERSION:
        strcpy(text,"version");
        break;
    case AMW0x7_COMMAND_NONE:
    default:
        ohiassert(0);
        break;
    }
}

static AMW0x7_Errors_t setCommand (AMW0x7_DeviceHandle_t dev,
                                   AMW0x7_Command_t command,
                                   const char* param,
                                   const char* reply)
{
    char text[128] = {0};
    AMW0x7_Errors_t err = AMW0x7_ERRORS_COMMAND_TIMEOUT;

    // Set text command
    memset(text,0,sizeof(text));
    getStingCommand(command, text);

    // Add parameters
    if (param != NULL)
    {
        strcat(text, " ");
        strcat(text, param);
    }
    strcat(text, AMW0x7_COMMAND_END_LINE);

    // FIXME

    return err;
}

static AMW0x7_Errors_t readCommand (AMW0x7_DeviceHandle_t dev,
                                    AMW0x7_Command_t command,
                                    const char* param,
                                    char* reply)
{
    char text[128] = {0};
    char response[WARCOMEB_AMW0x7_RX_BUFFER+1] = {0};
    uint32_t responseIndex = 0;

    AMW0x7_Errors_t err = AMW0x7_ERRORS_COMMAND_TIMEOUT;

    // Set text command
    memset(text,0,sizeof(text));
    getStingCommand(command, text);

    // Add parameters
    if (param != NULL)
    {
        strcat(text, " ");
        strcat(text, param);
    }
    strcat(text, AMW0x7_COMMAND_END_LINE);

    UtilityBuffer_flush(&dev->rxDescriptor);
    // Send command
    Uart_sendString(dev->device, text);

    // Check module reply...
    uint32_t endTimeout = System_currentTick() + AMW0x7_READ_COMMAND_TIMEOUT;
    while (System_currentTick() < endTimeout)
    {
        if (!UtilityBuffer_isEmpty(&dev->rxDescriptor))
        {
            UtilityBuffer_pull(&dev->rxDescriptor, (uint8_t *)&response[responseIndex]);
            responseIndex++;

            if ((responseIndex > 2) &&
                (memcmp(AMW0x7_COMMAND_DONE, (const char *) &response[responseIndex-2], strlen(AMW0x7_COMMAND_DONE)) == 0))
            {
                err = AMW0x7_ERRORS_NO_ERROR;

                // Copy the module reply back!
                strcpy(reply,response);

                // Delete the command into reply
                char *start = strstr(reply, text);
                char *stop  = start + strlen(text);
                memmove(start, start + strlen(text), strlen(stop) + 1);

                UtilityBuffer_flush(&dev->rxDescriptor);
                break;
            }
        }
    }
    return err;
}

void AMW0x7_init (AMW0x7_DeviceHandle_t dev, AMW0x7_Config_t* config)
{
    ohiassert(config->device != NULL);

    // Initialize the device pointer
    memset(dev, 0, sizeof (AMW0x7_Device_t));
    dev->device   = config->device;
    Uart_setCallbackObject(dev->device, dev);

    // Initialize buffer descriptor
    UtilityBuffer_init(&dev->rxDescriptor, dev->rxBuffer, WARCOMEB_AMW0x7_RX_BUFFER+1);

    dev->pinReset = config->pinReset;

    // Init pins
    initPins(dev);

    // Reset module: hardware reset!
    AMW0x7_reset(dev, AMW0x7_RESETTYPE_HARDWARE);
}

AMW0x7_Errors_t AMW0x7_reset (AMW0x7_DeviceHandle_t dev, AMW0x7_ResetType_t type)
{
    AMW0x7_Errors_t err = AMW0x7_ERRORS_COMMAND_FAIL;

    // Reset internal module status
    dev->isAwake     = TRUE;
    dev->isConnected = FALSE;

    switch (type)
    {
    case AMW0x7_RESETTYPE_HARDWARE:
//        // Configure reset pin
//        Gpio_config(dev->pinReset, GPIO_PINS_OUTPUT);
//        Gpio_set(dev->pinReset);
//        System_delay(2);
//        Gpio_clear(dev->pinReset);
//        System_delay(2);
//        Gpio_config(dev->pinReset,GPIO_PINS_INPUT);
//        System_delay(10);
        break;
    case AMW0x7_RESETTYPE_SOFTWARE:
//        sendCommand(dev,BGX13P_COMMAND_REBOOT);
        break;
    default:
        break;
    }

    return err;
}

AMW0x7_Errors_t AMW0x7_getFirmwareVersion (AMW0x7_DeviceHandle_t dev, char* data)
{
    return readCommand(dev, AMW0x7_COMMAND_VERSION, NULL, data);
}

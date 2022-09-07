/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_21_00_05
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Empty Project
 *
 * Description: An empty project that uses DriverLib. In this project, DriverLib
 * is built from source instead of the usual library.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author:
*******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>


int main(void)
{
    volatile uint32_t ii;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    /* Configuring P1.0 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);//LED1(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);//LED2(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);//LED2(Green)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);//LED2(Blue)

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);

    while (1)
    {
        //button S1 is pressed, the green RGB LED turns on
        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == (uint_fast8_t)(0x00)){
            // LED2(Green)
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);

            // LED1(Red) → LED2(Red)
                       GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
                       /* Delay Loop */
                       for(ii=0;ii<10000;ii++)
                       {
                       }
                       GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                       /* Delay Loop */
                       for(ii=0;ii<10000;ii++)
                       {
                       }
        }

        //S2 is pressed the blue RGB LED
        else if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == (uint_fast8_t)(0x00)){
            // LED2(Red)
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);

            // LED1(Red) → LED2(Red)
                       GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
                       /* Delay Loop */
                       for(ii=0;ii<10000;ii++)
                       {
                       }
                       GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                       /* Delay Loop */
                       for(ii=0;ii<10000;ii++)
                       {
                       }
        }
        else{
            // LED1(Red) → LED2(Red)
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            /* Delay Loop */
            for(ii=0;ii<10000;ii++)
            {
            }
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
            /* Delay Loop */
            for(ii=0;ii<10000;ii++)
            {
            }

            // LED2(Red)
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            /* Delay Loop */
            for(ii=0;ii<10000;ii++)
            {
            }
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        }
    }

}

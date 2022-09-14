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
/*******************************************************************************
 * MSP432 GPIO - Input Interrupt
 *
 * Description: This example demonstrates a very simple use case of the
 * DriverLib GPIO APIs. P1.1 (which has a switch connected to it) is configured
 * as an input with interrupts enabled and P1.0 (which has an LED connected)
 * is configured as an output. When the switch is pressed, the LED output
 * is toggled.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST         P1.0  |---> P1.0 LED
 *            |                  |
 *            |            P1.1  |<--Toggle Switch
 *            |                  |
 *            |                  |
 *
 * Author: Timothy Logan
 ******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>

#include <stdbool.h>

int main(void)
{

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    /* Configuring P1.0 as output and P1.1 (switch) as input */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);


    /* Configuring P1.1 as an input and enabling interrupts */
        //1. Configure the GPIO pin as an input.
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

        //2. Select the edge (clock signal) that triggers the interrupt.
        GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);

        //3. Clear the pin's interrupt flag. This makes sure that no previous interrupts are handled.
        //(This step is not mandatory, but it is good practice to do so.)
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);

        //4. Set the interrupt enable (IE) bit of the specific GPIO pin
        //(enabling the interrupt in the peripheral).
        GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

        //5. Set the interrupt enable (IE) bit of the corresponding interrupt source
        //(enabling the interrupt in the interrupt controller).
        Interrupt_enableInterrupt(INT_PORT1);

    /* Configuring P1.4 as an input and enabling interrupts */
        //1. Configure the GPIO pin as an input.
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);

        //2. Select the edge (clock signal) that triggers the interrupt.
        GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);

        //3. Clear the pin's interrupt flag. This makes sure that no previous interrupts are handled.
        //(This step is not mandatory, but it is good practice to do so.)
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);

        //4. Set the interrupt enable (IE) bit of the specific GPIO pin
        //(enabling the interrupt in the peripheral).
        GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

        //5. Set the interrupt enable (IE) bit of the corresponding interrupt source
        //(enabling the interrupt in the interrupt controller).
        Interrupt_enableInterrupt(INT_PORT1);
    
    //6. Enable interrupts globally (set global interrupt enable (GIE) bit).
    Interrupt_enableMaster();

    /* Going to LPM3 */
    while (1)
    {
        MAP_PCM_gotoLPM3();
    }
}

/* GPIO ISR */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1); //GPIO_PIN(X)
    /* Toggling the output on the LED */
    if(status & GPIO_PIN1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    if(status & GPIO_PIN4)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }

    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

}

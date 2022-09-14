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
 * Description: An empty project that uses DriverLib
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
volatile uint32_t ii;
volatile uint32_t i =0;
int main(void)
{
    i=-1;
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // LED2(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // LED2(Green)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // LED2(Blue)

    //4. Configure pin P2.5 as input (with pull-up resistor)
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);

    //6. Clear the interrupt flag for pin P2.5
    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);

    //7. Enable interrupt for pin P2.5
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);

    //8. Enable interrupt for Port 2
    Interrupt_enableInterrupt(INT_PORT2);

    //9. Enable master interrupt
    Interrupt_enableMaster();

    //10. Forever loop that puts the device to low power mode 3 state.
    while(1)
    {
        PCM_gotoLPM3();
    }
}

//1. Declare an ISR for Port 2 (Hint: PORT2_IRQHandler)
void PORT2_IRQHandler(void)
{
    //2. Declare a local integer variable
    uint32_t status;

    //3. Get interrupt status for Port 2 and store it into the local variable (declared above)
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);


    //5. Check if the global variable is equal to 20 (number of notches on the wheel encoder).
        //o TRUE: Toggle pin P1.0 and reset the local variable
        //o FALSE: Nil
    i=i+1;

                                if(i==0)
                                {
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
                                }
                            if(i==1)
                            {
                                // LED2(BLUE)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
                            }
                            if(i==2)
                            {
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                // LED2(GREEN)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
                            }
                            if(i==3)
                            {
                                // LED2(BLUE)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                // LED2(GREEN)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
                            }
                            if(i==4)
                            {
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
                                // LED2(RED
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
                            }
                            if(i==5)
                            {
                                // LED2(RED)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
                                // LED2(BLUE)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);

                            }
                            if(i==6)
                            {
                                // LED2(BLUE)
                                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                // LED2(RED)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
                                // LED2(GREEN)
                                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
                             }
                            if(i==7){
                                    // LED2(BLUE)
                                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
                                    // LED2(RED)
                                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
                                    // LED2(GREEN)
                                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);

                                    i=-1;
                                }


    //6. Clear the interrupt flag for Port 2 (Hint: use the variable)
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
    //6. Clear the interrupt flag for Port 2 (Hint: use the variable)
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
}


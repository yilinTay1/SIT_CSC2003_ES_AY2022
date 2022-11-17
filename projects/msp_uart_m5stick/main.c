/******************************************************************************
 *
 *               MSP432P401
 *             -----------------
 *            |                 |
 *            |                 |
 *            |     P3.3/UCA0TXD|----> M5Stick
 *            |                 |
 *            |     P3.2/UCA0RXD|<---- M5stick
 *            |                 |
 *
 *******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"
#include "UART_Driver.h"

/* Standard Includes */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//![UART Config]
/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 115200 baud rate. These
 * values were calculated using the online calculator that TI provides at:
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
const eUSCI_UART_Config uartConfig =
    {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        13,
        0,
        37,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION};

const Timer_A_UpModeConfig upConfig =
    {
        TIMER_A_CLOCKSOURCE_ACLK,           // ACLK Clock Source 32.768 Khz
        TIMER_A_CLOCKSOURCE_DIVIDER_32,     // 32.768 Khz / 32 = 1024
        1000,                               // (1/1024) * 2048 = 2s
        TIMER_A_TAIE_INTERRUPT_DISABLE,     // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                    // Clear value
};

/* UART received data */
char uartReceivedData[10];

int main(void)
{
    /* Halting WDT  */
    WDT_A_holdTimer();

    /* Setting DCO (clock) to 24MHz */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /* Configure pins P3.2 and P3.3 in UART mode. */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                                               GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    /* Configuring UART Module */
    UART_initModule(EUSCI_A2_BASE, &uartConfig);
    /* Enable UART module */
    UART_enableModule(EUSCI_A2_BASE);

    /* Configuring TimerA Module */
    Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);

    /* Enabling interrupts and starting the timer */
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA1_0);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);

    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA2);

    /* Enabling MASTER interrupts */
    Interrupt_enableMaster();
    uartReceivedData[0] = 0;

    UART_Printf(EUSCI_A2_BASE, "Starting UART\n\r");
    while (1)
    {
        PCM_gotoLPM3InterruptSafe();
    }
}

/* Timer for UART Communctions */
void TA1_0_IRQHandler(void)
{
    char s[100] = "1,5,2,6,Embedded is the best";
    strcat(s, "\n\r");
    UART_Printf(EUSCI_A2_BASE, s);
}

/* Interrupt for UART */
void EUSCIA2_IRQHandler(void)
{
    unsigned char c;
    c = UART_receiveData(EUSCI_A2_BASE);
    if (c == '#')
    {
        int x = atoi(strtok(received, ","));
        int y = atoi(strtok(NULL, ","));
        uartReceivedData[0] = 0;
    }
    else
    {
        strcat(uartReceivedData, (const char *)&c);
    }
}

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ESP8266.h>
#include <UART_Driver.h>

#include <stdint.h>
#include <stdbool.h>

//running at 3Mhz and the UART configured to the baud rate of 115200bps, 
//with one stop bit and odd parity

//https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
eUSCI_UART_ConfigV1 UART0Config =
{
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,
     1,// UCBR, clockPrescalar 
     10,// UCBRF, firstModReg  
     0,// UCBRS, secondModReg  
     EUSCI_A_UART_ODD_PARITY,// Odd parity
     EUSCI_A_UART_LSB_FIRST,// LSB First
     EUSCI_A_UART_ONE_STOP_BIT,// One stop bit
     EUSCI_A_UART_MODE,
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION// Oversampling
	 EUSCI_A_UART_8_BIT_LEN// Data length is 8 bits
};

int main(void)
{
    /* Halting WDT  */
    WDT_A_holdTimer();

    /* Set P1.0 as Output, LED1 will turn on */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Selecting P1.2 and P1.3 in UART mode */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configuring UART Module */
    UART_initModule(EUSCI_A0_BASE, &UART0Config);

    /* Enable UART module */
    UART_enableModule(EUSCI_A0_BASE);

    /* Enabling interrupts (Rx) */
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA0);
    Interrupt_enableMaster();

    while(1)
    {
        PCM_gotoLPM3InterruptSafe();
    }
}


void EUSCIA0_IRQHandler(void)
{
    unsigned char character = 0;

    character = UART_receiveData(EUSCI_A0_BASE);
//LED1 will turn on when any of the keys from ‘a’ to ‘m’ is pressed.
//the upper-caps equivalent (‘A’ to ‘M’) of the character would be displayed on the serial console
    if (character == 'a')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'A');
    }
	
	if (character == 'b')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'B');
    }
	if (character == 'c')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'C');
    }
	
	if (character == 'd')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'D');
    }
	if (character == 'e')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'E');
    }
	
	if (character == 'f')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'F');
    }
	if (character == 'g')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'G');
    }
	
	if (character == 'h')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'H');
    }
    if (character == 'i')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'I');
    }
	
	if (character == 'j')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'J');
    }
	if (character == 'k')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'K');
    }
	
	if (character == 'l')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'L');
    }
	if (character == 'm')
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'M');
    }
	
	//turn off LED1 and display the character ‘Z’ when the character ‘z’ is keyed in.
	if (character == 'z')
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        UART_transmitData(EUSCI_A0_BASE, 'Z');
    }
}

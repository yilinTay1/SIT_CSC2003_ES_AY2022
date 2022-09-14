/**
 * Authors: Tay Yi Lin, Lua Zhi Zhan
 */
#include "driverlib.h"
#include <stdint.h>

int32_t counter;

void offAllLED2Pins(void);

int main(void)
{
    /* Stop Watchdog  */
    WDT_A_holdTimer();

    // Initialize global counter variable
    counter = 0;

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // LED2(Red)
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // LED2(Green)
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // LED2(Blue)
    offAllLED2Pins();                             // Off all LED2 color pins

    // Configure pin P2.5 as input (with pull-up resistor)
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);

    // Clear the interrupt flag for pin P2.5
    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);

    // Enable interrupt for pin P2.5
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);

    // Enable interrupt for Port 2
    Interrupt_enableInterrupt(INT_PORT2);

    // Enable master interrupt
    Interrupt_enableMaster();

    // Forever loop that puts the device to low power mode 3 state.
    while (1)
    {
        PCM_gotoLPM3();
    }
}

/**
 * Off all LED2 color pins
 */
void offAllLED2Pins(void)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void PORT2_IRQHandler(void)
{
    counter++;

    switch (counter)
    {
    case 0:
        // Off all LED2 color pins
        offAllLED2Pins();
        break;
    case 1:
        // On LED2(Blue) only
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    case 2:
        // On LED2(Green) only
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    case 3:
        // On LED2(Green + Blue) only
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    case 4:
        // On LED2(Red) only
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    case 5:
        // On LED2(Red + Blue) only
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    case 6:
        // On LED2(Red + Green) only
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    case 7:
        // On LED2(Red + Green + Blue)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        counter = -1; // reset counter
        break;
    }

    // Get status and clear status interrupt flag
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
}

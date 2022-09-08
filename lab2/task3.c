/**
 * Authors: Tay Yi Lin, Lua Zhi Zhan
 */

/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>

#define CYCLE ((uint32_t)(50000))

int main(void)
{
    uint32_t i;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    // Set required ports and pins as output
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // LED1(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // LED2(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // LED2(Green)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // LED2(Blue)

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);

    while (1)
    {
        // button S1 is pressed, green LED turns on
        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == (uint_fast8_t)(0x00))
        {
            // On LED2(Green)
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        }

        // button S2 is pressed, blue RGB turns on
        else if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == (uint_fast8_t)(0x00))
        {
            // On LED2(Blue)
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        }

        // Toggle LED1 red light
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        for (i = 0; i < CYCLE; i++)
        {
        }
        // Toggle LED2 red light
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);

        // Off LED2 green and blue lights
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }
}

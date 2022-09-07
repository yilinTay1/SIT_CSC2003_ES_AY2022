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
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // LED1(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // LED2(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // LED2(Green)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // LED2(Blue)

    while (1)
    {
        // LED1(Red) → LED2(Red)
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }

        // LED2(Red)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }

        // LED1(Red) → LED2(Green)
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }

        // LED2(Red)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }

        // LED1(Red) → LED2(Blue)
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }

        // LED2(Red)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        /* Delay Loop */
        for (ii = 0; ii < 100000; ii++)
        {
        }
    }
}

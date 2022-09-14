/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

uint32_t counter;

int main(void)
{
    /* Stop Watchdog */
    MAP_WDT_A_holdTimer();
    counter = 0;

    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);

    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);
    MAP_Interrupt_enableInterrupt(INT_PORT2);
    MAP_Interrupt_enableMaster();

    while (1)
    {
        MAP_PCM_gotoLPM3();
    }
}

/* GPIO ISR */
void PORT2_IRQHandler(void)
{
    uint32_t status;
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    counter++;
    if (counter == 20)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        status = 0;
    }
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
}

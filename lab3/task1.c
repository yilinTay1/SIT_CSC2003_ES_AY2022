#include "driverlib.h"

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
    // 1. Configure the GPIO pin as an input.
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    // 2. Select the edge (clock signal) that triggers the interrupt.
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);

    // 3. Clear the pin's interrupt flag. This makes sure that no previous interrupts are handled.
    //(This step is not mandatory, but it is good practice to do so.)
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);

    // 4. Set the interrupt enable (IE) bit of the specific GPIO pin
    //(enabling the interrupt in the peripheral).
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    // 5. Set the interrupt enable (IE) bit of the corresponding interrupt source
    //(enabling the interrupt in the interrupt controller).
    Interrupt_enableInterrupt(INT_PORT1);

    /* Configuring P1.4 as an input and enabling interrupts */
    // 1. Configure the GPIO pin as an input.
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);

    // 2. Select the edge (clock signal) that triggers the interrupt.
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);

    // 3. Clear the pin's interrupt flag. This makes sure that no previous interrupts are handled.
    //(This step is not mandatory, but it is good practice to do so.)
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);

    // 4. Set the interrupt enable (IE) bit of the specific GPIO pin
    //(enabling the interrupt in the peripheral).
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    // 5. Set the interrupt enable (IE) bit of the corresponding interrupt source
    //(enabling the interrupt in the interrupt controller).
    Interrupt_enableInterrupt(INT_PORT1);

    // 6. Enable interrupts globally (set global interrupt enable (GIE) bit).
    Interrupt_enableMaster();

    /* Going to LPM3 */
    while (1)
    {
        PCM_gotoLPM3();
    }
}

/* GPIO ISR */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1); // GPIO_PIN(X)
    /* Toggling the output on the LED */
    if (status & GPIO_PIN1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    if (status & GPIO_PIN4)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }

    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
}

#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
volatile uint32_t ii;
volatile uint32_t i = 0;
int main(void)
{
    i = -1;
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // LED2(Red)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // LED2(Green)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // LED2(Blue)

    // 4. Configure pin P2.5 as input (with pull-up resistor)
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);

    // 6. Clear the interrupt flag for pin P2.5
    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);

    // 7. Enable interrupt for pin P2.5
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);

    // 8. Enable interrupt for Port 2
    Interrupt_enableInterrupt(INT_PORT2);

    // 9. Enable master interrupt
    Interrupt_enableMaster();

    // 10. Forever loop that puts the device to low power mode 3 state.
    while (1)
    {
        PCM_gotoLPM3();
    }
}

// 1. Declare an ISR for Port 2 (Hint: PORT2_IRQHandler)
void PORT2_IRQHandler(void)
{
    // 2. Declare a local integer variable
    uint32_t status;

    // 3. Get interrupt status for Port 2 and store it into the local variable (declared above)
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);

    // 5. Check if the global variable is equal to 20 (number of notches on the wheel encoder).
    // o TRUE: Toggle pin P1.0 and reset the local variable
    // o FALSE: Nil
    i = i + 1;

    if (i == 0)
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }
    if (i == 1)
    {
        // LED2(BLUE)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }
    if (i == 2)
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        // LED2(GREEN)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }
    if (i == 3)
    {
        // LED2(BLUE)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        // LED2(GREEN)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }
    if (i == 4)
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        // LED2(RED
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }
    if (i == 5)
    {
        // LED2(RED)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        // LED2(BLUE)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }
    if (i == 6)
    {
        // LED2(BLUE)
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        // LED2(RED)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        // LED2(GREEN)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }
    if (i == 7)
    {
        // LED2(BLUE)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        // LED2(RED)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        // LED2(GREEN)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);

        i = -1;
    }

    // 6. Clear the interrupt flag for Port 2 (Hint: use the variable)
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
    // 6. Clear the interrupt flag for Port 2 (Hint: use the variable)
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
}

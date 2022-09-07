#include "driverlib.h"

#define WAIT_INIT_MULTI ((uint32_t)(2))           // Multiplier for longer busy wait
#define WAITCYCLES_BASE ((uint32_t)(10000))       // Base value for the wait cycles calculation
#define WAIT_CYCLES ((uint32_t)(WAITCYCLES_BASE)) // Constant define for the initial number of waiting cycles

// Global variable defining the number of cycles of the busy loop
uint32_t g_waitcycles = WAIT_CYCLES * WAIT_INIT_MULTI;

void pressed()
{
    // TODO: Implement debounce for both buttons

    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == ((uint8_t)0x00))
    {
        GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }

    /* Toggle LED2 on Button2(S2) pressed */
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == ((uint8_t)0x00))
    {
        GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stopping the Watchdog Timer

    uint32_t count = 0; // Simple counter variable

    /* Button1(S1) and LED1 */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    /*Button2(S2) and LED2 */
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);

    while (1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        for (count = 0; count < g_waitcycles; count++) // Busy Loop for Delay
        {
            pressed();
        }
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }
}

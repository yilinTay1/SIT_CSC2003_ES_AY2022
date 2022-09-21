#include "driverlib.h"

Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,     // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_3, // SMCLK/3 = 1MHz
        5000,                          // (1/1Mhz) * 5000 = 5ms
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        500 // Reset value to 500
            // Duty cycle = 500/5000 = 10%
};

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    // To output an input signal from PWM pin
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Set peripheral module function in the output direction for the selected pin
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);

    // Set button 2 as input pin and enable interrupt
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    /* Configuring Timer_A to have a period of approximately 200ms and an initial duty cycle of 10% of that (1000 ticks)  */
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);

    /* Enabling interrupts and starting the watchdog timer */
    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();

    /* Sleeping when not in use */
    while (1)
    {
        PCM_gotoLPM0();
    }
}

/* Port1 ISR - This ISR will progressively step up the duty cycle of the PWM on a button press */
void PORT1_IRQHandler(void)
{
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

    if (status & GPIO_PIN4)
    {
        // 5000 * 90%  = 4500
        if (pwmConfig.dutyCycle == 4500)
            pwmConfig.dutyCycle = 500;
        else
            pwmConfig.dutyCycle += 500;

        Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
}

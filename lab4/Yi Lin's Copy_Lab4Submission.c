// Configure the Timer_A module to create a precision 
// PWM with an adjustable duty cycle. 
// The PWM period is 5ms (200Hz) and is output on P5.6. 
// The initial duty cycle of the PWM is 10%. 
// However, when the button P1.4 is pressed (no debouncing needed), 
// the duty cycle is increased by 10%. 
// Once the duty cycle reaches 90%, the duty cycle is reset to 10% 

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig =
{
		//The PWM period is 5ms (200Hz)Hz is in Seconds
        TIMER_A_CLOCKSOURCE_SMCLK, // SMCLK = 3MHz
        TIMER_A_CLOCKSOURCE_DIVIDER_5, // 3MHz/5 (DIVIDER_5) = 600 KHz
        3000, //PWM. 1/600 KHz * (Find- 3000) = 5ms (0.005S)
		
		//initial duty cycle of the PWM is 10%. 
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        300 // 3000 * 10% = 300
};

int main(void)
{
    /* Halting the watchdog */
    MAP_WDT_A_holdTimer();
	
	// To output an input signal from PWM pin
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);


    /* P2.4 as peripheral output for PWM and P1.1 for button interrupt */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
	
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    /* Configuring Timer_A to have a period of approximately 80ms and an initial duty cycle of 10% of that (1000 ticks)  */
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

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
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
	
    if (status & GPIO_PIN1)
    {
		//Once the duty cycle reaches 90%, the duty cycle is reset to 10% 
        if(pwmConfig.dutyCycle == 2700) // 3000 * 90% = 2700
            pwmConfig.dutyCycle = 300; // 3000 * 10% = 300
        else
			//duty cycle is increased by 10%
            pwmConfig.dutyCycle += 300;

        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    }
}

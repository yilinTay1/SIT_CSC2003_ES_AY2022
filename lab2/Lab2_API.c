#include "driverlib.h"

void main(void)
{
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stopping the Watchdog Timer

  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
  GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); //  pin is on high voltage level when the button is not pressed (open circuit)
 
  while (1)
  {
    /*S1 button will toggle LED1*/
    // pin is on low voltage level if the button is pressed (short circuit)
    // Bit = 0: The input is low (InputPinWithPullUpResistor)
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == ((uint8_t)0x00)) // P1.1(S1) S1 button press
      GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    for (count = 0; count < g_waitcycles; count++)
    {
    }
  }
}
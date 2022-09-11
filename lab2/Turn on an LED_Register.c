#include “msp.h”
void main(void)
{
    /* Input switch */
    P1->SEL1 &= ~2; /* configure P1.1 as simple I/O */
    P1->SEL0 &= ~2;
    P1->DIR &= ~2; /* P1.1 set as input */
    P1->REN |= 2;  /* P1.1 pull resistor enabled */
    P1->OUT |= 2;  /* (If PxOUT bit = 1: It is a pull-up) Pull up/down is selected by P1->OUT*/

    /* Output LED */
    P2->SEL1 &= ~1; /* configure P2.0 as simple I/O */
    P2->SEL0 &= ~1;
    P2->DIR |= 1; /* P2.0 set as output pin */

    while (1)
    {
        if (P1->IN & 2)    /* use SW 1 to control red LED */
            P2->OUT &= ~1; /* turn off P2.0 red LED when SW is not pressed */
        else
            P2->OUT |= 1; /* (Bit = 1: The output is high) turn on P2.0 red LED when SW is pressed */
    }
}

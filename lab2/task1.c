#include "driverlib.h"

#define WAIT_INIT_MULTI ((uint32_t)(15))          // Multiplier for longer busy wait
#define WAITCYCLES_BASE ((uint32_t)(10000))       // Base value for the wait cycles calculation
#define WAIT_CYCLES ((uint32_t)(WAITCYCLES_BASE)) // Constant define for the initial number of waiting cycles

#define REGBASEADR ((uint32_t)(0x40004C00))  // Base addr. of Port 1 configuration register
#define REGOFS_SEL0 ((uint32_t)(0x0000000A)) // Addr. Offset for Select0-Register in Port 1
#define REGOFS_SEL1 ((uint32_t)(0x0000000C)) // Select1 offset in Port 1 conf. reg.
#define REGOFS_DIR ((uint32_t)(0x00000004))  // Direction offset in Port 1 conf. reg.
#define REGOFS_OUTV ((uint32_t)(0x00000002)) // Output Value offset in Port 1 conf. reg.

#define BIT0 (uint16_t)(0x0001)

// Global variable defining the number of cycles of the busy loop
uint32_t g_waitcycles = WAIT_CYCLES * WAIT_INIT_MULTI;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stopping the Watchdog Timer

    uint32_t count = 0; // Simple counter variable

    (*((volatile uint16_t *)(REGBASEADR + REGOFS_SEL0))) &= ~(BIT0); // Set bit 0 of Select 0 register to 0
    (*((volatile uint16_t *)(REGBASEADR + REGOFS_SEL1))) &= ~(BIT0); // Set bit 0 of Select 1 register to 0
    (*((volatile uint16_t *)(REGBASEADR + REGOFS_DIR))) |= (BIT0);   // Set bit 0 of Direction register to 1

    while (1)
    {
        (*((volatile uint16_t *)(REGBASEADR + REGOFS_OUTV))) ^= (BIT0); // Toggle Output State of P1.0

        for (count = 0; count < g_waitcycles; count++) // Busy Loop for Delay
        {
        }
    }
}

/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
 * Generate calibration data for both front sensors.
 * this version requires the sample time to be set to give the required 15us
 * rather than using a coretimer() delay.
 * ADC control clock = 25ns  (clockdiv = 3, 8.33ns SYSCLK)
 * ADC clock div = 2 gives TAD = 100ns
 * Sample time 150 = 15us 
 * at 10 bit conversion gives 61.4 ksps = 16.3 us.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include "sensor.h"
#include "button.h"      // button prototypes
#include "global.h"

// *****************************************************************************
// *****************************************************************************
void TIMER4_InterruptSvcRoutine(uint32_t status, uintptr_t context)
{
    static uint8_t i = 0;
    tick = true;
    if (i++ >200) {
        led_right_Toggle();
        led_left_Toggle();
        i=0;
    }
}
// Section: Main Entry Point
// *****************************************************************************


// *****************************************************************************

int main ( void )
{
    uint8_t i;
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TMR4_CallbackRegister(TIMER4_InterruptSvcRoutine, (uintptr_t) NULL);
    TMR4_Start();
    printf("\r\nMENG the Mirthless has comms ....\r\n");
    for (i=0; i<200; i+=10) {
        button_right_wait();
        printf("%3d %5d  %5d\r\n",i,read_WS1(), read_WS6());
    } 
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/


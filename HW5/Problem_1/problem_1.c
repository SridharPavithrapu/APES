/*************************************************************************************
*
* FileName        :    problem_1.c
* Description     :    This file is example for creating driver library in TIVA board.
*
* File Author Name:    Sridhar Pavithrapu
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


/* Global variables */

/* System clock rate in Hz */
uint32_t g_ui32SysClock;



/*** Function Definitions ***/

/**
​* ​ ​ @brief​ : Initialize the LED pins
​* ​ ​
​*
​* ​ ​ @param​ ​ None
​*
​* ​ ​ @return​ ​None
​*/
void LED_Initialize()
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    /* PN0 and PN1 are used for USER LEDs. */
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    MAP_GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1,
                             GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

    /* Default the LEDs to OFF. */
    MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
}


/**
​* ​ ​ @brief​ : Initialize the UART
​* ​ ​
​*
​* ​ ​ @param​ ​ None
​*
​* ​ ​ @return​ ​None
​*/
void UART0_Initialize()
{

    /* Enable the GPIO Peripheral used by the UART. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /* Enable UART0 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Configure GPIO Pins for UART mode. */
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Initialize the UART for console I/O. */
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}

/**
​* ​ ​ @brief​ : Main function demonstrating the creation of driver
*               library in Tiva board.
​* ​ ​
​*
​* ​ ​ @param​ ​ None
​*
​* ​ ​ @return​ ​integer status
​*/
int main(void)
{

    /* Set the clocking to run directly from the crystal at 120MHz. */
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);

    uint32_t count = 0;
    va_list structCount;
    structCount.__ap = &count;

    /* Initializing the LED */
    LED_Initialize();
    /* Initializing the UART */
    UART0_Initialize();

    /* Logging the string */
    UARTprintf("Project for: Sridhar Pavithrapu 04/06/2018\n");

    while(1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0,1);
        UARTvprintf("Count is: %d\n",structCount);
        count++;

        /* Delay for a bit. */
        SysCtlDelay(g_ui32SysClock / 4 / 3);


        GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0,0);

        /* Delay for a bit. */
        SysCtlDelay(g_ui32SysClock / 4 / 3);
    }

	return 0;
}

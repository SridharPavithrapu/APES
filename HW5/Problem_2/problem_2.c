/*************************************************************************************
*
* FileName        :    problem_2.c
* Description     :    This file is example for creating tasks in TIVA board
*                       using FreeRTOS.
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
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Macros section */

/* Delay of 2Hz */
#define AUTO_RELOAD_TIMER_PERIOD_FIRST_TASK pdMS_TO_TICKS( 250 )
/* Delay of 4Hz */
#define AUTO_RELOAD_TIMER_PERIOD_SECOND_TASK pdMS_TO_TICKS( 125 )
#define TASK_BUFFER 1024



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
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /* PN0,PN1,PF0 and PF4 are used for USER LEDs. */
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    MAP_GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1,
                             GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
    MAP_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
                                 GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

    /* Default the LEDs to OFF. */
    MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0);
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
​* ​ ​ @brief​ : Blinking LED0 signal handler
​* ​ ​
​*
​* ​ ​ @param​ ​ xTimer gives information about time
​*
​* ​ ​ @return​ ​None
​*/
static void led0_blink( TimerHandle_t xTimer )
{
    static uint8_t led0_state = 0;
    /* Toggling LED0 */
    GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0,led0_state);
    led0_state = !led0_state;
}

/**
​* ​ ​ @brief​ : Blinking LED1 signal handler
​* ​ ​
​*
​* ​ ​ @param​ ​ xTimer Gives information about time
​*
​* ​ ​ @return​ ​None
​*/
static void led1_blink( TimerHandle_t xTimer )
{
    static uint8_t led1_state = 0;

    /* Toggling LED1 */
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,led1_state);
    led1_state = !led1_state;
}

/**
​* ​ ​ @brief​ : Task-1 definition
​* ​ ​
​*
​* ​ ​ @param​ ​ pvParameters Parameters for task1
​*
​* ​ ​ @return​ ​None
​*/
void task1( void *pvParameters )
{
    TimerHandle_t xAutoReloadTimer1;

    UARTprintf("In Task-1 \n");

    /* Create the auto-reload timer, to blink LED0. */
    xAutoReloadTimer1 = xTimerCreate(
                            /* Text name for the software timer - not used by FreeRTOS. */
                            "AutoReload",
                            /* The software timer's period in ticks. */
                            AUTO_RELOAD_TIMER_PERIOD_FIRST_TASK,
                            /* Setting uxAutoRealod to pdTRUE creates an auto-reload timer. */
                            pdTRUE,
                            /* This example does not use the timer id. */
                            0,
                            /* The callback function to be used by the software timer being created. */
                            led0_blink );

    /* Check the software timer got created. */
    if( ( xAutoReloadTimer1 != NULL ))
    {
        xTimerStart( xAutoReloadTimer1, 0 );
    }

    for(;;);

    /* Deleting the task */
    vTaskDelete(NULL);
}

/**
​* ​ ​ @brief​ : Task-2 definition
​* ​ ​
​*
​* ​ ​ @param​ ​ pvParameters Parameters for task1
​*
​* ​ ​ @return​ ​None
​*/
void task2( void *pvParameters )
{
    TimerHandle_t xAutoReloadTimer2;

    UARTprintf("In Task-2 \n");

    /* Create the auto-reload timer, to blink LED1. */
    xAutoReloadTimer2 = xTimerCreate(
                            /* Text name for the software timer - not used by FreeRTOS. */
                            "AutoReload",
                            /* The software timer's period in ticks. */
                            AUTO_RELOAD_TIMER_PERIOD_SECOND_TASK,
                            /* Setting uxAutoRealod to pdTRUE creates an auto-reload timer. */
                            pdTRUE,
                            /* This example does not use the timer id. */
                            0,
                            /* The callback function to be used by the software timer being created. */
                            led1_blink );

    /* Check the software timer got created. */
    if( ( xAutoReloadTimer2 != NULL ))
    {
        xTimerStart( xAutoReloadTimer2, 0 );
    }

    for(;;);

    /* Deleting the task */
    vTaskDelete(NULL);
}

/**
​* ​ ​ @brief​ : Main function demonstrating the creating tasks
*               using FreeRTOS in Tiva board.
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


    /* Initializing the LED */
    LED_Initialize();
    /* Initializing the UART */
    UART0_Initialize();

    UARTprintf("Problem-2\n");

    /* Creating task-1 */
    xTaskCreate(task1, "Task-1", TASK_BUFFER, NULL, 1, NULL);

    /* Creating task-2 */
    xTaskCreate(task2, "Task-2", TASK_BUFFER, NULL, 1, NULL);

    /* Starting the scheduler */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
    line will never be reached.  If the following line does execute, then
    there was insufficient FreeRTOS heap memory available for the idle and/or
    timer tasks to be created.  See the memory management section on the
    FreeRTOS web site for more details. */
    for(;;);

    return 0;
}

/*************************************************************************************
*
* FileName        :    problem_3.c
* Description     :    This file is example for creating tasks and example
*                       of using queue and event groups in TIVA board
*                       using FreeRTOS.
*
* File Author Name:    Sridhar Pavithrapu
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
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
#include "queue.h"
#include "event_groups.h"


/* Macros section */

/* Delay of 2Hz */
#define AUTO_RELOAD_TIMER_PERIOD_FIRST_TASK pdMS_TO_TICKS( 250 )
/* Delay of 4Hz */
#define AUTO_RELOAD_TIMER_PERIOD_SECOND_TASK pdMS_TO_TICKS( 125 )
/* Event bit 0, which is set by a task. */
#define TOGGLE_LED ( 1UL << 0UL )
/* Event bit 1, which is set by a task. */
#define LOG_STRING ( 1UL << 1UL )

#define BUFFER 500
#define TASK_BUFFER 1024


/* Global variables */

/* System clock rate in Hz */
uint32_t g_ui32SysClock;
/* Handle for queue */
QueueHandle_t xQueue;
/* Handle for event group */
EventGroupHandle_t xEventGroup;
uint8_t led_event;
uint8_t string_event;


/***Global Structures ***/

/*
​* ​ ​ @brief   ​ : Structure for the string info
​*  ​ @contents : tick_string -> text string
*               string_length -> length of the string
​*/
typedef struct
{
    char tick_string[BUFFER];
    uint8_t string_length;
} Data_t;



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
void UART0_Initialize(){

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
static void toggle_led( TimerHandle_t xTimer )
{
    led_event = 1;
}

/**
​* ​ ​ @brief​ : Logging string signal handler
​* ​ ​
​*
​* ​ ​ @param​ ​ xTimer Gives information about time
​*
​* ​ ​ @return​ ​None
​*/
static void log_string( TimerHandle_t xTimer )
{
    string_event = 1;
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

    led_event = 0;

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
                            toggle_led );

    /* Check the software timer got created. */
    if( ( xAutoReloadTimer1 != NULL ))
    {
        xTimerStart( xAutoReloadTimer1, 0 );
    }

    for(;;)
    {
        if(led_event == 1)
        {
            /* Generating toggle led event */
            xEventGroupSetBits( xEventGroup, TOGGLE_LED );
            led_event = 0;
        }
    }

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

    /* Create the auto-reload timer, to log string. */
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
                            log_string );

    /* Check the software timer got created. */
    if( ( xAutoReloadTimer2 != NULL ))
    {
        xTimerStart( xAutoReloadTimer2, 0 );
    }

    for(;;)
    {
        if(string_event == 1)
        {
            Data_t var;
            char local_string[BUFFER];

            sprintf(local_string,"Task-2 count is: %d\n",xTaskGetTickCount());
            var.string_length = strlen(local_string);
            strncpy(var.tick_string,local_string,var.string_length);
            BaseType_t xStatus = xQueueSendToBack( xQueue, &var, portMAX_DELAY );

            /* Generating event for logging string */
            xEventGroupSetBits( xEventGroup, LOG_STRING );
            string_event = 0;
        }
    }

    /* Deleting the task */
    vTaskDelete(NULL);

}

/**
​* ​ ​ @brief​ : Task-3 definition
​* ​ ​
​*
​* ​ ​ @param​ ​ pvParameters Parameters for task1
​*
​* ​ ​ @return​ ​None
​*/
void task3( void *pvParameters )
{
    UARTprintf("In Task-3 \n");

    EventBits_t xEventGroupValue;
    const EventBits_t xBitsToWaitFor = ( TOGGLE_LED | LOG_STRING);
    for( ;; )
    {
        /* Block to wait for event bits to become set within the event group. */
        xEventGroupValue = xEventGroupWaitBits( /* The event group to read. */
                                xEventGroup,
                                /* Bits to test. */
                                xBitsToWaitFor,
                                /* Clear bits on exit if the
                                unblock condition is met. */
                                pdTRUE,
                                /* Don't wait for all bits. This
                                parameter is set to pdTRUE for the
                                second execution. */
                                pdFALSE,
                                /* Don't time out. */
                                portMAX_DELAY );

        /* Toggle LED event set. */
        if( ( xEventGroupValue & TOGGLE_LED ) != 0 )
        {
            static uint8_t led0_state = 0;
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0,led0_state);
            led0_state = !led0_state;
        }
        /* Log string event set. */
        if( ( xEventGroupValue & LOG_STRING ) != 0 )
        {
            Data_t var;
            char string_received[500];
            memset(string_received,'\0',sizeof(string_received));
            BaseType_t xStatus = xQueueReceive( xQueue, &var, portMAX_DELAY );
            strncpy(string_received, var.tick_string, var.string_length);
            UARTprintf(string_received);
        }
    }
}

/**
​* ​ ​ @brief​ : Main function demonstrating the creating tasks
*            using queues and event groups in FreeRTOS of Tiva board.
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

    UARTprintf("Problem-3\n");

    /* Before an event group can be used it must first be created. */
    xEventGroup = xEventGroupCreate();

    /* The queue is created to hold a maximum of 5 values, each of which is
    large enough to hold a variable of type Data_t. */
    xQueue = xQueueCreate( 5, sizeof( Data_t ) );

    if( xQueue != NULL )
    {
        /* Creating task-1 */
        xTaskCreate(task1, "Task-1", TASK_BUFFER, NULL, 1, NULL);

        /* Creating task-2 */
        xTaskCreate(task2, "Task-2", TASK_BUFFER, NULL, 1, NULL);

        /* Creating task-3 */
        xTaskCreate(task3, "Task-3", TASK_BUFFER, NULL, 1, NULL);

        /* Starting the scheduler */
        vTaskStartScheduler();

    }
    else
    {
        UARTprintf("Error in creating queue\n");
    }

    /* If all is well, the scheduler will now be running, and the following
    line will never be reached.  If the following line does execute, then
    there was insufficient FreeRTOS heap memory available for the idle and/or
    timer tasks to be created.  See the memory management section on the
    FreeRTOS web site for more details. */
    for(;;);

    return 0;
}

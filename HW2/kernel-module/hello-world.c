/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file kernel_timer.c 
* @brief  Includes function declartions for creating kernel module 
*	along with kernel timer. 
* @author Sridhar Pavithrapu 
* @date January 28 2018 
**/

/* Headers Section */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sridhar Pavithrapu");
MODULE_DESCRIPTION("A simple kernel module with demonstartion to kernel timer");
MODULE_VERSION("1.0");

static unsigned int time_interval = 500;
static char *name_string = "default";
static unsigned int timer_count=0;
struct timer_list g_timer;


/** 
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 **/

module_param(time_interval, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(time_interval, "An integer");
module_param(name_string, charp, 0000);
MODULE_PARM_DESC(name_string, "A character string");

/*** Function Definitions ***/

/**
​* ​ ​ @brief​ : Timer handler for printing the timer count and name
​**/

void timer_handler(unsigned long data)
{
	/* Incrementing the count value */
	timer_count++;

	printk(KERN_INFO "In timer_handler with name: %s, and count :%d\n", name_string,timer_count);
    	
	/* Restarting the timer */
    	mod_timer( &g_timer, jiffies + msecs_to_jiffies(time_interval));
 
}

/**
​* ​ ​ @brief​ : Initilaises the kernel module and kernel timer
​*
​* ​ ​ Returns a status code of kernel module
​*
​* ​ ​ @return​ successful intialization of kernel module
​**/

static int __init kernel_module_init(void)
{
	int status;
	printk(KERN_INFO "In kernel module initalization\n=============\n");
	printk(KERN_INFO "Given timer count: %d\n", time_interval);
	printk(KERN_INFO "Given name_string: %s\n", name_string);

	/*Starting the timer.*/
    	setup_timer(&g_timer, timer_handler, 0);
    	status = mod_timer( &g_timer, jiffies + msecs_to_jiffies(time_interval));
	if(status){
		printk(KERN_INFO "Error in mod_timer");
	}
	return 0;
}

/**
​* ​ ​ @brief​ : Exiting the kernel module
​**/

static void __exit kernel_module_exit(void)
{
	int status;
	printk(KERN_INFO "In kernel module exit\n");
	status = del_timer(&g_timer);
	if(status){
		printk(KERN_WARNING "Timer is still in use\n");
	}
}

module_init(kernel_module_init);
module_exit(kernel_module_exit);

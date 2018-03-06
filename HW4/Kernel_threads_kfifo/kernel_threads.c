/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file kernel_threads.c 
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
#include <linux/kthread.h>  // for threads
#include <linux/sched.h>  // for task_struct
#include <linux/time.h>   // for using jiffies 


/* Module description */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sridhar Pavithrapu");
MODULE_DESCRIPTION("A simple kernel module with demonstration of kernel threads with kfifo");
MODULE_VERSION("1.0");


static struct task_struct *thread1;

static struct task_struct *thread2;


/*** Function Definitions ***/

/**
​ * ​ ​ @brief​ : Timer handler for printing the timer count and name.
 *
 * ​ ​ @param​ ​: data for any arguments passed 
​ *
​ * ​ ​ @return​ : None
​**/

int first_thread_fn() {

	printk(KERN_INFO "In thread1");
	
	return 0;
}

int second_thread_fn() {

	printk(KERN_INFO "In thread2");

	return 0;
}

/**
​* ​ ​ @brief​ : Initilaises the kernel module and kernel timer
​*
​* ​ ​ Returns a status code of kernel module
​*
​* ​ ​ @return​ successful intialization of kernel module
​**/

static int __init thread_init(void){
	
	char  first_thread_name[8]="thread1";
	char  second_thread_name[8]="thread2";
	
	printk(KERN_INFO "In thread_init function");
	
	thread1 = kthread_create(first_thread_fn,NULL,first_thread_name);
	if((thread1))
	{
		printk(KERN_INFO "First thread created");
		wake_up_process(thread1);
	}
	
	thread2 = kthread_create(second_thread_fn,NULL,second_thread_name);
	if((thread2))
	{
		printk(KERN_INFO "Second thread created");
		wake_up_process(thread2);
	}

	return 0;
}

/**
​ * ​ ​ @brief​ : Exiting the kernel module.
 *
 * ​ ​ @param​ ​: None
​ *
​ * ​ ​ @return​ : None
​**/

static void __exit thread_exit(void){
	
	int ret;
	ret = kthread_stop(thread1);
	if(!ret)
		printk(KERN_INFO "First thread stopped");
	
	ret = kthread_stop(thread2);
	if(!ret)
		printk(KERN_INFO "Second thread stopped");
}

module_init(thread_init);
module_exit(thread_exit);

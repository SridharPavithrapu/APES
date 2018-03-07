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
* @brief  Includes function declarations processes communicationg using kfifo.
* @author Sridhar Pavithrapu 
* @date March 6 2018 
**/

/* Headers Section */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/timer.h>
#include <linux/kthread.h>  
#include <linux/sched.h>  
#include <linux/time.h>   
#include <linux/proc_fs.h>
#include <linux/kfifo.h>
#include <linux/hrtimer.h>
#include <linux/delay.h> 
#include <linux/err.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/list.h>
#include <linux/rtmutex.h>
#include <linux/string.h>


/* Module description */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sridhar Pavithrapu");
MODULE_DESCRIPTION("A simple kernel module with demonstration of kernel threads with kfifo");
MODULE_VERSION("1.0");
MODULE_INFO(vermagic, "4.14.15 SMP mod_unload ");

/* Macros declaration */
/* Fifo size in elements (bytes) */
#define FIFO_SIZE	2048
#define BUFFER_SIZE 200
#define TIMER_VALUE 1000000
#define NAME_BUFFER 8
#define KFIFO_NUM_ZERO 0


/* Global variables */
static DECLARE_KFIFO(test, unsigned char, FIFO_SIZE);
static struct task_struct *thread1;
static struct task_struct *thread2;


/*** Function Definitions ***/

/**
​ * ​ ​ @brief​ : Thread function for first thread.
 *
 * ​ ​ @param​ ​: data for any arguments passed 
​ *
​ * ​ ​ @return​ : int (status of the thread exit)
​**/

int first_thread_fn(void * data) {
	
	char buffer[BUFFER_SIZE];
	struct task_struct *task, *previous_task, *next_task;		
	ktime_t timeout = ktime_get();
	
	printk(KERN_INFO "Start of thread1");
	
	while(!kthread_should_stop()){

		memset(buffer, KFIFO_NUM_ZERO, sizeof(buffer));
		
		/* Getting the task information */
		task = current;
		
		/* Getting the previous task information */
		previous_task= list_entry(task->tasks.prev, struct task_struct, tasks);

		/* Getting the next task information */
		next_task=list_entry(task->tasks.next, struct task_struct, tasks);

		sprintf(buffer, "\tCurrent Task Information:\n Name: %s\nPID: %d\nvruntime: %llu\n\n\n\n", (task->comm), (task->pid), task->se.vruntime);
 
		sprintf(buffer, "%s\tPrevious Task Information:\n Name: %s\nPID: %d\nvruntime: %llu\n\n\n\n", buffer, (previous_task->comm), (previous_task->pid), previous_task->se.vruntime);

	    sprintf(buffer, "%s\tNext Task Information:\n Name: %s\nPID: %d\nvruntime: %llu\n\n\n\n", buffer, (next_task->comm), (next_task->pid), next_task->se.vruntime);


		/* Writing data to kernel fifo */
		kfifo_in(&test, buffer, strlen(buffer));
		
		/* setting timeout for one second */
		timeout = ktime_add_us(timeout, TIMER_VALUE);
		__set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_hrtimeout_range(&timeout, 100, HRTIMER_MODE_ABS);
	}

	printk(KERN_INFO "End of thread1");
	
	do_exit(KFIFO_NUM_ZERO);
	return KFIFO_NUM_ZERO;
}


/**
​ * ​ ​ @brief​ : Thread function for second thread.
 *
 * ​ ​ @param​ ​: data for any arguments passed 
​ *
​ * ​ ​ @return​ : int (status of the thread exit)
​**/

int second_thread_fn(void * data) {
	unsigned char buffer[BUFFER_SIZE];
	unsigned char c;

	printk(KERN_INFO "Start of thread2");

	while(!kthread_should_stop()){
		
			/* If data is present on the fifo */
			if(kfifo_len(&test) > KFIFO_NUM_ZERO){
				
				memset(buffer, KFIFO_NUM_ZERO, sizeof(buffer));
				kfifo_out(&test, buffer, BUFFER_SIZE);	
				printk(KERN_INFO "\n\n %s \n\n", buffer);
			}
	
	}

	printk(KERN_INFO "End of thread2");

	do_exit(KFIFO_NUM_ZERO);
	return KFIFO_NUM_ZERO;
}

/**
​* ​ ​ @brief​ : Initialises the kernel module and which spawns two threads
​*
​* ​ ​ Returns a status code of kernel module
​*
​* ​ ​ @return​ successful intialization of kernel module
​**/

static int __init thread_init(void){
	
	char  first_thread_name[NAME_BUFFER]="thread1";
	char  second_thread_name[NAME_BUFFER]="thread2";
	
	printk(KERN_INFO "In thread_init function");
	
	INIT_KFIFO(test);

	thread1 = kthread_create(first_thread_fn,NULL,first_thread_name);
	if (IS_ERR(thread1)) {
		printk(KERN_ERR "RT Failed to create RT thread\n");
		return -ESRCH;
	}
	
	printk(KERN_INFO "First thread created");
	wake_up_process(thread1);
	

	thread2 = kthread_create(second_thread_fn,NULL,second_thread_name);
	if (IS_ERR(thread2)) {
		printk(KERN_ERR "RT Failed to create RT thread\n");
		return -ESRCH;
	}
	printk(KERN_INFO "Second thread created");
	wake_up_process(thread2);

	return KFIFO_NUM_ZERO;
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
		thread1 = NULL;
	
	ret = kthread_stop(thread2);
	if(!ret)
		printk(KERN_INFO "Second thread stopped");
		thread2 = NULL;

	kfifo_free(&test);
}

module_init(thread_init);
module_exit(thread_exit);

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
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/timer.h>
#include <linux/kthread.h>  // for threads
#include <linux/sched.h>  // for task_struct
#include <linux/time.h>   // for using jiffies
#include <linux/proc_fs.h>
#include <linux/kfifo.h>
#include <linux/hrtimer.h>
#include <linux/delay.h> 
#include <linux/err.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/list.h>
#include <linux/rtmutex.h>
#include <linux/hrtimer.h>
#include <linux/delay.h>


/* Module description */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sridhar Pavithrapu");
MODULE_DESCRIPTION("A simple kernel module with demonstration of kernel threads with kfifo");
MODULE_VERSION("1.0");
MODULE_INFO(vermagic, "4.14.15 SMP mod_unload ");

/* fifo size in elements (bytes) */
#define FIFO_SIZE	32

static DECLARE_KFIFO(test, unsigned char, FIFO_SIZE);
static DECLARE_RWSEM(list_lock);
struct timer_list g_timer;
//static unsigned int time_interval = 500;

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

/**
​ * ​ ​ @brief​ : Timer handler for printing the timer count and name.
 *
 * ​ ​ @param​ ​: data for any arguments passed 
​ *
​ * ​ ​ @return​ : None
​**/

/*void timer_handler(unsigned long data){
	
	
	//down_write(&list_lock);
	  
	kfifo_in(&test, "hello", 5);
	//up_write(&list_lock);
	
    	
	
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(time_interval));
 
}*/

int first_thread_fn(void * data) {

	//int status;
	
	

	/*Starting the timer.*/
    /*setup_timer(&g_timer, timer_handler, 0);
    status = mod_timer( &g_timer, jiffies + msecs_to_jiffies(time_interval));
	if(status){
		printk(KERN_INFO "Error in mod_timer");
	}*/
	
	
	ktime_t timeout = ktime_get();
	printk(KERN_INFO "Start of thread1");
	while(!kthread_should_stop()){

		kfifo_put(&test, 'h');
		kfifo_put(&test, 'e');
		kfifo_put(&test, 'l');
		kfifo_put(&test, 'l');
		kfifo_put(&test, 'o');

		timeout = ktime_add_us(timeout, 500000);
		__set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_hrtimeout_range(&timeout, 100, HRTIMER_MODE_ABS);
	}

	printk(KERN_INFO "End of thread1");
	
	do_exit(0);
	return 0;
}

int second_thread_fn(void * data) {
	unsigned char buf[6] = {0};
	unsigned char c;

	printk(KERN_INFO "Start of thread2");

	while(!kthread_should_stop()){
		
		//while(kfifo_avail(&test)){

			//down_read(&list_lock);
			if(kfifo_len(&test) > 0){
				
				c = kfifo_get(&test, buf);
				printk(KERN_INFO "buf: %s\n", buf);
			}
	
			//up_read(&list_lock);
		//}
	
	}

	printk(KERN_INFO "End of thread2");

	do_exit(0);
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
	//struct sched_param param = { .sched_priority = MAX_RT_PRIO - 1 };
	//struct sched_param param1 = { .sched_priority = MAX_RT_PRIO - 2 };
	
	printk(KERN_INFO "In thread_init function");
	
	INIT_KFIFO(test);

	thread1 = kthread_create(first_thread_fn,NULL,first_thread_name);
	if (IS_ERR(thread1)) {
		printk(KERN_ERR "RT Failed to create RT thread\n");
		return -ESRCH;
	}
	
	printk(KERN_INFO "First thread created");
	//sched_setscheduler(thread1, SCHED_FIFO, &param);
	wake_up_process(thread1);
	

	thread2 = kthread_create(second_thread_fn,NULL,second_thread_name);
	if (IS_ERR(thread2)) {
		printk(KERN_ERR "RT Failed to create RT thread\n");
		return -ESRCH;
	}
	printk(KERN_INFO "Second thread created");
	//sched_setscheduler(thread2, SCHED_FIFO, &param1);
	wake_up_process(thread2);
	

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
		thread1 = NULL;
	
	ret = kthread_stop(thread2);
	if(!ret)
		printk(KERN_INFO "Second thread stopped");
		thread2 = NULL;

	kfifo_free(&test);
}

module_init(thread_init);
module_exit(thread_exit);

/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file kthreads_process_tree.c 
* @brief  Includes function declarations for practicing kthread.
* @author Sridhar Pavithrapu 
* @date March 6 2018 
**/

/* Headers Section */
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/string.h>
#include<linux/kthread.h>


/* Module description */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sridhar Pavithrapu");
MODULE_DESCRIPTION("A simple kernel module to generate kthreads and priting processes information");
MODULE_VERSION("1.0");
MODULE_INFO(vermagic, "4.14.15 SMP mod_unload ");

/* Global variables */
static struct task_struct *thread1;
extern struct task_struct init_task;

/*** Function Definitions ***/

/**
​ * ​ ​ @brief​ : Thread function for printing metrics of process tree informations.
 *
 * ​ ​ @param​ ​: data for any arguments passed 
​ *
​ * ​ ​ @return​ : int (status of the thread exit)
​**/

static int process_metrics(void *data){

	struct list_head *list_node;
	struct task_struct *node_temp;
	int count = 0;
	
	printk(KERN_INFO "Starting process tree metrics \n\n");
	
	node_temp = current;
    
	/* Starting process tree metrics */
	while(!kthread_should_stop()){
		
		printk(KERN_INFO "\nThread Name:%s \n", node_temp->comm);
		printk(KERN_INFO "Process Id:%d \n", node_temp->pid);
		printk(KERN_INFO "Process Status:%d \n", node_temp->state);
		
		list_for_each(list_node, &node_temp->children)
		{
			count++;
		}
		printk(KERN_INFO "Number of children's in the process tree:%d \n", count);
		count=0;
                
		printk(KERN_INFO "Nice Values:%d\n\n", (node_temp->rt_priority));	
		if(node_temp != &init_task){
			node_temp = node_temp->parent;
		}
		else{
			break;
		}
	}
	printk(KERN_INFO "End of process tree metrics \n");
	
	thread1 = NULL;
	do_exit(0);
	return 0;
}

/**
​* ​ ​ @brief​ : Initializes the kernel module and which spawns thread for process tree traversal
​*
​* ​ ​ Returns a status code of kernel module
​*
​* ​ ​ @return​ successful initialization of kernel module
​**/

static __init int thread_init_process_traverse(void){

    printk(KERN_INFO "In thread_init_process_traverse function.\n");
	
	/* Creating thread */
	thread1 = kthread_create(process_metrics, NULL, "Process Tree Traversal Thread");
	if (!IS_ERR(thread1))
	{
		printk(KERN_INFO "Thread creation for process traversal is done.\n");
        wake_up_process(thread1);
	}
	else
		printk(KERN_INFO "Error in creating thread.\n");
	

    return 0;
}

/**
​ * ​ ​ @brief​ : Exiting the kernel module.
 *
 * ​ ​ @param​ ​: None
​ *
​ * ​ ​ @return​ : None
​**/

static __exit void thread_clean_process_traverse(void){
	
	printk(KERN_INFO "Unloading the kernel module.\n");
	/* Error check for thread one */
	if (thread1){
		
		kthread_stop(thread1);
		thread1 = NULL;
		printk(KERN_INFO "First thread stopped.\n");
	}
	else
		printk(KERN_ERR "Error in thread deletion\n");
}

module_init(thread_init_process_traverse);
module_exit(thread_clean_process_traverse);


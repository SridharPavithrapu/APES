/** 
* @file   sort_array.h 
* @brief  Includes asmlinkage of system call in kernel. 
* @author Sridhar Pavithrapu 
* @date   January 26 2018 
**/

#ifndef __SORT_ARRAY_H__
#define __SORT_ARRAY_H__

asmlinkage long sys_sortArray(int32_t *, int32_t, int32_t *);

#endif 
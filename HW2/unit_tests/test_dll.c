/*************************************************************************************
*
* FileName        :    test_dll.c
* Description     :    This file contains necessary  test functions for double linked list.
					   
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit, cmocka
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "doublyLinkedList.h"

/* Macros section */
#define TEST_NUM_ZERO (0)
#define TEST_NUM_ONE (1)
#define TEST_NUM_TWO (2)
#define TEST_NUM_TEN (10)
#define TEST_NUM_ELEVEN (11)
#define TEST_NUM_TWELVE (12)

/**
​* ​ ​ @brief​ : test function for DLL insert at beginning
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_insert_at_beginning_valid(void **state){

	/* Test case for inserting node at beginning of DLL */
	int data = TEST_NUM_TEN;
	int position = TEST_NUM_ONE;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data);
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = get_data(head,position);
		assert_int_equal(return_value, data);
	}
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL insert at end
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_insert_at_end_valid(void **state){

	/* Test case for inserting node at end of DLL */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int position = TEST_NUM_TWO;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = get_data(head,position);
		assert_int_equal(return_value, data2);
	}
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL insert at given position valid case
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_insert_at_position_valid(void **state){

	/* Test case for inserting node at given index valid scenario */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int data3 = TEST_NUM_TWELVE;
	int position = TEST_NUM_TWO;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = insert_at_position(head,data3,position);
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = get_data(head,position);
		assert_int_equal(return_value, data3);
	}
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL insert at given position invalid case
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_insert_at_position_invalid(void **state){

	/* Test case for inserting node at given index invalid scenario */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int data3 = TEST_NUM_TWELVE;
	int position = TEST_NUM_ZERO;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = insert_at_position(head,data3,position);
	assert_non_null(head);
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function to get the size of DLL 
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_size_valid(void **state){

	/* Test case for size of DLL */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int data3 = TEST_NUM_TWELVE;
	int position = TEST_NUM_TWO;
	int count = TEST_NUM_ZERO;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	count++;
	head = insert_at_end(head,data2);
	count++;
	head = insert_at_position(head,data3,position);
	count++;
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = size(head);
		assert_int_equal(return_value, count);
	}
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL delete node at beginning
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_delete_at_beginning_valid(void **state){

	/* Test case for deleting node at beginning of DLL */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int position = TEST_NUM_ONE;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = delete_at_beginning(head);
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = get_data(head,position);
		assert_int_not_equal(return_value, data1);
	}
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL delete node at end
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_delete_at_end_valid(void **state){

	/* Test case for deleting node at end of DLL */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int position = TEST_NUM_ONE;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = delete_at_end(head);
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = get_data(head,position);
		assert_int_equal(return_value, data1);
	}
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL delete node at given position valid case
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_delete_at_position_valid(void **state){

	/* Test case for deleting node at given index valid scenario */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int position = TEST_NUM_ONE;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = delete_at_position(head,position);
	if(head == NULL){
		assert_null(head);	
	}
	else{
		int return_value = get_data(head,position);
		assert_int_not_equal(return_value, data1);
	}
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL delete node at given position invalid case
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_delete_at_position_invalid(void **state){

	/* Test case for deleting node at given index invalid scenario */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	int position = TEST_NUM_ZERO;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = delete_at_position(head,position);
	assert_non_null(head);		
	
	free(head);
}

/**
​* ​ ​ @brief​ : test function for DLL destroy all the nodes
​* ​ ​
​*
​* ​ ​ @param​ ​ state  ​ A pointer to the state
​*
​* ​ ​ @return​ ​None
​*/
void test_destroy_valid(void **state){

	/* Test case for destroying DLL */
	int data1 = TEST_NUM_TEN;
	int data2 = TEST_NUM_ELEVEN;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = destroy(head);
	assert_null(head->next);
	free(head);
}


/**
​* ​ ​ @brief​ : main function for all DLL test cases
​* ​ ​
​*
​* ​ ​ @return​ ​Pass and Fail test cases
​*/
int main(int argc, char **argv){

	/* Calling all DLL test case functions */
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_insert_at_beginning_valid),
		cmocka_unit_test(test_insert_at_end_valid),
		cmocka_unit_test(test_insert_at_position_valid),
		cmocka_unit_test(test_insert_at_position_invalid),
		cmocka_unit_test(test_size_valid),
		cmocka_unit_test(test_delete_at_beginning_valid),
		cmocka_unit_test(test_delete_at_end_valid),
		cmocka_unit_test(test_delete_at_position_valid),
		cmocka_unit_test(test_delete_at_position_invalid),
		cmocka_unit_test(test_destroy_valid),


	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

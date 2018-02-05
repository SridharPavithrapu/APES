#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "doublyLinkedList.h"


void test_insert_at_beginning_valid(void **state){

	int data = 10;
	int position = 1;
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

void test_insert_at_end_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	int position = 2;
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

void test_insert_at_position_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	int data3 = 12;
	int position = 2;
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

void test_insert_at_position_invalid(void **state){

	int data1 = 10;
	int data2 = 11;
	int data3 = 12;
	int position = 0;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = insert_at_position(head,data3,position);
	assert_non_null(head);
	
	free(head);
}

void test_size_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	int data3 = 12;
	int position = 2;
	int count = 0;
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

void test_delete_at_beginning_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	int position = 1;
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

void test_delete_at_end_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	int position = 1;
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

void test_delete_at_position_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	int position = 1;
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

void test_delete_at_position_invalid(void **state){

	int data1 = 10;
	int data2 = 11;
	int position = 0;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = delete_at_position(head,position);
	assert_non_null(head);		
	
	free(head);
}


void test_destroy_valid(void **state){

	int data1 = 10;
	int data2 = 11;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	head = insert_at_beginning(head,data1);
	head = insert_at_end(head,data2);
	head = destroy(head);
	assert_null(head->next);
	free(head);
}




int main(int argc, char **argv){

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

# Steps to run unit-test for doubly linked list

* For building and running tests, enter the below command inside the unit_tests folder:

    ```SHELL
    make test
    ```
    
* For cleaning up local build artifacts, enter the below command inside the unit_tests folder:

    ```SHELL
    make clean
    ```

## Source

Included source files are:

* doublyLinkedList.{h|c} - Library for Doubly Linked List.

* test_dll.c - unit tests for doubly linked lists.

* main.c - Library for running the outtput of DLL.

## Test Functions

DLL test function description and usage:

* test_insert_at_beginning_valid - This interface is used to test the valid scenario of inserting node at beginning of DLL.
								   In this scenario, a node is inserted in the DLL, and the test case is validated by
								   checking the data element of node after inserting.

* test_insert_at_end_valid - This interface is used to test the valid scenario of inserting node at end of DLL.

* test_insert_at_position_valid - This interface is used to test the valid scenario of inserting node at given position of DLL.

* test_insert_at_position_invalid - This interface is used to test the invalid scenario of inserting node at given position of DLL.

* test_size_valid - This interface is used to test the valid scenario of size of DLL.

* test_delete_at_beginning_valid - This interface is used to test the valid scenario of deleting node at beginning of DLL.

* test_delete_at_end_valid - This interface is used to test the valid scenario of deleting node at end of DLL.

* test_delete_at_position_valid - This interface is used to test the valid scenario of deleting node at given position of DLL.

* test_delete_at_position_invalid - This interface is used to test the invalid scenario of inserting node at given position of DLL.

* test_destroy_valid - This interface is used to test the valid scenario destroying DLL.


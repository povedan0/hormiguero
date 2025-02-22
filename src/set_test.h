/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author PPROG - Group 2 - AGL
 * @version 0.0 
 * @date 22-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation
 * @pre void 
 * @post Non NULL pointer to space 
 */
void test1_set_create();

/**
 * @test Test set creation
 * @pre set pointer to NULL 
 * @post Output == NULL
 */
void test2_set_create();

/**
 * @test Test function for getting number of elements of a set
 * @pre Set with a number of elements
 * @post Ouput==OK 
 */
void test1_set_get_number_elements(); 

/**
 * @test Test function  for getting number of elements of a set
 * @pre pointer to set = NULL 
 * @post Output==ERROR
 */
void test2_set_get_number_elements();


/**
 * @test Test function for checking if  a set is full
 * @pre pointer to set = NULL 
 * @post Output==TRUE
 */
void test1_set_is_full();

void test2_set_is_full();
void test3_set_is_full();
void test4_set_is_full();
void test1_set_is_empty();
void test2_set_is_empty();
void test3_set_is_empty();
void test1_set_add();
void test2_set_add();
void test3_set_add();
void test4_set_add();
void test5_set_add();
void test1_set_del();
void test2_set_del();
void test3_set_del();
void test4_set_del();
void test5_set_del();
void test6_set_del();


#endif

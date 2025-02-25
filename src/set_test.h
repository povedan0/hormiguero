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

 /**
 * @test Tests the set_is_full function with an empty set.
 * @pre The set has been created and is empty.
 * @post Output == FALSE, indicating the set is not full.
 */
void test2_set_is_full();

/**
 * @test Tests the set_is_full function with a full set.
 * @pre The set has been created and filled to its maximum capacity.
 * @post Output == TRUE, indicating the set is full.
 */
void test3_set_is_full();

/**
 * @test Tests the set_is_full function with a partially filled set.
 * @pre The set has been created and partially filled with elements.
 * @post Output == FALSE, indicating the set is not full.
 */
void test4_set_is_full();

/**
 * @test Tests the set_is_empty function when the set pointer is NULL.
 * @pre The set pointer is NULL.
 * @post The result of the function should be FALSE (set is not considered empty).
 */
void test1_set_is_empty();

/**
 * @test Tests the set_is_empty function with an empty set.
 * @pre The set has been created and is empty.
 * @post Output should be TRUE.
 */
void test2_set_is_empty();

/**
 * @test Tests the set_is_empty function with a non-empty set.
 * @pre The set has been created and an element has been added to it.
 * @post Output == FALSE (set is not empty).
 */
void test3_set_is_empty();

/**
 * @test Verify that the set_add function returns ERROR when the set pointer is NULL.
 * @pre The set pointer is NULL.
 * @post Output should be ERROR.
 */
void test1_set_add();

/**
 * @test Verify that the set_add function returns ERROR when the ID is invalid.
 * @pre The set has been created.
 * @post Output == ERROR (the invalid ID cannot be added to the set).
 */
void test2_set_add();

/**
 * @test Verify that the set_add function returns ERROR if the set is full.
 * @pre The set has been created and filled to its maximum capacity.
 * @post Output ==ERROR (no more elements can be added to the set).
 */
void test3_set_add();

/**
 * @test Verify that the set_add function returns OK when an ID is added.
 * @pre The set has been created.
 * @post Output == OK (ID successfully added to the set).
 */
void test4_set_add();

/**
 * @test Tests adding an ID to a full set.
 * @pre The set has been created and filled to its maximum capacity.
 * @post Output == ERROR (no more elements can be added to the set).
 */
void test5_set_add();

/**
 * @test Test the set_del function with a NULL set.
 * @pre The set pointer is NULL.
 * @post Output == ERROR (the set cannot be modified).
 */
void test1_set_del();

/**
 * @test Tests the set_del function with an invalid ID (NO_ID).
 * @pre The set has been created.
 * @post Output == ERROR (invalid ID cannot be removed from the set).
 */
void test2_set_del();

/**
 * @test Tests removing an ID from an empty set.
 * @pre The set has been created and is empty.
 * @post Output == ERROR (ID cannot be removed from an empty set).
 *       If the ID (1) is not found, the expected result is also ERROR.
 */
void test3_set_del();

/**
 * @test Tests removing an ID that is not in the set.
 * @pre The set has been created and an ID (1) has been added to it.
 * @post Output == ERROR (the ID (2) cannot be removed because it is not in the set).
 */
void test4_set_del();

/**
 * @test Tests removing an ID from a set.
 * @pre The set has been created and an ID (1) has been added to it.
 * @post Output == OK.
 */
void test5_set_del();

/**
 * @test Tests removing an ID from a set with multiple elements.
 * @pre The set has been created and multiple IDs (1, 2, 3) have been added to it.
 * @post The result of the function should be that the number of elements in the set is 2.
 */
void test6_set_del();

/**
 * @test Tests wehther the ID number 1 is contained in a NULL set
 * @pre A set pointer has been created and initialized to NULL
 * @post The expected result of the function is FALSE
*/
void test1_set_contains_id();

/** 
 * @test Tests whether NO_ID is contained in new set
 * @pre The set's memory is allocated and the data is initialized
 * @post The expected function result is: FALSE
*/
void test2_set_contains_id();

/** 
 * @test Tests whether the set contains a certain id
 * @pre The set is created and initialized, id=1 is added to it, different id is searched
 * @post The expected function output is FALSE
*/
void test3_set_contains_id();

/** 
 * @test Tests whether the function correctly detects an id contained in a set
 * @pre The set is created and an id=1 is added to it. The function fetches whether the set contains id=1
 * @post The expected function output is TRUE
*/
void test4_set_contains_id();

#endif

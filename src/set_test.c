/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author PPROG - Group 2 - AGL
 * @version 0.0 
 * @date 22-02-2025
 * @copyright GNU Public License
 */

#include "set_test.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_TESTS 24

/** 
 * @brief Main function for SPACE unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test1_set_get_number_elements();
  if (all || test == 3) test2_set_get_number_elements();
  if (all || test == 4) test1_set_is_full();
  if (all || test == 5) test2_set_is_full();
  if (all || test == 6) test3_set_is_full();
  if (all || test == 7) test4_set_is_full();
  if (all || test == 8) test1_set_is_empty();
  if (all || test == 9) test2_set_is_empty();
  if (all || test == 10) test3_set_is_empty();
  if (all || test == 11) test1_set_add();
  if (all || test == 12) test2_set_add();
  if (all || test == 13) test3_set_add();
  if (all || test == 14) test4_set_add();
  if (all || test == 15) test1_set_del();
  if (all || test == 16) test2_set_del();
  if (all || test == 17) test3_set_del();
  if (all || test == 18) test4_set_del();
  if (all || test == 19) test5_set_del();
  if (all || test == 20) test6_set_del();
  if (all || test == 21) test1_set_contains_id();
  if (all || test == 22) test2_set_contains_id();
  if (all || test == 23) test3_set_contains_id();
  if (all || test == 24) test4_set_contains_id();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/**Test whether a new set is successfully created*/
void test1_set_create() {
  int result;
  Set *set;
  set = set_create();
  result=set!=NULL ;
  PRINT_TEST_RESULT(result);
  set_destroy(&set);
}

/**Test whether the function set_get_number_elements successfully 
 * gets the number of elements of a valid set*/
void test1_set_get_number_elements() {
  Set *set;
  set = set_create();
  set_set_number_elements(set, 13);
  PRINT_TEST_RESULT(set_get_number_elements(set) == 13);
  set_destroy(&set);
}

/**Test whether the function set_get_number_elements returns the error code -1
 * when set points to NULL */
void test2_set_get_number_elements() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_get_number_elements(set) == -1);
}

/**Tests the function with a NULL set. The expected result is TRUE. */
void test1_set_is_full() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_is_full(set) == TRUE);
}

/**Tests the function with an empty set. The expected result is FALSE */
void test2_set_is_full() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_is_full(set) == FALSE);
  set_destroy(&set);
}

/**Tests the function with a full set. The expected result is TRUE */
void test3_set_is_full() {
  Set *set = set_create();
  set_set_number_elements(set, SET_SIZE);
  PRINT_TEST_RESULT(set_is_full(set) == TRUE);
  set_destroy(&set);
}

/**Tests the function with a partially filled set. The expected result is FALSE. */
void test4_set_is_full() {
  Set *set = set_create();
  set_set_number_elements(set, SET_SIZE-5);
  PRINT_TEST_RESULT(set_is_full(set) == FALSE);
  set_destroy(&set);
}

/**If set points to NULL. The expected result is FALSE */
void test1_set_is_empty() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_is_empty(set) == FALSE);
}

/**If the set is empty, the function is expected to expected to return TRUE*/
void test2_set_is_empty() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_is_empty(set) == TRUE);
  set_destroy(&set);
}

/**If the set is not empty, it should return FALSE */
void test3_set_is_empty() {
  Set *set = set_create();
  set_add(set, 1);  /* Add an element to the set*/
  PRINT_TEST_RESULT(set_is_empty(set) == FALSE);
  set_destroy(&set);
}

/** Verify that the function returns ERROR when the set pointer is NULL. */
void test1_set_add() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_add(set, 1) == ERROR);
}

/**Verify that the function returns ERROR when the ID is invalid. */
void test2_set_add() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_add(set, NO_ID) == ERROR);
  set_destroy(&set);
}

/**Verify that the function returns ERROR if the set is full. */
void test3_set_add() {
  Set *set = set_create();
  set_set_number_elements(set, SET_SIZE);
  PRINT_TEST_RESULT(set_add(set, 1) == ERROR);
  set_destroy(&set);
}

/**Verify that the function returns OK when ID is added. */
void test4_set_add() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_add(set, 1) == OK);
  set_destroy(&set);
}

/**Test with a NULL set. The expected result is ERROR */
void test1_set_del() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_del(set, 1) == ERROR);
}

/**Tests the function with an invalid ID (NO_ID). Expected result: ERROR..*/
void test2_set_del() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_del(set, NO_ID) == ERROR);
  set_destroy(&set);
}

/**Tests removing an ID from an empty set. Expected result: ERROR.
 * (If ID = 1 is not found the expected result is also ERROR).
*/
void test3_set_del() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_del(set, 1) == ERROR);
  set_destroy(&set);
}

/** Tests removing an ID that is not in the set. Expected result: ERROR. */
void test4_set_del() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_del(set, 2) == ERROR);
  set_destroy(&set);
}

/**Tests removing an ID from a set */ /* same as test3 (?) */
void test5_set_del() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_del(set, 1) == OK);
  set_destroy(&set);
}

/**Tests removing an ID from a set with multiple elements. */
void test6_set_del() {
  Set *set = set_create();
  set_add(set, 1);
  set_add(set, 2);
  set_add(set, 3);
  set_del(set, 2);
  PRINT_TEST_RESULT(set_get_number_elements(set) == 2);
  set_destroy(&set);
}

/**This function tests the set_contains_id function by passing a NULL set
 * and checking if the function correctly returns FALSE. */
void test1_set_contains_id() {
  Set *s= NULL;
  PRINT_TEST_RESULT(set_contains_id(s, 1) == FALSE);
}

void test2_set_contains_id() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_contains_id(s, NO_ID) == FALSE);
  set_destroy(&s);
}

/*** This function tests the set_contains_id function by creating a set,
 * adding an element to it, and checking if the function correctly returns
 * FALSE when searching for an element that is not in the set.
 */ 
void test3_set_contains_id() {
  Set *s;
  s = set_create();
  set_add(s, 1);
  PRINT_TEST_RESULT(set_contains_id(s, 10) == FALSE);
  set_destroy(&s);
}

/**This function tests the set_contains_id function by creating a set,
 * adding an element to it, and checking if the function correctly returns
 * TRUE when searching for an element that is in the set. */
void test4_set_contains_id() {
  Set *s;
  s = set_create();
  set_add(s, 1);
  PRINT_TEST_RESULT(set_contains_id(s, 1) == TRUE);
  set_destroy(&s);
}
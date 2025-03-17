/**
 * @brief Defines space module test functions and macros
 * 
 * @file space_test.h
 * @author PPROG Group 2 - GPA
 * @version 2.2.3
 * @date 24-02-2025
 * @copyright GNU Public License 
*/
#include "space_test.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_TESTS 53

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
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_space_create(); 
  if (all || test == 2) test2_space_create(); 
  if (all || test == 3) test1_space_set_name();
  if (all || test == 4) test2_space_set_name();
  if (all || test == 5) test3_space_set_name();
  if (all || test == 6) test1_space_set_north();
  if (all || test == 7) test2_space_set_north();
  if (all || test == 8) test1_space_set_south();
  if (all || test == 9) test2_space_set_south();
  if (all || test == 10) test1_space_set_east();
  if (all || test == 11) test2_space_set_east();
  if (all || test == 12) test1_space_set_west();
  if (all || test == 13) test2_space_set_west();
  if (all || test == 14) test1_space_add_object_id();
  if (all || test == 15) test2_space_add_object_id();
  if (all || test == 16) test3_space_add_object_id();  
  if (all || test == 17) test1_space_get_id();
  if (all || test == 18) test2_space_get_id();
  if (all || test == 19) test1_space_get_name();
  if (all || test == 20) test2_space_get_name();
  if (all || test == 21) test1_space_get_north();
  if (all || test == 22) test2_space_get_north();
  if (all || test == 23) test1_space_get_south();
  if (all || test == 24) test2_space_get_south();
  if (all || test == 25) test1_space_get_east();
  if (all || test == 26) test2_space_get_east();
  if (all || test == 27) test1_space_get_west();
  if (all || test == 28) test2_space_get_west();
  if (all || test == 29) test1_space_destroy();
  if (all || test == 30) test2_space_destroy();
  if (all || test == 31) test1_space_get_number_objects();
  if (all || test == 32) test2_space_get_number_objects();
  if (all || test == 33) test3_space_get_number_objects();
  if (all || test == 34) test1_space_contains(); 
  if (all || test == 35) test2_space_contains(); 
  if (all || test == 36) test3_space_contains(); 
  if (all || test == 37) test4_space_contains(); 
  if (all || test == 38) test1_space_del_object_id();
  if (all || test == 39) test2_space_del_object_id();
  if (all || test == 40) test3_space_del_object_id();
  if (all || test == 41) test1_space_objects_is_full();
  if (all || test == 42) test2_space_objects_is_full();
  if (all || test == 43) test1_space_set_character();
  if (all || test == 44) test2_space_set_character();
  if (all || test == 45) test1_space_get_character();
  if (all || test == 46) test2_space_get_character();
  if (all || test == 47) test1_space_set_gdesc();
  if (all || test == 48) test2_space_set_gdesc();
  if (all || test == 49) test1_space_get_gdesc();
  if (all || test == 50) test2_space_get_gdesc();
  if (all || test == 51) test1_space_get_objects();
  if (all || test == 52) test2_space_get_objects();
  if (all || test == 53) test3_space_get_objects();
  

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/**This function tests the space_create function by creating a space with a valid ID
 * and checking if the function correctly returns a non-NULL pointer. */
void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

/**This function tests the space_create function by creating a space with a valid ID
 * and checking if the function correctly returns the expected ID. */
void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

/**This function tests the space_destroy function with a valid space*/
void test1_space_destroy() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_destroy(s) == OK);
}

/**This function tests the space_destroy function with a NULL space*/
void test2_space_destroy() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}

/**This function tests the space_set_name function by creating a space,
 * setting its name, and checking if the function correctly returns OK. */
void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

/**This function tests the space_set_name function by passing a NULL space
 * and checking if the function correctly returns ERROR. */
void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}
/**This function tests the space_set_name function by creating a space,
 * attempting to set its name to NULL, and checking if the function correctly returns ERROR. */
void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/**This function retrieves the ID of the space that is located to the north
 * of the given space. If the space is NULL, it returns NO_ID. */
void test1_space_set_north() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_north(s, 4) == OK);
  space_destroy(s);
}

/**This function tests the space_set_north function by passing a NULL space
 * and checking if the function correctly returns ERROR. */
void test2_space_set_north() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_north(s, 4) == ERROR);
}

/**This function tests the space_set_south function by creating a space,
 * setting the ID of the space located to the south, and checking if the function
 * correctly returns OK. */
void test1_space_set_south() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_south(s, 4) == OK);
  space_destroy(s);
}

/**This function tests the space_set_south function by passing a NULL space
 * and checking if the function correctly returns ERROR. */
void test2_space_set_south() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_south(s, 4) == ERROR);
}

/**This function tests the space_set_east function by creating a space,
 * setting the ID of the space located to the east, and checking if the function
 * correctly returns OK. */
void test1_space_set_east() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_east(s, 4) == OK);
  space_destroy(s);
}

/**This function tests the space_set_east function by passing a NULL space
 * and checking if the function correctly returns ERROR. */
void test2_space_set_east() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_east(s, 4) == ERROR);
}

void test1_space_set_west() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_west(s, 4) == OK);
  space_destroy(s);
}

/** This function tests the space_set_west function by creating a space,
 * setting the ID of the space located to the west, and checking if the function
 * correctly returns OK. */
void test2_space_set_west() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_west(s, 4) == ERROR);
}

/**This function tests the space_add_object_id function by creating a space,
 * adding an object ID to the set of objects in the space, and checking if the function
 * correctly returns OK. */
void test1_space_add_object_id() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_object_id(s, 1) == OK);
  space_destroy(s);
}

/**This function tests the space_add_object_id function by passing a NULL space
 * and checking if the function correctly returns ERROR. */
void test2_space_add_object_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object_id(s,1) == ERROR);
}

/**This function tests the space_add_object_id function by creating a space,
 * attempting to add an invalid object ID (NO_ID) to the set of objects in the space,
 * and checking if the function correctly returns ERROR. */
void test3_space_add_object_id() {
  Space *s = NULL;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_object_id(s, NO_ID) == ERROR);
  space_destroy(s);
}

/**This function tests space_del_object_id with a valid space and object ID*/
void test1_space_del_object_id() {
  Space *s = space_create(1);
  space_add_object_id(s, 1);
  PRINT_TEST_RESULT(space_del_object_id(s, 1) == OK);
  space_destroy(s);
}

/**This function tests space_del_object_id with a NULL space*/
void test2_space_del_object_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_del_object_id(s, 1) == ERROR);
}

/**This function tests space_del_object_id with an invalid object ID*/
void test3_space_del_object_id() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_del_object_id(s, NO_ID) == ERROR);
  space_destroy(s);
}

/**This function tests space_objects_is_full with a NULL space*/
void test1_space_objects_is_full() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_objects_is_full(s) == TRUE);
}

/**This function tests space_objects_is_full with an empty space*/
void test2_space_objects_is_full() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_objects_is_full(s) == FALSE);
  space_destroy(s);
}

/**This function tests space_set_character with a valid space and character ID*/
void test1_space_set_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_character(s, 1) == OK);
  space_destroy(s);
}

/**This function tests space_set_character with a NULL space*/
void test2_space_set_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_character(s, 1) == ERROR);
}

/**This function tests space_get_character with a valid space*/
void test1_space_get_character() {
  Space *s = space_create(1);
  space_set_character(s, 1);
  PRINT_TEST_RESULT(space_get_character(s) == 1);
  space_destroy(s);
}

/**This function tests space_get_character with a NULL space*/
void test2_space_get_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
}

/**This function tests space_set_gdesc with a valid space and gdesc*/
void test1_space_set_gdesc() {
  Space *s = space_create(1);
  char **gdesc = (char **)malloc(GDESC_HEIGHT * sizeof(char *));
  int i;
  for (i = 0; i < GDESC_HEIGHT; i++) {
    gdesc[i] = (char *)malloc(GDESC_LENGTH * sizeof(char));
    strcpy(gdesc[i], "test");
  }
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
  for (i = 0; i < GDESC_HEIGHT; i++) {
    free(gdesc[i]);
  }
  free(gdesc);
  space_destroy(s);
}

/**This function tests space_set_gdesc with a NULL space*/
void test2_space_set_gdesc() {
  Space *s = NULL;
  char **gdesc = (char **)malloc(GDESC_HEIGHT * sizeof(char *));
  int i;
  for (i = 0; i < GDESC_HEIGHT; i++) {
    gdesc[i] = (char *)malloc(GDESC_LENGTH * sizeof(char));
    strcpy(gdesc[i], "test");
  }
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
  for (i = 0; i < GDESC_HEIGHT; i++) {
    free(gdesc[i]);
  }
  free(gdesc);
}

/**This function tests space_get_gdesc with a valid space*/
void test1_space_get_gdesc() {
  Space *s = space_create(1);
  char **gdesc = (char **)malloc(GDESC_HEIGHT * sizeof(char *));
  int i;
  for (i = 0; i < GDESC_HEIGHT; i++) {
    gdesc[i] = (char *)malloc(GDESC_LENGTH * sizeof(char));
    strcpy(gdesc[i], "test");
  }
  space_set_gdesc(s, gdesc);
  PRINT_TEST_RESULT(space_get_gdesc(s) != NULL);
  for (i = 0; i < GDESC_HEIGHT; i++) {
    free(gdesc[i]);
  }
  free(gdesc);
  space_destroy(s);
}

/**This function tests space_get_gdesc with a NULL space*/
void test2_space_get_gdesc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
}

/**This function tests the space_get_name function by creating a space,
 * setting its name, and checking if the function correctly reads the name. */
void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}
/** This function tests the space_get_name function by passing a NULL space
 * and checking if the function correctly returns NULL. */
void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/**This function tests the space_get_objects function by creating a space,
 * adding an object ID to the set of objects in the space, and checking if the function
 * correctly returns a non-NULL array of object IDs. */
void test1_space_get_objects() {
  Space *s;
  s = space_create(1);
  space_add_object_id(s, 1);
  PRINT_TEST_RESULT(space_get_objects(s) != NULL);
  space_destroy(s);
}

/**This function tests the space_get_objects function by creating a space
 * without adding any object IDs to it, and checking if the function correctly
 * returns NULL. */
void test2_space_get_objects() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_get_objects(s) == NULL);
  space_destroy(s);  
}

/**This function tests the space_get_objects function by passing a NULL space
 * and checking if the function correctly returns NULL. */
void test3_space_get_objects() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_objects(s) == NULL);
}

/**This function tests the space_get_north function by creating a space,
 * setting the ID of the space located to the north, and checking if the function
 * correctly gets the north ID. */
void test1_space_get_north() {
  Space *s;
  s = space_create(5);
  space_set_north(s, 4);
  PRINT_TEST_RESULT(space_get_north(s) == 4);
  space_destroy(s);
}

/**This function tests the space_get_north function by passing a NULL space
 * and checking if the function correctly returns NO_ID. */
void test2_space_get_north() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
}

/**This function tests the space_get_south function by creating a space,
 * setting the ID of the space located to the south, and checking if the function
 * correctly gets the south ID. */
void test1_space_get_south() {
  Space *s;
  s = space_create(5);
  space_set_south(s, 2);
  PRINT_TEST_RESULT(space_get_south(s) == 2);
  space_destroy(s);
}

/** This function tests the space_get_south function by passing a NULL space
 * and checking if the function correctly returns NO_ID. */
void test2_space_get_south() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
}

/** This function creates a space, sets its east neighbor, and checks if
 * space_get_east correctly retrieves the east neighbor's ID. */
void test1_space_get_east() {
  Space *s;
  s = space_create(5);
  space_set_east(s, 1);
  PRINT_TEST_RESULT(space_get_east(s) == 1);
  space_destroy(s);
}

/**This function checks if space_get_east correctly handles a NULL space
 * by returning NO_ID. */
void test2_space_get_east() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
}

/**This function creates a space, sets its west space, and checks if
 * space_get_west correctly reads the west space's ID. */
void test1_space_get_west() {
  Space *s;
  s = space_create(5);
  space_set_west(s, 6);
  PRINT_TEST_RESULT(space_get_west(s) == 6);
  space_destroy(s);
}

/**This function checks if space_get_west correctly handles a NULL space
 * by returning NO_ID. */
void test2_space_get_west() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
}

/**This function returns the ID of the specified space. If the space is NULL,
 * it returns NO_ID. */
void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

/**This function checks if space_get_id correctly handles a NULL space
 * by returning NO_ID. */
void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/**This function checks if space_get_number_objects correctly handles a NULL space
 * by returning -1. */
void test1_space_get_number_objects() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_number_objects(s) == -1);
}

/**This function creates a space and checks if space_get_number_objects correctly
 * returns 0 when the space contains no objects. */
void test2_space_get_number_objects() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_number_objects(s) == 0);
    space_destroy(s);
}

/**This function tests space_get_number_objects with a space containing objects*/
void test3_space_get_number_objects() {
  Space *s = space_create(1);
  space_add_object_id(s, 1);
  space_add_object_id(s, 2);
  PRINT_TEST_RESULT(space_get_number_objects(s) == 2);
  space_destroy(s);
}

/** This function creates a space, adds an object to it, and checks if
 * space_contains correctly identifies that the space contains the object. */
void test1_space_contains() {
    Space *s;
    s = space_create(1);
    space_add_object_id(s, 1);
    PRINT_TEST_RESULT(space_contains(s, 1) == TRUE);
    space_destroy(s);
}

/**This function checks if space_contains correctly handles a NULL space
 * by returning FALSE when checking for an object. */
void test2_space_contains() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_contains(s, 1) == FALSE);
}

/**This function creates a space and checks if space_contains correctly
 * returns FALSE when checking for NO_ID. */
void test3_space_contains() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_contains(s, NO_ID) == FALSE);
    space_destroy(s);
}
/**This function creates a space and checks if space_contains correctly
 * returns FALSE when checking for an object ID that is not present in the space. */
void test4_space_contains() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_contains(s, 20) == FALSE);
    space_destroy(s);
}

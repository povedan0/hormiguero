/** 
 * @brief It tests character module
 * 
 * @file set_test.c
 * @author PPROG - Group 2 - AGL
 * @version 0.0 
 * @date 22-02-2025
 * @copyright GNU Public License
*/

#include "character_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief maximum number of tests in the character test module */
#define MAX_TESTS 44


int main(int argv, char **argc) {    
  int test = 0;
  int all = 1;

  if (argv < 2) {
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argc[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_character_create();
  if (all || test == 2) test2_character_create();
  if (all || test == 3) test3_character_create();
  if (all || test == 4) test1_character_destroy();
  if (all || test == 5) test2_character_destroy();
  if (all || test == 6) test1_character_set_name();
  if (all || test == 7) test2_character_set_name();
  if (all || test == 8) test3_character_set_name();
  if (all || test == 9) test4_character_set_name();
  if (all || test == 10) test5_character_set_name();
  if (all || test == 11) test1_character_set_gdesc();
  if (all || test == 12) test2_character_set_gdesc();
  if (all || test == 13) test3_character_set_gdesc();
  if (all || test == 14) test4_character_set_gdesc();
  if (all || test == 15) test5_character_set_gdesc();
  if (all || test == 16) test1_character_increase_health();
  if (all || test == 17) test2_character_increase_health();
  if (all || test == 18) test3_character_increase_health();
  if (all || test == 19) test4_character_increase_health();
  if (all || test == 20) test5_character_increase_health();
  if (all || test == 21) test1_character_remove_health();
  if (all || test == 22) test2_character_remove_health();
  if (all || test == 23) test3_character_remove_health();
  if (all || test == 24) test4_character_remove_health();
  if (all || test == 25) test5_character_remove_health();
  if (all || test == 26) test1_character_set_friendly();
  if (all || test == 27) test2_character_set_friendly();
  if (all || test == 28) test1_character_set_message();
  if (all || test == 29) test2_character_set_message();
  if (all || test == 30) test3_character_set_message();
  if (all || test == 31) test4_character_set_message();
  if (all || test == 32) test5_character_set_message();
  if (all || test == 33) test1_character_get_id();
  if (all || test == 34) test2_character_get_id();
  if (all || test == 35) test1_character_get_name();
  if (all || test == 36) test2_character_get_name();
  if (all || test == 37) test1_character_get_gdesc();
  if (all || test == 38) test2_character_get_gdesc();
  if (all || test == 39) test1_character_get_health();
  if (all || test == 40) test2_character_get_health();
  if (all || test == 41) test1_character_get_friendly();
  if (all || test == 42) test2_character_get_friendly();
  if (all || test == 43) test1_character_get_message();
  if (all || test == 44) test2_character_get_message();


  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_character_create() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(c!=NULL);
  character_destroy(c);
}

void test2_character_create() {
  Character *c=NULL;
  c = character_create(3);
  PRINT_TEST_RESULT(character_get_id(c) == 3);
  character_destroy(c);
}

void test3_character_create() {
  Character *c=NULL;
  c = character_create(NO_ID);
  PRINT_TEST_RESULT(c == NULL);
  character_destroy(c);
}

void test1_character_destroy() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_destroy(c) == ERROR);
}

void test2_character_destroy() {
  Character *c = NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_destroy(c) == OK); 
}

void test1_character_set_name() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_set_name(c, "hi") == ERROR);
}

void test2_character_set_name() {
  Character *c=NULL;
  char *s=NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_name(c, s) == ERROR);
  character_destroy(c);
}

void test3_character_set_name() {
  Character *c=NULL;
  int i;
  char *s= (char *) malloc((WORD_SIZE+2)*sizeof(char)); 
  if (!s) return;
  for (i = 0 ; i <= WORD_SIZE+1 ; i++) {
    s[i] = 'a';
  }
  PRINT_TEST_RESULT(character_set_name(c, s) == ERROR);
  free(s);
  character_destroy(c);
}

void test4_character_set_name() {
  Character *c = NULL;
  char s[] = "hola";
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_name(c, s) == OK);
  character_destroy(c);
}

void test5_character_set_name() {
  Character *c=NULL;
  c = character_create(10);
  character_set_name(c, "a");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "a") == 0);
  character_destroy(c);
}

void test1_character_set_gdesc() {
  Character *c=NULL;
  char gdesc[] = "hola";
  PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == ERROR);
}

void test2_character_set_gdesc() {
  Character *c;
  char *gdesc=NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == ERROR);
  character_destroy(c);
}

void test3_character_set_gdesc() {
  Character *c;
  char gdesc[] = "aaaaaaaaaaaa";
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == ERROR);
  character_destroy(c);
}

void test4_character_set_gdesc() {
  Character *c;
  char gdesc[] = "a";
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == OK);
  character_destroy(c);
}

void test5_character_set_gdesc() {
  Character *c=NULL;
  c = character_create(10);
  character_set_gdesc(c, "a");
  PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "a") == 0);
  character_destroy(c);
}

void test1_character_increase_health() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_increase_health(c, 1) == ERROR);
}

void test2_character_increase_health() {
  Character *c;
  c = character_create(10);
  PRINT_TEST_RESULT(character_increase_health(c, -1) == ERROR);
  character_destroy(c);
}

void test3_character_increase_health() {
  Character *c=NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_increase_health(c, 10) == OK);
  character_destroy(c);
}

void test4_character_increase_health() {
  Character *c = NULL;
  c = character_create(10);
  character_increase_health(c, 10);
  PRINT_TEST_RESULT(character_get_health(c) == MAX_HEALTH_POINTS);
  character_destroy(c);
}

void test5_character_increase_health() {
  Character *c = NULL;
  c = character_create(10),
  character_remove_health(c, 2);
  character_increase_health(c, 1);
  PRINT_TEST_RESULT(character_get_health(c) == MAX_HEALTH_POINTS-1);
  character_destroy(c);
}
 
void test1_character_remove_health() {
  Character *c= NULL;
  PRINT_TEST_RESULT(character_remove_health(c, 10) == ERROR);
}

void test2_character_remove_health() {
  Character *c=NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_remove_health(c, -10) == ERROR);
  character_destroy(c);
}

void test3_character_remove_health() {
  Character *c = NULL;
  c = character_create(10);
  character_remove_health(c, MAX_HEALTH_POINTS+1);
  PRINT_TEST_RESULT(character_get_health(c) == 0);
  character_destroy(c);
}

void test4_character_remove_health() {
  Character *c = NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_remove_health(c, 10) == OK);
  character_destroy(c);
}

void test5_character_remove_health() {
  Character *c = NULL;
  c = character_create(10);
  character_remove_health(c, 10); 
  PRINT_TEST_RESULT(character_get_health(c) == MAX_HEALTH_POINTS - 10);
  character_destroy(c);
}

void test1_character_set_friendly() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

void test2_character_set_friendly() {
  Character *c=NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
  character_destroy(c);
}

void test1_character_set_message() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_set_message(c, "hola") == ERROR);
}

void test2_character_set_message() {
  Character *c = NULL;
  char *g=NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_message(c, g) == ERROR);
  character_destroy(c);
}

void test3_character_set_message() {
  Character *c=NULL;
  int i;
  char *s= (char *) malloc((WORD_SIZE+2)*sizeof(char)); 
  if (!s) return;
  for (i = 0 ; i <= WORD_SIZE+1 ; i++) {
    s[i] = 'a';
  }
  PRINT_TEST_RESULT(character_set_message(c, s) == ERROR);
  free(s);
  character_destroy(c);
}

void test4_character_set_message() {
  Character *c = NULL; 
  char g[] = "Hola!";
  c = character_create(10);
  PRINT_TEST_RESULT(character_set_message(c, g) == OK);
  character_destroy(c);
}

void test5_character_set_message() {
  Character *c = NULL; 
  char g[] = "Hola!";
  c = character_create(10);
  character_set_message(c, g);
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "Hola!") == 0);
  character_destroy(c);
}

void test1_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test2_character_get_id() {
  Character *c = NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_get_id(c) == 10);
  character_destroy(c);
}

void test1_character_get_name() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test2_character_get_name() {
  Character *c=NULL;
  character_create(10);
  character_set_name(c, "a");
  PRINT_TEST_RESULT(character_get_name(c) != NULL);
  character_destroy(c);
}

void test1_character_get_gdesc() {
  Character *c=NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test2_character_get_gdesc() {
  Character *c=NULL;
  character_create(10);
  character_set_gdesc(c, "a");
  PRINT_TEST_RESULT(character_get_gdesc(c) != NULL);
  character_destroy(c);
}

void test1_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == -1);
}

void test2_character_get_health() {
  Character *c = NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_get_health(c) == MAX_HEALTH_POINTS);
  character_destroy(c);
}

void test1_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}

void test2_character_get_friendly() {
  Character *c = NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}

void test1_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test2_character_get_message() {
  Character *c = NULL;
  c = character_create(10);
  PRINT_TEST_RESULT(character_get_message(c) != NULL);
  character_destroy(c);
}

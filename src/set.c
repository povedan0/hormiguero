/**
 * @brief It implements the set module functionality
 *
 * @file set.c
 * @author PPROG - Grupo 2 - GPA
 * @version 0
 * @date 18-02-2025
 * @copyright GNU Public License
 */
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Set
 * 
 * This struct contains all information relative to a set 
*/
struct _Set {
    Id ids[SET_SIZE];  /*!< Array of elements contained in the set */
    long n_ids;        /*!< Number of elements contained in said set */
};

/**
 * Allocates and initializes a new set.
 * Returns a pointer to the set or NULL on failure.
 */
Set *set_create(void) {
    Set *new_set = NULL;

    /* memory allocation */
    if (!(new_set = (Set *) calloc(1, sizeof(Set)))) return NULL;

    /* since callloc is used, no variable initialization is needed */

    return new_set;
}

/**
 * Returns the number of elements in the set.
 * Returns -1 if the set is NULL.
 */
long set_get_number_elements(Set *set) {
    if ( set == NULL ) return -1;

    return set->n_ids;
}

/**Sets the number of elements in a set.
 * This function is primarily used for testing purposes. Specifically, to test the function 
 * set_get_number_elements, as the structure Set is not accessible from set_test.c
 */
void set_set_number_elements(Set *set, long n_ids) {
    if (set != NULL) {
        set->n_ids = n_ids;
    }
}

/**
 * Frees memory allocated for a set and nullifies its pointer.
 * Returns OK on success, ERROR if the set is already NULL.
 */
Status set_destroy(Set **set) {
    if(*set) {
        free(*set);
        *set = NULL;
        return OK;
    } else {
        return ERROR;
    }
}

/**
 * Checks if the set has reached its maximum capacity.
 * Returns TRUE if full or NULL, FALSE otherwise.
 */
Bool set_is_full(Set *set) {
    if (!set) return TRUE;

    if (set->n_ids == SET_SIZE) return TRUE;

    return FALSE;
}

/**
 * Checks if the set is empty.
 * Returns TRUE if empty, FALSE otherwise.
 */
Bool set_is_empty(Set *set) {
    if ( set == NULL ) return FALSE;

    if ( set->n_ids == 0 ) return TRUE;

    return FALSE;
}

/**
 * Adds an ID to the set if it's not already present.
 * Returns ERROR if the set is full or the ID is invalid.
*/
Status set_add(Set *set, Id id) {
    long i;
    
    /* check available sapce and valid ID */
    if (set == NULL || set_is_full(set) == TRUE || id == NO_ID ) {
        return ERROR;
    }    

    /* look for existing id */
    for (i = 0 ; i < set->n_ids ; i++) {
        if (set->ids[i] == id) break;
    }

    /* id not found in the current array */
    if ( i == set->n_ids ){
        set->ids[i] = id;
        (set->n_ids)++;
    }

    return OK;
}

/**
 * Removes an ID from the set if present.
 * Returns ERROR if the set is empty or the ID is invalid.
 */
Status set_del(Set *set, Id id) {
    long i; 

    /* check valid set */
    if (!set || set_is_empty(set) == TRUE || id == NO_ID) {
        return ERROR;
    }

    /* search for id position in set */
    for (i = 0 ; i < set->n_ids ; i++) {
        if (set->ids[i] == id) {
            break;
        }
    }

    /* id not found */
    if (i == set->n_ids ) {
        return ERROR;
    }

   /* Replace the ID with the last ID in the array and set the last element in the array to NO_ID */
    if (i != set->n_ids - 1) {
        set->ids[i] = set->ids[set->n_ids - 1];
        set->ids[set->n_ids - 1] = NO_ID;
    } else {
        set->ids[set->n_ids - 1] = NO_ID;
    }

    /* decrement n_ids */
    (set->n_ids)--;


    return OK;
}

/**
 * Prints the set's contents to stdout
*/
void set_print(Set *set) {
    long i;
    
    if (set == NULL) return;

    fprintf(stdout, "---> Set: %p\n", (void *) set);
    fprintf(stdout, "---> Number of elements: %ld\n", set->n_ids);

    for ( i = 0 ; i < set->n_ids ; i++) {
        fprintf(stdout, "  ---> Element %ld: %ld\n", i+1, set->ids[i]);
    }
    
}

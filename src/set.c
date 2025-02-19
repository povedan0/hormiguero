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

Set *set_create(void) {
    Set *new_set = NULL;

    /* memory allocation */
    if (!(new_set = (Set *) calloc(1, sizeof(Set)))) return NULL;

    /* since callloc is used, no variable initialization is needed */

    return new_set;
}

long set_get_number_elements(Set *set) {
    if ( set == NULL ) return 0;

    return set->n_ids;
}

Status set_destroy(Set **set) {
    if(*set) {
        free(*set);
        *set = NULL;
        return OK;
    } else {
        return ERROR;
    }
}

Bool set_is_full(Set *set) {
    if (!set) return TRUE;

    if (set->n_ids == SET_SIZE) return TRUE;

    return FALSE;
}

Bool set_is_empty(Set *set) {
    if ( set == NULL ) return TRUE;

    if ( set->n_ids == 0 ) return TRUE;

    return FALSE;
}

Status set_add(Set *set, Id id) {
    long i;
    
    /* check available sapce and valid ID */
    if (set_is_full(set) == TRUE || id == NO_ID ) {
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

Status set_del(Set *set, Id id) {
    long i; 

    /* check valid set */
    if (set_is_empty(set) == TRUE || id == NO_ID) {
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

    /*
    for ( j = i ; j < set->n_ids ; j++) {
        if ( j + 1 != set->n_ids ) {
            set->ids[j] = set->ids[j+1];
        } else {
            set->ids[j] = NO_ID;
        }
    }
    */

   /* swap old id wtih last in the array */
    if (i != set->n_ids - 1 && set->n_ids > 0) {
        set->ids[i] = set->ids[set->n_ids - 1];
    }

    /* decrement n_ids */
    if (set->n_ids > 0) {
        (set->n_ids)--;
    }

    return OK;
}

void set_print(Set *set) {
    long i;
    
    if (set == NULL) return;

    fprintf(stdout, "---> Set: %p\n", (void *) set);
    fprintf(stdout, "---> Number of elements: %ld\n", set->n_ids);

    for ( i = 0 ; i < set->n_ids ; i++) {
        fprintf(stdout, "  ---> Element %ld: %ld\n", i+1, set->ids[i]);
    }
    
}

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

struct _Set {
    Id ids[SET_SIZE];
    long n_ids;
};

Set *set_create(void) {
    Set *new_set = NULL;

    if (!(new_set = (Set *) malloc(1 * sizeof(Set)))) return NULL;

    new_set->n_ids = 0;
    for (long i = 0 ; i < SET_SIZE ; i++) {
        new_set->ids[i] = NO_ID;
    }

    return new_set;
}

long set_get_number_elements(Set *set) {
    if ( set == NULL ) return 0;

    return set->n_ids;
}

Status set_detroy(Set *set) {
    if(set) {
        free(set);
        return OK;
    }
    return ERROR;
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
    long i, j; 

    if (set_is_empty(set) == TRUE || id == NO_ID) {
        return ERROR;
    }

    for (i = 0 ; i < set->n_ids ; i++) {
        if (set->ids[i] == id) {
            break;
        }
    }

    if (i == set->n_ids ) {
        return ERROR;
    }

    for ( j = i ; j < set->n_ids ; j++) {
        if ( j + 1 != set->n_ids ) {
            set->ids[j] = set->ids[j+1];
        } else {
            set->ids[j] = NO_ID;
        }
    }

    (set->n_ids)--;
    return OK;
}
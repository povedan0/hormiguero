/** 
 * @brief It declares the set module's public functions and types
 *
 * @file set.h
 * @author PPROG - Grupo 2 - GPA
 * @version 0
 * @date 18-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define SET_SIZE 10

typedef struct _Set Set;

Set *set_create(void);

Status set_destroy(Set *set);

Status set_add(Set *set, Id id);

Status set_del(Set *set, Id id);

long set_get_number_elements(Set *set);

Bool set_is_full(Set *set);
#endif

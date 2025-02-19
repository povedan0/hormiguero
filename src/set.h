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

/** macro containing the maximum size fo a set */
#define SET_SIZE 100

/** alias for the _Set structure */
typedef struct _Set Set;

/** 
 * @brief Allocates memory for a new set and initializes its members 
 * @author PPROG Gupo 2 - GPA 
 * 
 * @return the newly created set structure
*/
Set *set_create(void);

/**
 * @brief De-allocates memory for a set and all of its members
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set the set structure to be destroyed 
 * @return OK if everything went well or ERROR if an error occurred 
*/
Status set_destroy(Set **set);

/**
 * @brief Adds a given element to a set if said element is not already a part of it 
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set pointer to set structure to be modified 
 * @param id id of the new object in the set 
 * @return OK if everything went well or ERROR if an error occurred 
*/
Status set_add(Set *set, Id id);

/**
 * @brief Removes a given element from a set 
 * @author PPROG Grupo 2 - GPA 
 * 
 * @param set pointer to the set struct that will be modified 
 * @param id id number of the object that will be removed 
 * @return OK if everything went well or ERROR if an error occurred
*/
Status set_del(Set *set, Id id);

/**
 * @brief fetches the number of elements in a set 
 * @author PPROG Grupo 2 - GPA 
 * 
 * @param set the set whose number of elements will be retrieved 
 * @return the number of elements in the set
*/
long set_get_number_elements(Set *set);

/**
 * @brief Boolean for checking if a set is full
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set pointer to set structure to be checked 
 * @return TRUE if set is full, false otherwise 
*/
Bool set_is_full(Set *set);

/**
 * @brief Prints all information relative to a set structure 
 * @author PPROG Grupo 2 - GPA 
 * 
 * @param set pointer to set whose data will be printed
*/
void set_print(Set *set);

/**
 * @brief Boolean for checking if a set is empty
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set pointer to set structure to be checked 
 * @return TRUE if set is empty, false otherwise 
*/
Bool set_is_empty(Set *set);

#endif

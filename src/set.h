/** 
 * @brief It declares the set module's public functions and types
 *
 * @file set.h
 * @author PPROG - Grupo 2 - GPA
 * @version 1.2.0
 * @date 18-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/** @brief Maximum number of elements in a set */
#define SET_SIZE 100

/** @brief Alias for the _Set structure */
typedef struct _Set Set;

/**
 * @brief Creates and initializes a new set.
 * @author PPROG Grupo 2 - GPA
 * 
 * @return Pointer to the newly allocated set, or NULL on failure.
 */
Set *set_create(void);

/**
 * @brief Frees memory allocated for a set and resets its pointer.
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Double pointer to the set to be destroyed.
 * @return OK on success, ERROR on failure.
 */
Status set_destroy(Set **set);

/**
 * @brief Adds an element to the set if it is not already present.  
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Pointer to the set.
 * @param id ID to be added.
 * @return OK on success, ERROR otherwise.
 */
Status set_add(Set *set, Id id);

/**
 * @brief Removes an element from the set if it exists.  
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Pointer to the set.
 * @param id ID to be removed.
 * @return OK on success, ERROR otherwise.
 */
Status set_del(Set *set, Id id);

/**
 * @brief Retrieves the number of elements in a set.  
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Pointer to the set.
 * @return Number of elements in the set, -1 if set is NULL.
 */
long set_get_number_elements(Set *set);


/**
 * @brief Sets the number of elements in a set.  (Initially, added for testing purposes)
 * @author PPROG Grupo 2 - AGL
 * 
 * @param set Pointer to the set.
 * @param n_ids Number of elements in the set.
 * @return void
 */
void set_set_number_elements(Set *set, long n_ids);


/**
 * @brief Gets the Ids of the elements in a set. 
 * @author PPROG Grupo 2 - AGL
 * 
 * @param set Pointer to the set.
 * @return ids array containing the IDs from the set.

 */
Id *set_get_ids(Set *set);

/**
 * @brief returns a boolean containing whether the set contains a certain id or not
 * @author PPROG Group 2 - GPA
 * 
 * @param set pointer to set that should contain the id
 * @param element_id id of the element to be searched within the set
 * @return TRUE if the set contains the element id or FALSE if an error occurred or the set does not contain it
*/
Bool set_contains_id(Set *set, Id element_id);

/**
 * @brief Returns a boolean to whether the space contains an object or not
 * @author PPROG Group 2 - GPA
 * 
 * @param set pointer to Set to look through 
 * @param element_id ID number to look for in set
 * @return TRUE if the object is contained in the set, FALSE if an error occurred or if the object cannot be found
*/
Bool set_contains_id(Set *set, Id element_id); 

/**
 * @brief Sets the number of elements in a set.  (Initially, added for testing purposes)
 * @author PPROG Grupo 2 - AGL
 * 
 * @param set Pointer to the set.
 * @param n_ids Number of elements in the set.
 * @return void
 */
void set_set_number_elements(Set *set, long n_ids);

/**
 * @brief Checks if the set is full.  
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Pointer to the set.
 * @return TRUE if full, FALSE otherwise.
 */
Bool set_is_full(Set *set);

/**
 * @brief Checks if the set is empty.  
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Pointer to the set.
 * @return TRUE if empty, FALSE otherwise.
 */
Bool set_is_empty(Set *set);

/**
 * @brief Prints the set's contents to stdout.  
 * @author PPROG Grupo 2 - GPA
 * 
 * @param set Pointer to the set.
 */
void set_print(Set *set);

#endif

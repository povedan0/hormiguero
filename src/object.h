/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author PPROG Group 2 (AGL)
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/** alias for the object structure */
typedef struct _Object Object;

/**
 * @brief It creates a new object, allocating memory and initializing its fields
 * @author PPROG Group 2 (AGL)
 *
 * @param id the identification number for the new object
 * @return a new object, initialized
 */
Object* object_create(Id id);

/**
 * @brief It destroys an object, freeing the allocated memory
 * @author PPROG Group 2 (AGL)
 *
 * @param object a pointer to the object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object* object);

/**
 * @brief It gets the id of an object
 * @author PPROG Group 2 (AGL)
 *
 * @param object a pointer to the space
 * @return the id of space
 */
Id object_get_id(Object* object);

/**
 * @brief It sets the name of an object
 * @author PPROG Group 2 (AGL)
 *
 * @param object a pointer to the object
 * @param name a string with the name to store for the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief It gets the name of an object
 * @author PPROG Group 2 (AGL)
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char* object_get_name(Object* object);



/**
 * @brief It prints the object information (id and name of the object)
 * @author PPROG Group 2 (AGL)
 *
 * @param object a pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_print(Object* object);

#endif

/**
 * @brief It defines the space module interface
 *
 * @file object.h
 * @author 
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

 #ifndef OBJECT_H
 #define OBJECT_H
 
 #include "types.h"
 
 typedef struct _Object Object;
 
 /**
  * @brief It creates a new object, allocating memory and initializing its fields
  * @author 
  *
  * @param id the identification number for the new object
  * @return a new object, initialized
  */
 Object* object_create(Id id);
 
 /**
  * @brief It destroys an object, freeing the allocated memory
  * @author 
  *
  * @param object a pointer to the object that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status object_destroy(Object* object);
 

 /**
  * @brief It gets the id of an object
  * @author 
  *
  * @param object a pointer to the space
  * @return the id of space
  */
 Id object_get_id(Object* object);
 
 /**
  * @brief It sets the name of an object
  * @author 
  *
  * @param object a pointer to the object
  * @param name a string with the name to store for the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status object_set_name(Object* object, char* name);
 
 /**
  * @brief It gets the name of an object
  * @author 
  *
  * @param object a pointer to the object
  * @return  a string with the name of the object
  */
 const char* object_get_name(Object* object);
 
 
 
 /**
  * @brief It prints the object information
  * @author 
  *
  * This fucntion shows the id and name of the object.
  * @param object a pointer to the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status object_print(Object* object);
 
 #endif
 
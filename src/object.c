/**
 * @brief It implements the module 'object'
 *
 * @file object.c
 * @author 
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

 #include "object.h"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 /**
  * @brief Object
  *
  * This struct stores all the information of an object.
  */
 struct _Object {
   Id id;                    /*!< Id number of the object, it must be unique */
   char name[WORD_SIZE + 1]; /*!< Name of the object */
 };
 
 /** object_create allocates memory for a new object
  *  and initializes its members
  */
Object* object_create(Id id) {
   Object* newObject = NULL;
 
   /* Error control */
   if (id == NO_ID) return NULL;
 
   newObject = (Object*)malloc(sizeof(Object));
   if (newObject == NULL) {
     return NULL;
   }
 
   /* Initialization of an empty object*/
   newObject->id = id;
   newObject->name[0] = '\0';
  
   return newObject;
 }
 
 Status object_destroy(Object* object) {
   if (!object) {
     return ERROR;
   }
 
   free(object);
   /*object = NULL;*/
   return OK;
 }
 
 Id object_get_id(Object* object) {
   if (!object) {
     return NO_ID;
   }
   return object->id;
 }
 
 Status object_set_name(Object* object, char* name) {
   if (!object || !name) {
     return ERROR;
   }
 
   if (!strcpy(object->name, name)) {
     return ERROR;
   }
   return OK;
 }
 
 const char* object_get_name(Object* object) {
   if (!object) {
     return NULL;
   }
   return object->name;
 }
 
 
 Status object_print(Object* object) {
   Id idaux = NO_ID;
 
   /* Error Control */
   if (!object) {
     return ERROR;
   }
 
   /*
   Print the id and the name of the object */
   fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);
 
 
   return OK;
 }
 
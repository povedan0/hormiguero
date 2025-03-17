/**
 * @brief It implements the module 'object'
 *
 * @file object.c
 * @author PPROG - Grupo 2 - AGL
 * @version 1.0.2
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

/** It creates a new object, allocating memory and initializing its fields */
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

/** It destroys an object, freeing the allocated memory */
Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  /*object = NULL;*/
  return OK;
}

/** It gets the id of an object */
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

/** It sets the name of an object */
Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

/** It gets the name of an object */
const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

/** It prints the object information (id and name of the object) */
Status object_print(Object* object) {
  Id idaux;

  /* Error Control */
  if (!object) {
    return ERROR;
  }

  idaux = object->id;

  if (idaux == NO_ID) {
    return ERROR;
  }
  /*
  Print the id and the name of the object */
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", idaux, object->name);


  return OK;
}

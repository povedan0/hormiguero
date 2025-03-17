/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                      /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];   /*!< Name of the space */
  Id north;                   /*!< Id of the space at the north */
  Id south;                   /*!< Id of the space at the south */
  Id east;                    /*!< Id of the space at the east */
  Id west;                    /*!< Id of the space at the west */
  Set *objects;               /*!< Set of objects in the space */
  Id character_id;            /*!< Id of the character in the space or NO_ID if there is no character in the sapce */
  char **gdesc;               /*!< graphic description of the space */
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
  Space* newSpace = NULL;
  int i;

  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space*)malloc(sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  if (!(newSpace->gdesc = (char **) malloc(GDESC_HEIGHT * sizeof(char *)))) {
    space_destroy(newSpace);
    return NULL;
  }

  if (!(newSpace->gdesc[0] = (char *) malloc(GDESC_HEIGHT * GDESC_LENGTH * sizeof(char)))) {
    space_destroy(newSpace);
    return NULL;
  }

  for (i = 0 ; i < GDESC_HEIGHT  ; i++) {
    newSpace->gdesc[i] = newSpace->gdesc[0] + i*GDESC_LENGTH ;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();  /**Initialize the Set*/ 
  newSpace->character_id = NO_ID;    /** Initialize character_id to NO_ID */

  /* check for correct newSpace->objects initialization before exiting the function, as in game.c */
  if (newSpace->objects == NULL) {
    space_destroy(newSpace);
    return NULL;
  }

  return newSpace;
}

/** space_destroy frees any previously allocated memory for a space and detangles 
 * its pointer 
*/
Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  if(space->objects != NULL){
    set_destroy(&(space->objects));
  }

  if (space->gdesc) {
    if (space->gdesc[0]) free(space->gdesc[0]);
    free(space->gdesc);
  }

  free(space);
  /**space = NULL;*/ /**nonsense */
  return OK;
}

/** space_get_id fetches the id of a given space struct 
 * 
*/
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/** space_set_name assigns a given name to the space->name field of the space struct 
 * 
*/
Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

/** space_get name fetches the name of a space 
 * 
*/
const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

/** space_set_north sets the id of the space located at the north
 * 
*/
Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

/** space_get_north fetches the id of the space located at the north
 * 
*/
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

/** space_set_south sets the id of the space located at the south
 * 
*/
Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

/** space_get_south fetches the id of the space located at the south
 * 
*/
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

/** space_set_east sets the id of the space located at the east
 * 
*/
Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

/** space_get_east fetches the id of the space located at the east
 * 
*/
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

/** space_set_west sets the id of the space located at the west
 * 
*/
Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/** space_get_west fetches the id of the space located at the west
 * 
*/
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}


/** 
 * adds a given id to the set of objects in the space
*/
Status space_add_object_id(Space* space, Id object_id) {
  if (!space || !space->objects) { 
    return ERROR;
  }

  /** Add the object_id to the Set*/
  if (set_add(space->objects, object_id) == ERROR) {  
    return ERROR;
  }

  return OK;
}


/** 
 * removes a given id from the set of objects in the space
*/
Status space_del_object_id(Space *space, Id object_id) {
  if (!space || object_id == NO_ID) {
    return ERROR;
  }

  return set_del(space->objects, object_id);
}

/** 
 * returns whether a given space's space->objects field is full
*/
Bool space_objects_is_full(Space *space) {
  if (!space || !space->objects) return TRUE;

  return set_is_full(space->objects);
}

/**Returns an array with the IDs of all the objects in the Set of Space.*/
Id *space_get_objects(Space* space) {
  /*long num_objects = 0;*/
  Id *objects_ids = NULL;

  if (!space || !space->objects) return NULL;

  if (set_is_empty(space->objects)) return NULL;
  
  objects_ids = set_get_ids(space->objects);  

  return objects_ids;
}

/** Returns a boolean containing whether the space contains a certain object */
Bool space_contains(Space *space, Id object_id) {
  if (!space || object_id == NO_ID) {
    return FALSE;
  }

  return set_contains_id(space->objects, object_id);
}

/** Returns the number of objects contained in a space, -1 if an error occurred */
long space_get_number_objects(Space *space) {
  if (!space || !space->objects) {
    return -1;
  }

  return set_get_number_elements(space->objects);
}

/**sets the character ID in a given space */
Status space_set_character(Space* space, Id character_id) {
  if (!space) {
    return ERROR;
  }
  space->character_id = character_id;
  return OK;
}

/**gets the character ID in a given space */
Id space_get_character(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->character_id;
}

/** sets space->gdesc */
Status space_set_gdesc(Space *s, char **gdesc) {
  int i = 0;

  if (!s || !gdesc) return ERROR;

  for (i = 0; i < GDESC_HEIGHT ; i++) {
    strcpy(s->gdesc[i], gdesc[i]);
  }

  return OK;
}

/** gets space->gdesc */
char **space_get_gdesc(Space *s) {
  if (!s || !s->gdesc || !s->gdesc[0]) return NULL;

  return s->gdesc;
}



/** space_print prints a given space's information, space id and name, links, and object information
 *
*/
Status space_print(Space* space) {
  Id idaux = NO_ID;
  long i, n_ids; 
  Id *ids = NULL;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print every object in the space or "no objects in the space" */

  ids = space_get_objects(space);
  n_ids = space_get_number_objects(space);

  if (ids != NULL) {
    fprintf(stdout, "---> Number of objects in the space: %ld\n", n_ids);
    for (i = 0 ; i < n_ids ; i++) {
      fprintf(stdout, "  ---> Object %ld: %ld\n", i+1, ids[i]);
    }

  } else {
    fprintf(stdout, "---> No objects in the space.\n");
  }


  /* 4. Print the character_id in the space or "no character in the space" */
  if (space->character_id != NO_ID) {
    fprintf(stdout, "---> Character in the space: %ld\n", space->character_id);
  } else {
    fprintf(stdout, "---> No character in the space.\n");
  }

  if (space->gdesc) {
    fprintf(stdout, "---> Graphic description of the space: \n");
    for (i = 0 ; i < GDESC_HEIGHT ; i++) {
      fprintf(stdout, " %s\n", space->gdesc[i]);
    }
  } else {
    fprintf(stdout, "---> No graphic description of the space.\n");
  }

  return OK;
}

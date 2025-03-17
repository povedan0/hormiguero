/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 2.0.2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

/** alias for the space structure */
typedef struct _Space Space;

#define GDESC_HEIGHT 5
#define GDESC_LENGTH 10

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author PPROG Group 2 - GPA
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets whether the space has an object or not
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param idObject id of the object in the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object_id(Space* space, Id idObject);


/**
 * @brief removes the given object ID from the set of objects in the space
 * @author PPROG - Group 2 - GPA
 *
 * @param space a pointer to the space
 * @param object_id id of the object in the space to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_del_object_id(Space* space, Id object_id);

/** 
 * @brief Returns a boolean containing whether space->objects is full
 * @author PPROG Group 2 - GPA 
 * 
 * @param space pointer to space struct to be checked
 * @return TRUE if space->objects is full or pointers are invalid, FALSE otherwise
*/
Bool space_objects_is_full(Space *space);

/**
 * @brief It gets the id of the object in the space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return arrays of id's of the objects in the set of the space
 */
Id *space_get_objects(Space* space);

/**
 * @brief returns a boolean containing whether the space contains a certain object or not
 * @author PPROG Group 2 - GPA
 * 
 * @param space pointer to set that should contain the id
 * @param object_id id of the object to be searched within the set
 * @return TRUE if the space contains the object or FALSE if an error occurred or the space does not contain it
*/
Bool space_contains(Space *space, Id object_id);

/** 
 * @brief Fetches the number of objects in a space
 * @author PPROG Grupo 2 - GPA
 * 
 * @param space pointer to the space containing the objects
 * @return Number of objects in a space or -1 if an error occurred 
*/
long space_get_number_objects(Space *space);

/** 
 * @brief gets the character ID in a given space 
 * @author PPROG Grupo 2 - AGL
 * 
 * @param space pointer to the space containing the objects
 * @return Id of the character in the space 
*/
Id space_get_character(Space* space);

/** 
 * @brief set the character ID in a given space 
 * @author PPROG Grupo 2 - AGL
 * 
 * @param space pointer to the space containing the objects
 * @param character_id id of a character
 * 
 * @return OK if the character_id is successfully set; ERROR otherwise 
*/
Status space_set_character(Space* space, Id character_id);

/** 
 * @brief sets a given gdesc to the space->gdesc field. The graphic description muts be an array of strings which will be represented from the top down in the terminal
 * @author PPROG Group 2 - GPA
 * 
 * @param s the space structure that will be modified
 * @param gdesc array of strings containing the graphic description of the space
 * @return OK if everything went well or ERROR if an error occurred
*/
Status space_set_gdesc(Space *s, char **gdesc);

/**
 * @brief fetches the array of strings that make up a space's graphic description
 * @author PPROG Group 2 - GPA
 * 
 * @param s space structure containing s->gdesc
 * @return array of strings that makes up the gdesc, or NULL in case of an error 
*/
char **space_get_gdesc(Space *s);

/**
 * @brief It prints the space information
 * @author Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

#endif

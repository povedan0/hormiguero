/** @brief It defines the character data structure and the functions necessary for its management 
 * 
 * @file character.h
 * @author PPROG - Grupo 2 - AGL
 * @version 0
 * @date 25-02-2025
 * @copyright GNU Public License
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/** macro defining the maximum number of health points for characters */
#define MAX_HEALTH_POINTS 100

/** alias for the Character data structure */
typedef struct _Character Character;

/* 
    Public functions
*/

/** 
 * @brief Allocates memory for a given character and initializes its members
 * @author PPROG Group 2 (AGL)
 * 
 * @param id The id of the character to be created
 * @return NULL if an error occurred or a pointer to the newly created character variable
 * 
*/
Character *character_create(Id id);

/** 
 * @brief Frees any memory allocated for a given character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character variable that will be freed
 * @return OK if everything went well or ERROR if an error occurred
*/
Status character_destroy(Character *character);

/** 
 * @brief Returns the ID of a given character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character variable 
 * @return The ID of the character, or NO_ID if the pointer to character is NULL
*/
Id character_get_id(Character *character);

/**
 * @brief Set the name of a given character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character  A pointer to the character 
 * @param name A string containing the new name for the character
 * @return OK if the name was set successfully, or ERROR if an error occurred
*/
Status character_set_name(Character *character, char *name);

/** 
 * @brief Returns the name of the given character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character
 * @return pointer to the name of the character, or NULL if the character is NULL
*/
const char *character_get_name(Character *character);

/** 
 * @brief Sets the graphical description of the given character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character a pointer to the character
 * @param gdesc A string containing the graphical description for the character
 * @return OK if the graphical description was set successfully, or ERROR if an error occurred
*/
Status character_set_gdesc(Character *character, char *gdesc);

/** 
 * @brief Returns the graphical description of the character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character
 * @return The graphical description of the character, or NULL if the character is NULL
*/
const char *character_get_gdesc(Character *character);

/** 
 * @brief Returns the health of the given character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character a pointer to character 
 * @return The health of the character, or -1 if the character is NULL
*/
int character_get_health(Character *character);

/** 
 * @brief Increases the health of the  character 
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character
 * @return OK if everything went well or ERROR if an error occurred
*/
Status character_increase_health(Character *character, int health_points);

/** 
 * @brief Reduces the health of a character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character
 * @return OK if everything went well or ERROR if an error occurred
*/
Status character_remove_health(Character *character, int health_points) ;

/** 
 * @brief Increases the health of the  character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character
 * @return OK if everything went well or ERROR if an error occurred
*/
Bool character_get_friendly(Character *character);

/** 
 * @brief Checks whether the  character is friendly
 * @author PPROG Group 2 (AGL)
 * 
 * @param character A pointer to the character to be checked
 * @return Returns TRUE if the character is friendly; FALSE otherwise
*/
Status character_set_friendly(Character *character, Bool friendly);

/** 
 * @brief Set the message the  character
 * @author PPROG Group 2 (AGL)
 * 
 * @param character Pointer to the character whose message is to be set
 * @return OK if it went well, ERROR if error ocurred
*/
Status character_set_message(Character *character, char *message);

/** 
 * @brief Returns the  character's message
 * @author PPROG Group 2 (AGL)
 * 
 * @param character Pointer to the character whose message is to be return
 * @return message of the character, or NULL if the pointer to character is NULL.
*/
const char *character_get_message(Character *character);

/** 
 * @brief Prints the details of a character to the standard output
 * @author PPROG Group 2 (AGL)
 * 
 * @param character Pointer to the character whose details are to be printed
 * @return OK if the operation is successful, otherwise returns ERROR
*/
Status character_print(Character *character);


#endif

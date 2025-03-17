/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "character.h"

/** macro defining the maximum number of spaces contained in a game */
#define MAX_SPACES 100

/** macro defining the maximum number of objects contained in a game */
#define MAX_OBJECTS 100

/** macro defining the maximum number of characters contained in a game */
#define MAX_CHARACTERS 100

/** alias for the game structure */
typedef struct _Game Game; 

/**
 * @brief assigns a given space pointer to a certain position in the game->spaces array 
 * @author PPROG Group 2 - AGL
 * 
 * @param game pointer to game containing game->spaces array 
 * @param space space pointer to be assigned 
 * @return OK if everything went well or ERROR if an error occurred 
*/
Status game_add_space(Game *game, Space *space);

/**
 * @brief assigns a given character pointer to a certain position in the game->spaces array 
 * @author PPROG Group 2 - AGL
 * 
 * @param game pointer to game containing game->character array 
 * @param character character pointer to be added to the game 
 * @return OK if everything went well or ERROR if an error occurred 
*/
Status game_add_character(Game *game, Character *character);


/**
 * @brief assigns a given object pointer to a certain position in the game->objects array 
 * @author PPROG Group 2 - AGL
 * 
 * @param game pointer to game containing game->objects array 
 * @param object space pointer to be assigned 
 * @return OK if everything went well or ERROR if an error occurred 
*/
Status game_add_object(Game *game, Object *object);


/**
 * @brief It creates a new game, allocating memory and initializing its members
 * @author PPROG Group 2 - AGL
 *
 * @param 
 * @return a new game, initialized
 */

Game *game_create();

/** 
 * @brief It initializes a game from a given file whose name is passed by argument. 
 * @author PPROG - Group 2 - AGL
 *  
 * @param filename meant to be a .dat file containing all of the spaces information - Ids, Names, and Connections. 
 * @return a pointer to a new game; NULL if error.
*/
Game *game_create_from_file(char *filename);

/** 
 * @brief Frees allocated memory for a game structure, game->spaces and game->last_cmd. 
 * @author PPROG Group 2 - GPA - AGL
 * 
 * @param game Pointer to a game variable.
 * @return OK, if everything goes well or ERROR if there was some mistake.
*/
Status game_destroy(Game *game);

/** 
 * @brief Given a pointer to a game and a space Id, returns a space struct or null. 
 * @author Profesores PPROG
 * 
 * @param game A pointer to game where the space exists. 
 * @param id Id of the desired space
 * @return The desired space if it can be found within the given game, or null if it cannot. 
*/
Space *game_get_space(Game *game, Id id);

/** 
 * @brief Given a pointer to a game and a object Id, returns a object struct or null. 
 * @author Profesores PPROG
 * 
 * @param game A pointer to game where the object exists. 
 * @param id Id of the desired object
 * @return The desired object if it can be found within the given game, or null if it cannot. 
*/
Object *game_get_object(Game *game, Id id);

/** 
 * @brief It retrieves the current player location, stored in game struct
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @return Id of the space where the player is currently located. 
*/
Id game_get_player_location(Game *game);

/** 
 * @brief fetches the player pointer contained in game-player
 * @author PPROG Group 2 - GPA
 * 
 * @param game pointer to _Game containing the player variable 
 * @return player pointer if everything went well or NULL if anything went wrong
*/
Player *game_get_player(Game *game);

/** 
 * @brief Matches the current player location to a space Id passed by argument
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @param id The id of the space the player must be moved to
 * @return OK if everything went well, or ERROR if an error ocurred. 
*/
Status game_set_player_location(Game *game, Id id);

/** 
 * @brief It retrieves the current object location, stored in game struct
 * @author PPROG Group 2 - GPA - AGL (mod to include array of objects)
 * 
 * @param game A pointer to the current game struct
 * @param Id Id of the object
 * @return Id of the space where the object is currently located. 
*/
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief returns the pointer to object contained in that position of the game->objects array
 * @author PPROG Group 2 - GPA 
 * 
 * @param game game structure containing the objects array
 * @param pos position in the array to return 
 * @return the pointer to object contained in that position of the array
*/
Object *game_get_object_at(Game *game, int pos);

/** 
 * @brief retrieves the number of objects contained in a game
 * @author PPROG Group 2 - GPA
 * 
 * @param game pointer to gaem structure containing the number of objects
 * @return game->n_objects, which ranges from 0 to MAX_OBJECTS or -1 if an error occurred
*/
int game_get_number_objects(Game *game);

/** 
 * @brief Matches the current object location to a space Id passed by argument
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @param space_id The id of the space the object must be moved to
 * @param object_id The id of the object added to the space
 * 
 * @return OK if everything went well, or ERROR if an error ocurred. 
*/
Status game_set_object_location(Game *game, Id space_id, Id object_id) ;

/** 
 * @brief  gets the number of characters in the game
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
  
 * @return an integer that corresponds to the number of characters in the game or -1 if pointer to game NULL. 
*/
int game_get_number_of_characters(Game *game);


/** 
 * @brief  Returns a pointer to the character with a given ID
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @param id The ID of a character
  
 * @return a pointer to the character with the ID passed as an argument. 
*/
Character *game_get_character(Game *game, Id id);

/**
 * @brief Fetches the character structure contained in that position in game->characters
 * @author PPROG Group 2 - GPA 
 * 
 * @param game pointer to the game structure containing the data 
 * @param position int position in the array to retrieve
 * @return character structure contained in that position
*/
Character *game_get_character_at(Game *game, int position);

/** 
 * @brief  gets the character's location
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @param character_id The id of the character 
 *  * 
 * @return Id of the space where the character is located. 
*/
Id game_get_character_location(Game *game, Id character_id);

/** 
 * @brief sets the location of the character to a space_id
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @param space_id The id of the space the object must be moved to
 * @param character_id The id of the object added to the space
 * 
 * @return OK if everything went well, or ERROR if an error ocurred. 
*/
Status game_set_character_location(Game *game, Id space_id, Id character_id);

/** 
 * @brief sets the location of the object to a space_id
 * @author PPROG Group 2 - GPA (changed return logic)
 * 
 * @param game A pointer to the current game struct
 * @param space_id The id of the space the object must be moved to
 * @param object_id The id of the object added to the space
 * 
 * @return OK if everything went well, or ERROR if an error ocurred. 
*/
Status game_set_object_location(Game *game, Id space_id, Id object_id);

/** 
 * @brief Retrieves the last command input stored in the game struct
 * @author Profesores PPROG
 * 
 * @param game A pointer to the current game struct
 * @return Pointer to the last command 
*/
Command* game_get_last_command(Game *game);

/** 
 * @brief Assigns game->last_cmd pointer to the command pointer passed by argument. 
 * @author Profesores PPROG
 * 
 * @param game A pointer to the current game struct
 * @param command A pointer to the last command input by the user 
 * @return OK if everything went well, and ERROR if an error ocurred 
*/
Status game_set_last_command(Game *game, Command *command);

/** 
 * @brief Checks value of the boolean variable game->finished 
 * @author Profesores PPROG
 * 
 * @param game A pointer to the current game struct
 * @return TRUE if game->finished == TRUE or FALSE if game->finished == FALSE
*/
Bool game_get_finished(Game *game);

/** 
 * @brief Updates the value of the game->finished boolean variable
 * @author PPROG Group 2 - GPA
 * 
 * @param game A pointer to the current game struct
 * @param finished Boolean variable to assign to game->finished
 * @return OK if everything went well or ERROR if an error ocurred
*/
Status game_set_finished(Game *game, Bool finished);

/** 
 * @brief  This function sets the chat message in the game structure.
 * @author PPROG - Group 2 - AGL, GPA (added error checks)
 * 
 * @param game A pointer to the current game struct
 * @param message A pointer to the message string to be set
 * @return OK if the message is successfully set. ERROR if the game pointer is NULL, the message pointer is NULL,
 * or the message length exceeds the maximum allowed length
*/
Status game_set_chat_message(Game *game, const char *message);

/** 
 * @brief This function retrieves the current chat message stored in the game structur
 * @author PPROG - Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @return A pointer to the chat message string if the game pointer is valid, or NULL if the game pointer is NULL
*/
char *game_get_chat_message(Game *game);

/** 
 * @brief Prints the current game state
 * @author Profesores PPROG
 * 
 * @param game A pointer to the current game struct
*/
void game_print(Game *game);

#endif

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

/** macro defining the maximum number of spaces contained in a game */
#define MAX_SPACES 100

/** 
 * @brief Game
 * 
 * This struct stores all the information related to a game.
*/
typedef struct _Game {
  Player *player;             /*!< pointer to Player structure */
  Object *object;             /*!< pointer to Object structure */
  Space *spaces[MAX_SPACES];  /*!< array of spaces that make up the game space */
  int n_spaces;               /*!< number of spaces loaded in the game */
  Command *last_cmd;          /*!< pointer to last Command */
  Bool finished;              /*!< boolean containing whether game has finished */
} Game; 

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
 * @brief It initializes a given game to the default. 
 * @author PPROG Group 2 - GPA 
 * 
 * @param game a pointer to the game to be modified. 
 * @return OK, if everything goes well or ERROR if there was some mistake.
*/
Status game_create(Game *game);

/** 
 * @brief It initializes a game from a given file whose name is passed by argument. 
 * @author Profesores PPROG
 * 
 * @param game a pointer to the game to be intialized. 
 * @param filename meant to be a .dat file containing all of the spaces information - Ids, Names, and Connections. 
 * @return OK, if everything goes well or ERROR if there was some mistake.
*/
Status game_create_from_file(Game *game, char *filename);

/** 
 * @brief Frees allocated memory for game->spaces and game->last_cmd. 
 * @author PPROG Group 2 - GPA 
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
 * @brief fetches the object pointer contained in game-object
 * @author PPROG Group 2 - GPA
 * 
 * @param game pointer to _Game containing the object variable 
 * @return object pointer if everything went well or NULL if anything went wrong
*/
Object *game_get_object(Game *game);

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
 * @author PPROG Group 2 - GPA 
 * 
 * @param game A pointer to the current game struct
 * @return Id of the space where the object is currently located. 
*/
Id game_get_object_location(Game *game);

/** 
 * @brief Matches the current object location to a space Id passed by argument
 * @author PPROG Group 2 - AGL
 * 
 * @param game A pointer to the current game struct
 * @param id The id of the space the object must be moved to
 * @return OK if everything went well, or ERROR if an error ocurred. 
*/
Status game_set_object_location(Game *game, Id id);

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
 * @author Profesores PPROG
 * 
 * @param game A pointer to the current game struct
 * @param finished Boolean variable to assign to game->finished
 * @return OK if everything went well or ERROR if an error ocurred
*/
Status game_set_finished(Game *game, Bool finished);

/** 
 * @brief Prints the current game state
 * @author Profesores PPROG
 * 
 * @param game A pointer to the current game struct
*/
void game_print(Game *game);

#endif

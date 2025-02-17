/**
 * @brief It defines the game update interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"
#include "space.h"

/**
 * @brief Identify and update the command provided by the user and execute the corresponding function
 * @author Profesores PPROG
 * 
 * @param game pointer to the game variable being used
 * @param cmd pointer to the command variable to me modified
 * @return OK if everything wetn well or ERROR if an error occurred
*/
Status game_actions_update(Game *game, Command *cmd);

#endif

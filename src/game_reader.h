
/**
 * @brief It defines the game_reader interface
 *
 * @file game_reader.h
 * @author  PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "command.h"
#include "game.h"
#include "space.h"
#include "types.h"

/**
 * @brief implements the loading mechanism for each of the spaces that make up the game map
 * @author PPROG Group 2 - AGL 
 * 
 * @param game pointer to game variable to be initialized 
 * @param filename string containing the name of the file cointaining the game data 
 * @return OK if everything went well, or ERROR if an error occurred
*/
Status game_reader_load_spaces(Game *game, char *filename);

/**
 * @brief implements the loading of objects in the game from a data file
 * @author PPROG Group 2 - AGL 
 * 
 * @param game pointer to game variable to be initialized 
 * @param filename string containing the name of the file cointaining the game data 
 * @return OK if everything went well, or ERROR if an error occurred
*/
Status game_reader_load_objects(Game *game, char *filename);

#endif

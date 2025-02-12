
/**
 * @brief It defines the game_reader interface
 *
 * @file game_reader.h
 * @author  PPROG Group 2 (GPA, AGL)
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



Status game_reader_load_spaces(Game *game, char *filename);

#endif

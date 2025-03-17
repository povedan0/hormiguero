/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 1.1.1
 * @date 27-01-2025
 * @copyright GNU Public License
 */
#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

/** Alias for the graphic_engine structure */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It Initializes a graphic_engine structure, allocating memory and initializing its members
 * @author PPROG - Grupo 2 - AGL
 *
 * @param void 
 * @return a pointer to a graphic_engine structure, initialized
 */
Graphic_engine *graphic_engine_create(void);

/**
 * @brief It frees the allocated memory associated with a Graphic_engine structure
 * @author PPROG - Grupo 2 - AGL
 *
 * @param ge a pointer to the graphic_engine that must be destroyed
 * @return void function
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It  updates and paints the graphical interface based on the current state of the game. 
 * It ensures the interface reflects the latest game state and provides information to the player.
 * @author PPROG - Grupo 2 - GPA
 *
 * @param ge a pointer to the Graphic_engine structure 
 * @param game pointer to the Game structure containing the current game state.
 * @return void function
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif

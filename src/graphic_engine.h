/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/** Alias for the graphic_engine structure */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief allocates memory for a new graphic engine and initializes its variables 
 * @author Profesores PPROG 
 * 
 * @return pointer to the newly created graphic engine
*/
Graphic_engine *graphic_engine_create(void);

/**
 * @brief frees any memory allocated for the graphic_engine 
 * @author Profesores PPROG
 * 
 * @param ge pointer to the graphic engine variable to be freed
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief updates the graphical representation of the game 
 * @author Profesores PPROG
 * 
 * @param ge pointer to the graphic engine which will be painted in the terminal 
 * @param game pointer to game structure containing all the game information 
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif

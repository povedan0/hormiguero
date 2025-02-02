/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/** 
    Private functions
*/

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

void game_loop_run(Game game, Graphic_engine *gengine);

void game_loop_cleanup(Game game, Graphic_engine *gengine);

/** main declares the game variable and the pointer to the graphic engine, both still to be initialized and intakes command-line arguments
 * 
 * The first of these, argv[0] is the  executable file to be run from the command line
 * The second, argv[1] is the .dat file that includes game data information, to be used later by the game_loop_init
 * 
 * once the game loop has been correctly initialized game_loop_run and game_loop_cleanup are called in succession to handle the game logic
 * and memory de-allocation
 * 
 * in case any error occurs, the function will return an error message. 
*/
int main(int argc, char *argv[]) {
  Game game;
  Graphic_engine *gengine;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if (!game_loop_init(&game, &gengine, argv[1])) {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

/** game_loop_init attemps to create a new game instance allocating the necessary memory for a given game and graphic 
 * engine, through functions defined in game.c and graphic_engine.c.
 * 
 * The function returns 0 if everything went well, or 1 and an error message if any error ocurred, while also
 * freeing any allocated memory.
*/
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

/** game_loop_run is responsible for the core game mechanics: It checks if the conditions for ending the game are met
 * and if they aren't prints the game, gets the next user input and updates the game variable. 
 * 
*/
void game_loop_run(Game game, Graphic_engine *gengine) {
  Command *last_cmd;

  if (!gengine) {
    return;
  }

  last_cmd=game_get_last_command(&game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(&game) == FALSE)) {
    graphic_engine_paint_game(gengine, &game);
    command_get_user_input(last_cmd);
    game_actions_update(&game, last_cmd);
  }

}

/** game_loop_cleanup frees any previously allocated memory for a given game variable and its grapgic engine 
 * 
*/
void game_loop_cleanup(Game game, Graphic_engine *gengine) {
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}

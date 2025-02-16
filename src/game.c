/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

/** 
 * game_add_space assigns a pointer to space struct to a given position in the game->spaces array 
 * and increments the nunmber of spaces in the game by one
*/
Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/** game_create initializes a given game struct's variables  
 * 
*/
Status game_create(Game *game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  /* variable initializations */
  game->n_spaces = 0;
  game->player = player_create(1); /* suppose player_id == 1 */
  game->object = object_create(2); /* suppose object_id == 2 */
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

/** 
 * game_create_from_file intializes a given game struct's variables
 * using data from a file whose name is passed by argument. 
 * 
 * The expected data format is the following: 
 * 
 * #s:SPACE_ID|SPACE_NAME|ID_NORTH|ID_EAST|ID_SOUTH|ID_WEST
*/
Status game_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/** 
 * game_destroy de-allocates any memory reserved for a certain game structure
*/
Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  command_destroy(game->last_cmd);
  player_destroy(game->player);
  object_destroy(game->object);

  return OK;
}

/**
 * game_get space searches a certain space by its id number and returns
 * the pointer to said space
*/
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

/** 
 * game_get_player returns the pointer to the player structure contained in game
*/
Player *game_get_player(Game *game) {
  if (!game) return NULL;

  return game->player;
}

/** 
 * game_get_object returns the pointer to the object structure contained in game 
*/
Object *game_get_object(Game *game) {
  if (!game) return NULL;

  return game->object;
}


/**
 * game_get_player_location returns the space id where the player is currently located
*/
Id game_get_player_location(Game *game) { 
  if (!game || !(game->player)) return NO_ID;
  
  return player_get_location(game->player); 
}

/**
 * game_set_player_location initializes the player's location to a certain space id value
*/
Status game_set_player_location(Game *game, Id id) {
  if (!game || !game->player || id == NO_ID) {
    return ERROR;
  }FF

  if (!player_set_location(game->player, id)) return ERROR;

  return OK;
}


/**
 * game_get_object_location cycles through every space and returns 
 * the space id that matches the object's location
*/
Id game_get_object_location(Game *game) { 
  long i;
  Id idaux;

  /* Error checking */
  if (!game || (idaux = object_get_id(game->object)) == NO_ID) {
    return NO_ID;
  }

  for (i = 0 ; i<game->n_spaces ; i++) {                                             /* cycle through spaces looking for space[i].object_id */
    if (idaux == space_get_object_id(game->spaces[i])) {
      break;                                                                         /* object id found */
    }
  }

  if (i == game->n_spaces) return NO_ID;                                             /* object id not found */

  /* Correct exit */
  return space_get_id(game->spaces[i]);                                   
}

/**
 * game_set_object_location is passed a certain space id and 
 * initializes that space's object_id 
*/
Status game_set_object_location(Game *game, Id id) {
  long i;

  /* Error checking */

  if (!game) {   /* removed id == NO_ID clause, conflict in command actions take */
    return ERROR;
  }

  for (i = 0 ; i < game->n_spaces ; i++) {                                            /* cycle through every space in game struct */
    if (id == space_get_id(game->spaces[i])) {                                        /* check their correct id number */
      if (space_set_object_id(game->spaces[i], object_get_id(game->object))) {        /* attempt to assign space->object_id */
        break;                                                                        /* correct assignment */
      } else return ERROR;                                                            /* error statement */
    }
  }

  if ( i == game->n_spaces ) return ERROR;                                            /* space was not found */

  /* Correct exit */
  return OK;

}

/**
 * game_get_last_command etches a pointer to the last command input by the user
*/
Command* game_get_last_command(Game *game) { return game->last_cmd; }

/**
 * game_set_last_command updates the last command input by the user
*/
Status game_set_last_command(Game *game, Command *command) {
  if (!game || !(game->last_cmd) || !command) return ERROR;

  game->last_cmd = command;

  return OK;
}

/**
 * game_get_finished returns a boolean containing whether 
 * the game has finished or not
*/
Bool game_get_finished(Game *game) { return game->finished; }

/**
 * game_set_finished receives a boolean and updates game->finished to match 
*/
Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

/**
 * game_print prints all relevant information to a game_struct
*/
void game_print(Game *game) {
  int i = 0;

  fprintf(stdout, "\n\n-------------\n\n");

  fprintf(stdout, "=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  fprintf(stdout, "=> Object location: %d\n", (int)game_get_object_location(game));
  fprintf(stdout, "=> Player location: %d\n", (int)player_get_location(game->player));
}

/**
   Implementation of private functions
*/


/**
 * game_get_space_id_at receives a position in the game->spaces array and returns its id number
*/
Id game_get_space_id_at(Game *game, int position) {
  /* Error checking */
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

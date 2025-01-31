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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

Status game_load_spaces(Game *game, char *filename);

Status game_add_space(Game *game, Space *space);

Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

/** game_create initializes a given game struct's variables  
 * 
*/
Status game_create(Game *game) {
  int i;

  /* variable initializations */
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player_location = NO_ID;
  game->object_location = NO_ID;
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

  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/** game_destroy frees memory allocated for game->spaces and
 * game->last_cmd through function calls, avoiding dangling pointers
 * 
 * Returns OK/ERROR
*/
Status game_destroy(Game *game) {
  int i = 0;

  /* destroy every space in game->spaces */
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  /* destroy game->last_cmd */
  command_destroy(game->last_cmd);

  return OK;
}

/** game_get_space matches a given space_id to its corresponding Space struct  
 * 
 * Returns the space variable or NULL if it cannot be found or no id is given
 * 
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

/** game_get_player_location retrieves the current
 * player location, stored in game struct
 * 
*/
Id game_get_player_location(Game *game) { return game->player_location; }

/** game_set_player_location assigns the player_location 
 * variable in the game struct to the passed space id
 * 
*/
Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }

  game->player_location = id;

  return OK;
}

/** game_get_object_location retrieves the current
 * object location, stored in game struct
 * 
*/
Id game_get_object_location(Game *game) { return game->object_location; }

/** game_set_object_location assigns the object_location 
 * variable in the game struct to the passed space id
 * 
*/
Status game_set_object_location(Game *game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  game->object_location = id;
  if (space_set_object(game_get_space(game, id), TRUE) != OK) return ERROR;

  return OK;
}

/** game_get_last_command retrieves the last_cmd variable in the game struct 
 * 
*/
Command* game_get_last_command(Game *game) { return game->last_cmd; }

/** game_set_last_command assigns las_cmd in the game struct to
 * the variable passed by argument
 * 
*/
Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

/** gaem_get_finished Checks value of the boolean variable game->finished 
 * 
*/
Bool game_get_finished(Game *game) { return game->finished; }

/** game_set_finished Updates the value of the game->finished boolean variable
 * 
*/
Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

/** game_print prints current game environment
 * 
*/
void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game->object_location);
  printf("=> Player location: %d\n", (int)game->player_location);
}

/**
   Implementation of private functions
*/

/** game_load_spaces is a private function in game.c that given a filename passed 
 * by argument and a pointer to a game struct loads every space contained 
 * in that file, calling space_create to allocate memory for them and storing 
 * them in game->spaces 
 * 
*/
Status game_load_spaces(Game *game, char *filename) {
  /* variable intilizations */
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  /* breaks scanned line down into the expected data points:
  #s:SPACE_ID|SPACE_NAME|ID_NORTH|ID_EAST|ID_SOUTH|ID_WEST */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
/* debug statement */
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      /* variable addignments */
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space); /* space added to game->spaces */
      }
    }
  }

  /* error checking */
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/** game_add_space is a private function in game.c that is given a pointer 
 * to game struct and pointer to space and is responsible for adding the space 
 * to game->spaces variable and keeping track of wether the number of spaces in 
 * the structure exceeds the maximum allowed by the MAX_SPACES macro defined 
 * in game.h
 * 
*/
Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/** game_get_space_id_at is a private function in game.c that is given a pointer 
 * to game struct and a position in the array game->spaces 
 * The function returns the id of the space stored in that position
 * 
*/
Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

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
#include "object.h"
#include "player.h"

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

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}


Status game_create(Game *game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = NULL;
  game->object = NULL;
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game->player=player_create(game_get_space_id_at(game, 0));
  game->object=object_create(game_get_space_id_at(game, 0));

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  command_destroy(game->last_cmd);

  return OK;
}

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

Space *game_get_player_location(Game *game) { 
  if(game->player==NULL){
    return NULL;
  }
  
  return game_get_space(game, player_get_location(game->player)); 
}

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID || game->player==NULL) {
    return ERROR;
  }

  player_set_location (game->player, id);

  return OK;
}

Id game_get_object_location(Game *game) { 
 int i;

 if(game == NULL || game->object==NULL){
  return NO_ID; /*object not found*/
 }

 for (i = 0; i < game->n_spaces; i++) {
  if (space_get_object(game->spaces[i]) == object_get_id(game->object)) {
    return game->object;
  }
}
  return NO_ID; 
}

Status game_set_object_location(Game *game, Id id) {
  /*int i = 0;*/ /*delete warning: variable unused*/

  if (id == NO_ID || game == NULL || game->object==NULL) {
    return ERROR;
  }

  for (int i = 0; i < game->n_spaces; i++) {
    if (space_get_id(game->spaces[i])  == id) {
      // Set the idObject field of the space to the object's id
      space_set_object (game->spaces[i],  object_get_id(game->object));
      return OK;
    }
  }

  /*add this return to delete initial warning*/
  return ERROR; /*the space with the given Id not found*/

}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  if(game->player!=NULL){
    printf("=> Player location: %ld\n", player_get_location(game->player));
  }else{
    printf("Player location not set");
  }

  if(game->object!=NULL){
    printf("=> Object location: %ld\n", object_get_location(game->object));
  }else{
    printf("Object location not set");
  }
}

/**
   Implementation of private functions
*/


Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

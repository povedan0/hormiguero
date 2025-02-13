/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "space.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

void game_actions_next(Game *game);

void game_actions_back(Game *game);

void game_actions_take(Game *game);

void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;

    case DROP:
     game_actions_drop(game);
      break;  

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_take(Game *game) {
  Id space_id = NO_ID;
  Id object_id = NO_ID;
  Space *space = NULL;

/*get the id of the space where the player is located*/
  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    return;
  }

/*create variable *space from the id of the space where the player is located*/
  space = space_create(space_id);
  if(space== NULL){
    return;
  }

/*check if there is an object in that space*/
  object_id = space_get_object_id(space);
  if(object_id != NO_ID){
    space_set_object_id(space, NO_ID); /*set NO_ID in the object of the space*/
    player_set_object_id(game->player, object_id); /*set the object_id in the player*/
  }  
  return;
}

void game_actions_drop(Game *game) {
  Id object_id = NO_ID;
  Space *space=NULL;


/*get the Id of the object carried out by the player*/
/*if the player is not carrying an object, the function exits*/
object_id = player_get_object_id(game->player);
  if(object_id == NO_ID){
    return;
  }

/*space where the player is located*/
  space = game_get_space(game, player_get_location(game->player));
  if(space==NULL){
    return;
  }
/*if the space where the player is located is empty, the object is dropped there*/
  if(space_get_object_id(space)==NO_ID){
    space_set_object_id (space, object_id);
    player_set_object_id(game->player, NO_ID);
  }

/*successful exit*/
  return;
}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

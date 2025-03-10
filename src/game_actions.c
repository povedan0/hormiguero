/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "object.h"
#include "game.h"




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions - implementation of each possible command 
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

/** Identify and update the command provided by the user and execute the corresponding function */
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

/** Placeholder function -- no action is needed for these commands */
void game_actions_unknown(Game *game) {}

/** Implementation to exit the game */
void game_actions_exit(Game *game) {}

/** Implementation of the action to go forward a space */
void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Error checking */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  /* update player location to match that of the next space */
  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

/** Implementation of the action to go back a space */
void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  /* Error checking */
  if (NO_ID == space_id) {
    return;
  }

  /* update player location to match that of the previous space */
  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

/** Implementation of take object function 
 *  There are multiple objects in the game. The function iterates through the objects in the space
 * where the player is located and allow the player to take one of them.
*/
void game_actions_take(Game *game) {
  Id *object_ids=NULL;
  Player *player=NULL;
  Command *last_cmd=NULL;
  Space *space=NULL;
  const char *name;
  int i, n_objects;

  if (!(last_cmd = game_get_last_command(game))) {
    return;
  }

  if (!(player = game_get_player(game))) {
    return;
  }

  if ((space = game_get_space(game, player_get_location(player))) == NULL) {
    return;
  }

  if (player_get_object_id(player) != NO_ID) {
    return;
  }

  if ((n_objects = game_get_number_objects(game)) <= 0 ) {
    return;
  }

  for (i = 0 ; i < n_objects ; i++) {
    if (!space_contains(space, object_id = object_get_id(game_get_object_at(game, i)))) {
      continue;
    }

    name = object_get_name(game_get_object_at(game, i));
    
    if (strcasecmp(name, command_get_name(last_cmd)) == 0) {
      player_set_object_id(player, object_id);
      space_del_object(space, object_id);
    }
  }

  /* Take the first object in the array */
  object_id = object_ids[0];

  /* Assign the object to the player and remove it from the space */
  player_set_object_id(player, object_id); /* Set player->object_id to match that of the object */
  space_del_object_id(space, object_id); /* Remove the object from the space */

}

/** Implementation of drop object function */
void game_actions_drop(Game *game) {
  Id object_id = NO_ID;
  Player *player = NULL;
  Space *space = NULL;
  
  /* Error checking */
  if (!game) return;

  if (!(player = game_get_player(game))) return;

  if (!(space = game_get_space(game, player_get_location(player)))) return;

  /* Error checking for object ID and that space does not contain object_id */
  if ((object_id = player_get_object_id(player)) != NO_ID && !space_objects_is_full(space)) {
    /* Add the object to the space */
    space_add_object_id(space, object_id);

    /* Reset the object carried by the player to NO_ID */
    player_set_object_id(player, NO_ID);
  }
}

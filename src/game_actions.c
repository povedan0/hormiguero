/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author PPROG Group 2 (GPA, AGL)
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

/** Implementation of take object function */
void game_actions_take(Game *game) {
  Id object_id=NO_ID;
  Player *player=NULL;

  if (!(player = game_get_player(game))) {
    return;
  }

  if (((object_id = object_get_id(game_get_object(game))) == NO_ID)){
    return;
  }

  /* Get the object_id from the space and assign it to the player, if poossible */
  if (game_get_object_location(game) == game_get_player_location(game)) { 
    player_set_object_id(player, object_id); /* set player->object_id to match that of the space */
    space_set_object_id(game_get_space(game, game_get_object_location(game)), NO_ID); /* reset the object id contained in the space */
  }
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

  /* Get the object_id from the player and set it to the space variable */
  if ((object_id = player_get_object_id(player)) != NO_ID && (space_get_object_id(space)) == NO_ID) { /* check if space already has an object */
    game_set_object_location(game, space_get_id(space)); /* This function assumes a single object exists */
    player_set_object_id(player, NO_ID); /* reset the object carried by the player */
  }
}

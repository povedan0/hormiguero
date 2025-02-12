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

void game_actions_take(Game *game) {
  Id object_id=NO_ID;
  Player *player=NULL;

  if (!(player = game_get_player(game))) {
    return;
  }

  if (((object_id = object_get_id(game_get_object(game))) == NO_ID)){
    return;
  }

  if (game_get_object_location(game) == game_get_player_location(game)) {
    player_set_object_id(player, object_id); /* errors already accouted for */
    space_set_object_id(game_get_space(game, game_get_object_location(game)), NO_ID); /* errors already accounted for */
  }
}

void game_actions_drop(Game *game) {
  Id object_id = NO_ID;
  Player *player = NULL;
  Space *space = NULL;
  
  if (!game) return;

  if (!(player = game_get_player(game))) return;

  if (!(space = game_get_space(game, player_get_location(player)))) return;

  if ((object_id = player_get_object_id(player)) != NO_ID) {
    space_set_object_id(space, object_id);
    player_set_object_id(player, NO_ID);
  }
}

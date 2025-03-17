/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 2.0.1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/**
   Private functions - implementation of each possible command 
*/

Status game_actions_unknown(Game *game);

Status game_actions_exit(Game *game);

Status game_actions_next(Game *game);

Status game_actions_back(Game *game);

Status game_actions_left(Game *game);

Status game_actions_right(Game *game);

Status game_actions_take(Game *game);

Status game_actions_drop(Game *game);

Status game_actions_attack(Game *game);

Status game_actions_chat(Game *game);

/**
   Game actions implementation
*/

/** Identify and update the command provided by the user and execute the corresponding function */
Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;
  Status result = ERROR;


  cmd = command_get_code(command);


  switch (cmd) {
    case UNKNOWN:
      result = game_actions_unknown(game);
      break;

    case EXIT:
      result = game_actions_exit(game);
      break;

    case NEXT:
      result = game_actions_next(game);
      break;

    case BACK:
      result = game_actions_back(game);
      break;

    case LEFT:
      result = game_actions_left(game);
      break;

    case RIGHT:
      result = game_actions_right(game);
      break;

    case TAKE:
      result = game_actions_take(game);
      break;

    case DROP:
      result = game_actions_drop(game);
      break;

    case ATTACK:
      result = game_actions_attack(game);
      break;

    case CHAT:
      result = game_actions_chat(game);
      break;

    default:
      break;
  }

  command_set_status(command, result);
  if (cmd != CHAT) game_set_chat_message(game, " ");
  game_set_last_command(game, command);
  
  return OK;
}

/**
   Calls implementation for each action
*/

/** Placeholder function -- no action is needed for these commands */
Status game_actions_unknown(Game *game) {
  return OK;
}

/** Implementation to exit the game */
Status game_actions_exit(Game *game) {
  return OK;
}

/** Implementation of the action to go forward a space */
Status game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Error checking */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  /* update player location to match that of the next space */
  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id == NO_ID) return ERROR;

  return game_set_player_location(game, current_id);
}

/** Implementation of the action to go back a space */
Status game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) return ERROR;

  /* update player location to match that of the previous space */
  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id == NO_ID) return ERROR;

  return game_set_player_location(game, current_id);
}

/** Implementation of the action to go left (west) a space */
Status game_actions_left(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Error checking */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) return ERROR;

  /* update player location to match that of the west space */
  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id == NO_ID) return ERROR;

  return game_set_player_location(game, current_id);
}

/** Implementation of the action to go right (east) a space */
Status game_actions_right(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Error checking */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) return ERROR;

  /* update player location to match that of the east space */
  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id == NO_ID) return ERROR;

  return game_set_player_location(game, current_id);
}


/** Implementation of take object function 
 *  There are multiple objects in the game. The function iterates through the objects in the space
 * where the player is located and allow the player to take one of them.
*/
Status game_actions_take(Game *game) {
  Id object_id;
  Player *player=NULL;
  Command *last_cmd=NULL;
  Space *space=NULL;
  const char *name;
  int i, n_objects;
  
  /* fetch the last command */
  if (!(last_cmd = game_get_last_command(game))) {
    return ERROR;
  }

  /* fetch player */
  if (!(player = game_get_player(game))) {
    return ERROR;
  }

  /* fetch the current space structure */
  if ((space = game_get_space(game, player_get_location(player))) == NULL) {
    return ERROR;
  }

  /* player already has an object */
  if (player_get_object_id(player) != NO_ID) {
    return ERROR;
  }

  /* invalid number of objects in the game */
  if ((n_objects = game_get_number_objects(game)) <= 0 ) {
    return ERROR;
  }

  for (i = 0 ; i < n_objects ; i++) {
    /* check if space contains object in the i-th position in the game->objects array */
    if (!space_contains(space, object_id = object_get_id(game_get_object_at(game, i)))) {
      continue;
    }

    /* get object name */
    name = object_get_name(game_get_object_at(game, i));
    
    /* compare object name with the string passed as second argument to the take command */
    if (strcasecmp(name, command_get_complement(last_cmd)) == 0) {
      /* if comparison is successful, set player's object id and remove object from set */
      player_set_object_id(player, object_id);
      space_del_object_id(space, object_id);
      break;
    }
  }

  return i != n_objects;
}

/** Implementation of drop object function */
Status game_actions_drop(Game *game) {
  Id object_id = NO_ID;
  Player *player = NULL;
  Space *space = NULL;
  
  /* Error checking */
  if (!game) return ERROR;

  /* fetch player */
  if (!(player = game_get_player(game))) return ERROR;

  /* fetch current space */
  if (!(space = game_get_space(game, player_get_location(player)))) return ERROR;

  /* Error checking for object ID and that space is not full */
  if ((object_id = player_get_object_id(player)) != NO_ID && !space_objects_is_full(space)) {
    /* Add the object to the space */
    space_add_object_id(space, object_id);

    /* Reset the object carried by the player to NO_ID */
    player_set_object_id(player, NO_ID);
    return OK;
  }

  return ERROR;
}

/** Implementation of the action to attack a character */
Status game_actions_attack(Game *game) {
  Id player_location = NO_ID;
  Id character_id = NO_ID;
  Space *space=NULL;
  int random_number;

  /* Error checking */
  if (!game) return ERROR;

  /* Get the player's location */
  if ((player_location = game_get_player_location(game)) == NO_ID) return ERROR;

  /* Get the space at that player location */
  if (!(space = game_get_space(game, player_location))) return ERROR;

  /**gets the character ID in a given space
   * if there is no character in the space, return (exit the function)
  */
  character_id = space_get_character(space);
  if(character_id == NO_ID || game_get_character_location(game, character_id) != player_location) return ERROR;

  /* If the character is friendly, return (exit the function) */
  if (character_get_friendly(game_get_character(game, character_id)) == TRUE) return ERROR;

  /* Check if the character is already dead */
  if (character_get_health(game_get_character(game, character_id)) == 0) return ERROR;

  /* Generate a random number between 0 and 9 */
  srand(time(NULL));
  random_number = rand() % 10;

  /* Determine the outcome of the attack */
  if (random_number >= 0 && random_number <= 4) {
    /* Character wins */
    player_remove_health(game_get_player(game), 1);
  } else {
    /* Player wins */
    character_remove_health(game_get_character(game, character_id), 1);
  }

  /* If the player has zero health points, the game finishes */
  if (player_get_health(game_get_player(game)) == 0) {
    game_set_finished(game, TRUE);
  }

  return OK;
}

/** This function allows the player to chat with a friendly character in the same space */
Status game_actions_chat(Game *game) {
  Id player_location = NO_ID;
  Id character_id = NO_ID;
  Space *space = NULL;

  /* Error checking */
  if (!game) return ERROR;

  /* Get the player's location */
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  /* Get the space at the player's location */
  if (!(space = game_get_space(game, player_location))) {
    return ERROR;
  }

  /* Get the character ID in the space */
  character_id = space_get_character(space);
  if (character_id == NO_ID || game_get_character_location(game, character_id) != player_location) {
    return ERROR;
  }

  /* If the character is not friendly, return */
  if (character_get_friendly(game_get_character(game, character_id)) == FALSE) {
    return ERROR;
  }

   /* Set the character's message in the game structure */
  return game_set_chat_message(game, character_get_message(game_get_character(game, character_id)));
}

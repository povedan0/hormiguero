/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "space.h"
#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Game
 *
 * This struct stores all the information of a game.
 */

struct _Game {
  Player *player;                           /*!< pointer to Player structure */
  Object *objects[MAX_OBJECTS];             /*!< array of pointers to Object structures */
  int n_objects;                            /*!< number of objects loaded in the game */
  Space *spaces[MAX_SPACES];                /*!< array of spaces that make up the game space */
  int n_spaces;                             /*!< number of spaces loaded in the game */
  Character *characters[MAX_CHARACTERS];    /*!< array of pointers to Character structures */
  int n_characters;                         /*!< number of characters loaded in the game */
  Command *last_cmd;                        /*!< pointer to last Command */
  Bool finished;                            /*!< boolean containing whether game has finished */
}; 



/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

/** 
 * game_add_space assigns a pointer to space struct to a given position in the game->spaces array 
 * and increments the number of spaces in the game by one
*/
Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/**
 * game_add_character assigns a pointer to character to a given position in the game->characters array 
 * and increments the number of characters in the game by one
*/
Status game_add_character(Game *game, Character *character) {

  /*check if character pointer is NULL or if the number of characters has reached the maximum limit*/
  if ((character == NULL) || (game->n_characters >= MAX_CHARACTERS)) {
    return ERROR;
  }

  /*adds the character to the characters array and increments the n_characters counter.*/
  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

/** game_create initializes a given game struct's variables  */
Game *game_create() {
  Game* game = NULL;
    int i;

    game = (Game*)malloc(sizeof(Game));
    if (game == NULL) {
        return NULL;
    }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    game->characters[i] = NULL;
  }

  /* variable initializations */
  game->n_spaces = 0;
  game->player = player_create(1); /* suppose player_id == 1 */
  game->last_cmd = command_create();
  game->finished = FALSE;

  if (game->player == NULL || game->last_cmd == NULL) {
    if (game->player) player_destroy(game->player);
    if (game->last_cmd) command_destroy(game->last_cmd);
    game_destroy(game);
    return NULL;
  }
  

  return game;
}

/** 
 * game_create_from_file intializes a given game struct's variables
 * using data from a file whose name is passed by argument. 
 * 
 * The expected data format is the following: 
 * 
 * #s:SPACE_ID|SPACE_NAME|ID_NORTH|ID_EAST|ID_SOUTH|ID_WEST
*/
Game *game_create_from_file(char *filename) {
  int i;
  Game *game = game_create();
    if (game == NULL) {
        return NULL;
    }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));

  /* Initialize the locations for all objects to the first space */
  for (i = 0; i < game->n_objects; i++) {
    game_set_object_location(game, game_get_space_id_at(game, 0), object_get_id(game->objects[i]));
  }

  /* Initialize the locations for all characters to different spaces */
  for (i = 0; i < game->n_characters && i < game->n_spaces; i++) {
    game_set_character_location(game, game_get_space_id_at(game, i), character_get_id(game->characters[i]));
  }

  return game;
}

/** 
 * game_destroy de-allocates any memory reserved for a certain game structure
*/
Status game_destroy(Game *game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }
  
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->objects[i]);
  }

  for (i = 0; i < game->n_characters; i++) {
    character_destroy(game->characters[i]);
  }

  command_destroy(game->last_cmd);
  player_destroy(game->player);
  
/**free the game structure */
  free(game);

  return OK;
}

/**
 * game_get_space searches a certain space by its id number and returns
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
 * game_get_object  iterates through the array of objects to find the one with the matching ID.
 * If it finds the object, it returns the pointer to that object; otherwise, it returns NULL. 
*/
Object *game_get_object(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (id == object_get_id(game->objects[i])) {
      return game->objects[i];
    }
  }

  return NULL;
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
  }

  if (!player_set_location(game->player, id)) return ERROR;

  return OK;
}


/**
 * game_get_object_location  the function uses space_contains to check 
 * if a space contains the specified object ID. If it finds the space, it returns the space ID;
 * otherwise, it returns NO_ID
*/
Id game_get_object_location(Game *game,  Id object_id) { 
  long i;
 
  /* Error checking */
  if (!game || object_id == NO_ID) {
    return NO_ID;
  }
  for (i = 0; i < game->n_spaces; i++) {  /* cycle through spaces */
    if (space_contains(game->spaces[i], object_id)) {
      return space_get_id(game->spaces[i]);  /* object id found */
    }
  }

  return NO_ID;  /* object id not found */
}

/**
 * game_set_object_location is passed a certain space id and 
 * initializes that space's object_id 
*/
Status game_set_object_location(Game *game, Id space_id, Id object_id) {
  long i;

  /* Error checking */

  if (!game) {   /* removed id == NO_ID clause, conflict in command actions take */
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {  /* cycle through every space in game */
    if (space_id == space_get_id(game->spaces[i])) {  /* check the correct id number */
      if (space_add_object_id(game->spaces[i], object_id) == OK) {  /* attempt to add object to space */
        return OK;  /* correct assignment */
      } else {
        return ERROR;  /* returns error if object_id cannot be added to the space  */
      }
    }
  }

  return ERROR;  /* space was not found */
}

/**
 * game_get_character_location cycles through every space and returns 
 * the space id that matches the character's location
*/
Id game_get_character_location(Game *game, Id character_id) { 
  int i;

  /* Error checking */
  if (!game || character_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++) {  /* cycle through spaces */
    if (game->spaces[i] != NULL && space_get_character(game->spaces[i]) == character_id) {  /* check if the space contains the character */
      return space_get_id(game->spaces[i]);  /* character id found */
    }
  }

  return NO_ID;  /* character id not found */
}

/**sets the location of the character to a space_id */
Status game_set_character_location(Game *game, Id space_id, Id character_id) {
  int i;

  /* Error checking */
  if (!game || character_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {  /* cycle through every space in game */
    if (game->spaces[i]  && space_id == space_get_id(game->spaces[i])) {  /* check the correct id number */
      if (space_set_character(game->spaces[i], character_id) == OK) {  /* attempt to set character in space */
        return OK;  /* correct assignment */
      } else {
        return ERROR;  /* returns error if character_id cannot be set in the space */
      }
    }
  }

  return ERROR;  /* space was not found */
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

  /** loop to print the locations of all objects in the game */
  fprintf(stdout, "=> Objects locations: \n");
  for (i = 0; i < game->n_objects; i++) {
    fprintf(stdout, "Object %d location: %d\n", (int)object_get_id(game->objects[i]), (int)game_get_object_location(game, object_get_id(game->objects[i])));
  }

  fprintf(stdout, "=> Player location: %d\n", (int)player_get_location(game->player));

  /**print the characters of the game and their locations */

  fprintf(stdout, "=> Number of characters: %d\n",  game->n_characters);
  for (i = 0; i < game->n_characters; i++){
    fprintf(stdout, "Character %d location: %d\n", (int)character_get_id(game->characters[i]), (int)game_get_character_location(game, character_get_id(game->characters[i])));
  }
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

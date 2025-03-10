/**
 * @brief It currently implements the load of spaces (it may later also implement load of other elements of the game)
 *
 * @file game_reader.c
 * @author  PPROG Group 2 (GPA, AGL)
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Game_reader implementation: load of spaces*/

Status game_reader_load_spaces(Game *game, char *filename) {
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

  /**file opening and error checking */
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  /** This loop reads the file.
   * If a line starts with #s:, it extracts the space ID, name, 
   * and neighboring space IDs (north, east, south, west). 
   * It creates a new Space structure, sets its properties, and adds it to the game */


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
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
      }
    }
  }

  /**error checking and close file */
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status game_reader_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id object_id = NO_ID, space_id = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  /**file opening and error checking */
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  /** 
   * This loop reads the file.
   * If a line starts with #o:, it extracts the object ID, name, 
   * and space ID where it is contained.  
   * It creates a new object structure, sets its properties, and 
   * adds it to the game in the apropriate space 
   * */


  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      object = object_create(object_id);
      if (object != NULL) {
        object_set_name(object, name);
        game_set_object_location(game, space_id, object_id);
        game_add_object(game, object);
      }
    }
  }

  /**error checking and close file */
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

/** Various static declarations of macros related to the graphical interface */
#define WIDTH_MAP 60
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 15
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback; /*!< pointers to areas representing different parts of the graphical interface */
};

/** initializes the graphic engine; Initializes the screen (height and width) */
/** Allocates memory for the graphic engine */
Graphic_engine *graphic_engine_create(void) {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

/** frees the memory allocated for the graphic engine and its areas*/
void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/**update the graphical representation of the game*/
/**get the location of the player and objects, and updates the screen*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_east = NO_ID, id_west = NO_ID;
  Space *space_act = NULL;
  char str[255];
  char temp_str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, j;
  Object *object = NULL;
  Character *character = NULL;
  Id character_id = NO_ID;
  Player *player = NULL;
  char *chat_message = NULL;
  char **gdesc = NULL;
  Id object_id = NO_ID;
  int num_objects = 0;
  const char *object_name = NULL;
  int max_length = WIDTH_MAP - 12; /*Adjust based on actual layout*/

  screen_area_clear(ge->map); /* the map area is cleared */
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act); /* fetches current space */
    id_back = space_get_north(space_act); /* reads the ids of spaces located at the north and south */
    id_next = space_get_south(space_act);
    id_east = space_get_east(space_act); /* reads the ids of spaces located at the east and west */
    id_west = space_get_west(space_act);

    
    /** Paint the north space */
    if (id_back != NO_ID) {
      space_act = game_get_space(game, id_back);
      gdesc = space_get_gdesc(space_act);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | %s %d|", gdesc[0], (int)id_back);
      screen_area_puts(ge->map, str);
      for (i = 1; i < 5; i++) {
        sprintf(str, "  | %s |", gdesc[i]);
        screen_area_puts(ge->map, str);
      }
      num_objects = space_get_number_objects(space_act);
      str[0] = '\0';
      for (j = 0; j < num_objects; j++) {
        object_id = game_get_object_id_at(game, j);
        object = game_get_object(game, object_id);
        object_name = object_get_name(object);
        if (strlen(str) + strlen(object_name) + 2 > max_length) {
          strcat(str, "...");
          break;
        }
        if (j > 0) {
          strcat(str, ", ");
        }
        strcat(str, object_name);
      }
      sprintf(str, "  | %s |", str);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    /* Paint the current space */
    space_act = game_get_space(game, id_act);
    gdesc = space_get_gdesc(space_act);
    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "  | %s %2d|", gdesc[0], (int)id_act);
    screen_area_puts(ge->map, str);
    for (i = 1; i < 5; i++) {
        sprintf(str, "  | %s |", gdesc[i]);
        screen_area_puts(ge->map, str);
    }
    num_objects = space_get_number_objects(space_act);
    str[0] = '\0';
    for (j = 0; j < num_objects; j++) {
      object_id = game_get_object_id_at(game, j);
      object = game_get_object(game, object_id);
      object_name = object_get_name(object);
      if (strlen(str) + strlen(object_name) + 2 > max_length) {
         strcat(str, "...");
          break;
      }
      if (j > 0) {
        strcat(str, ", ");
      }
      strcat(str, object_name);
    }
    sprintf(str, "  | %s |", str);
    screen_area_puts(ge->map, str);
    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);

    /* Paint the south space */
    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      space_act = game_get_space(game, id_next);
      gdesc = space_get_gdesc(space_act);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | %s %2d|", gdesc[0], (int)id_next);
      screen_area_puts(ge->map, str);
      for (i = 1; i < 5; i++) {
        sprintf(str, "  | %s |", gdesc[i]);
        screen_area_puts(ge->map, str);
      }
      num_objects = space_get_number_objects(space_act);
      str[0] = '\0';
      for (j = 0; j < num_objects; j++) {
        object_id = game_get_object_id_at(game, j);
        object = game_get_object(game, object_id);
        object_name = object_get_name(object);
        if (strlen(str) + strlen(object_name) + 2 > max_length) {
            strcat(str, "...");
            break;
        }
        if (j > 0) {
          strcat(str, ", ");
        }
          strcat(str, object_name);
      }
      sprintf(str, "  | %s |", str);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    /* Paint the east space */
    if (id_east != NO_ID) {
      sprintf(str, "        >");
      screen_area_puts(ge->map, str);
      space_act = game_get_space(game, id_east);
      gdesc = space_get_gdesc(space_act);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | %s %2d|", gdesc[0], (int)id_east);
      screen_area_puts(ge->map, str);
      for (i = 1; i < 5; i++) {
        sprintf(str, "  | %s |", gdesc[i]);
        screen_area_puts(ge->map, str);
      }
      num_objects = space_get_number_objects(space_act);
      str[0] = '\0';
      for (j = 0; j < num_objects; j++) {
        object_id = game_get_object_id_at(game, j);
        object = game_get_object(game, object_id);
        object_name = object_get_name(object);
        if (strlen(str) + strlen(object_name) + 2 > max_length) {
            strcat(str, "...");
            break;
        }
        if (j > 0) {
          strcat(str, ", ");
        }
        strcat(str, object_name);
      }
      sprintf(str, "  | %s |", str);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    /* Paint the west space */
    if (id_west != NO_ID) {
      sprintf(str, "        <");
      screen_area_puts(ge->map, str);
      space_act = game_get_space(game, id_west);
      gdesc = space_get_gdesc(space_act);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | %s %2d|", gdesc[0], (int)id_west);
      screen_area_puts(ge->map, str);
      for (i = 1; i < 5; i++) {
          sprintf(str, "  | %s |", gdesc[i]);
          screen_area_puts(ge->map, str);
      }
      num_objects = space_get_number_objects(space_act);
      str[0] = '\0';
      for (j = 0; j < num_objects; j++) {
        object_id = game_get_object_id_at(game, j);
        object = game_get_object(game, object_id);
        object_name = object_get_name(object);
        if (strlen(str) + strlen(object_name) + 2 > max_length) {
          strcat(str, "...");
          break;
        }
        if (j > 0) {
          strcat(str, ", ");
        }
        strcat(str, object_name);
      }
      sprintf(str, "  | %s |", str);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
  }

  
  /** Paint in the description area */
  screen_area_clear(ge->descript);

  /* Objects and their locations */
  sprintf(str, "Objects:");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_number_of_objects(game); i++) {
    Id object_id = game_get_object_id_at(game, i);
    object = game_get_object(game, object_id);
    if (object) {
      sprintf(str, "  %s %d", object_get_name(object), (int)game_get_object_location(game, object_id));
      screen_area_puts(ge->descript, str);
    }
  }

  /* Characters and their locations */
  sprintf(str, "Characters:");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_number_of_characters(game); i++) {
    character_id = game_get_character_id_at(game, i);
    character = game_get_character(game, character_id);
    if (character) {
        sprintf(str, "  /\\oo/\\ : %d (%d)", (int)game_get_character_location(game, character_get_id(character)), character_get_health(character));
        screen_area_puts(ge->descript, str);
    }
  }

  /* Player information */
  player = game_get_player(game);
  sprintf(str, "Player: %d (%d)", (int)game_get_player_location(game), player_get_health(player));
  screen_area_puts(ge->descript, str);
  if (player_get_object_id(player) == NO_ID) {
      sprintf(str, "Player has no object");
  } else {
       sprintf(str, "Player has object: %s", object_get_name(game_get_object(game, player_get_object_id(player))));
  }
  screen_area_puts(ge->descript, str);

  /* Chat message */
  chat_message = game_get_chat_message(game);
  if (chat_message && strlen(chat_message) > 0) {
      sprintf(str, "Chat: %s", chat_message);
      screen_area_puts(ge->descript, str);
  }


  /** Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /** Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, exit or e, take or t, drop or d");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /**  Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}

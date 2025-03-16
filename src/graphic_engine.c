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
#define WIDTH_MAP 55
#define WIDTH_DES 30
#define WIDTH_BAN 23
#define HEIGHT_MAP 25
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback; /*!< pointers to areas representing different parts of the graphical interface */
};

void graphic_engine_paint_description(Graphic_engine *ge, Game *game);

void graphic_engine_paint_help(Graphic_engine *ge, Game *game);

void graphic_engine_paint_feedback(Graphic_engine *ge, Game *game);

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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char obj = '\0';
  char str[255];

  screen_area_clear(ge->map); /* the map area is cleared */
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act); /* fetches current space */
    id_back = space_get_north(space_act); /* reads the ids of spaces located at the north and south */
    id_next = space_get_south(space_act);
/* 
    if (game_get_object_location(game) == id_back)
      obj = '*';
    else
      obj = ' ';
*/
    if (id_back != NO_ID) {
      sprintf(str, "  |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }
/*
    if (game_get_object_location(game) == id_act)
      obj = '*';
    else
      obj = ' ';
*/
    if (id_act != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^     %2d|", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
/*
    if (game_get_object_location(game) == id_next)
      obj = '*';
    else
      obj = ' ';
*/
    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
    }
  }

  /** Paint in the description area */
  screen_area_clear(ge->descript);
  graphic_engine_paint_description(ge, game);
  /*
  if ((obj_loc = game_get_object_location(game)) != NO_ID) {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }
  */

  /** Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /** Paint in the help area */
  screen_area_clear(ge->help);
  graphic_engine_paint_help(ge, game);

  /* Paint in the feedback area */
  graphic_engine_paint_feedback(ge, game);

  /**  Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}


void graphic_engine_paint_feedback(Graphic_engine *ge, Game *game) {
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char str[128];
  CommandCode last_cmd = UNKNOWN;

  if (!ge || !game) return;

  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);
  
}

void graphic_engine_paint_help(Graphic_engine *ge, Game *game) {
  char str[128];
  if (!ge || !game) return;

  sprintf(str, "The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "(N)ext, (B)ack, (L)eft, (R)ight, (T)ake, (D)rop, (C)hat, (A)ttack, or (E)xit");
  screen_area_puts(ge->help, str);
}

void graphic_engine_paint_description(Graphic_engine *ge, Game *game) {
  char str[128];
  int n_objects = 0, n_characters = 0, i;
  Object *o = NULL;
  Character *c = NULL;
  Player *p = NULL;

  if (!game || !ge) return;

  /* printting of objects area */

  /***********************************/
  sprintf(str, "Objects:");
  if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
  }
  screen_area_puts(ge->descript, str);

  n_objects = game_get_number_objects(game);

  for (i = 0 ; i < n_objects ; i++) {
    o = game_get_object_at(game, i);

    if (!o) break; /* finish printing objects */

    sprintf(str, "  %s: %ld", object_get_name(o), game_get_object_location(game, object_get_id(o)));
    if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
    }
    screen_area_puts(ge->descript, str);
  }

  /***********************************/

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /* printing of the characters area */ 

  /***********************************/
  sprintf(str, "Characters: ");
  if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
  }
  screen_area_puts(ge->descript, str);

  n_characters = game_get_number_of_characters(game);

  for (i = 0 ; i < n_characters ; i++) {
    c = game_get_character_at(game, i);

    if (!c) break;

    sprintf(str, "  %s: %ld (%d)", character_get_gdesc(c), game_get_character_location(game, character_get_id(c)), character_get_health(c));

    if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
    }

    screen_area_puts(ge->descript, str);
  }

  /***********************************/


  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /* printing of the player area */

  /***********************************/

  p = game_get_player(game);

  sprintf(str, "Player: %ld (%d)", player_get_location(p), player_get_health(p));
  if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
  }
  screen_area_puts(ge->descript, str);

  if (player_get_object_id(p) == NO_ID) {
    sprintf(str, "Player has no object");
    if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
    }
  } else {
    sprintf(str, "Player has object: %s", object_get_name(game_get_object(game, player_get_object_id(p))));
    if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
    }
  }
  screen_area_puts(ge->descript, str);

  /***********************************/

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /* printing of the message area */

  /***********************************/

  sprintf(str, "Message: %s", game_get_chat_message(game));
  if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';
  }
  screen_area_puts(ge->descript, str);
  /***********************************/
}

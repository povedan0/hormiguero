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

/** Various static declarations of macros related to the graphical interface */
#define WIDTH_MAP 55
#define WIDTH_DES 30
#define WIDTH_BAN 23
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

/** 
 * Macros representing the current dimensions of the spaces as shown in the terminal
*/
#define SPACE_WIDTH 15
#define SPACE_HEIGHT 9

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback; /*!< pointers to areas representing different parts of the graphical interface */
};

void graphic_engine_paint_description(Graphic_engine *ge, Game *game);

void graphic_engine_paint_help(Graphic_engine *ge, Game *game);

void graphic_engine_paint_feedback(Graphic_engine *ge, Game *game);

void graphic_engine_paint_map(Graphic_engine *ge, Game *game);

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

  /** Paint in the map area */
  screen_area_clear(ge->map);
  graphic_engine_paint_map(ge, game);

  /** Paint in the description area */
  screen_area_clear(ge->descript);
  graphic_engine_paint_description(ge, game);

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

void graphic_engine_paint_map(Graphic_engine *ge, Game *game) {
  char str[128], obj[128], obj1[128], obj2[128], **gdesc1 = NULL, **gdesc2 = NULL, **gdesc3 = NULL;
  char gdesc_west[10], gdesc_current[10], gdesc_east[10], gdesc_str[10], gdesc_south[10];
  Space *current_space = NULL, *aux_space1 = NULL, *aux_space2 = NULL;
  Object *o = NULL;
  Id current_id, north_id, south_id, east_id, west_id;
  int i;


  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;

  current_space = game_get_space(game, current_id);
  if (current_space == NULL) return;

  if (!ge || !game) return;

  /* printing of the space behind */
  if ((north_id = space_get_north(current_space)) != NO_ID) {
    aux_space1 = game_get_space(game, north_id);

    sprintf(str, "                   +---------------+");
    screen_area_puts(ge->map, str);
    
    if (space_get_character(aux_space1) == NO_ID)
      sprintf(gdesc_str, "      ");
    else
      sprintf(gdesc_str, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(aux_space1))));
    
    sprintf(str, "                   |     %s %-3ld|", gdesc_str, north_id);
    screen_area_puts(ge->map, str);

    gdesc1 = space_get_gdesc(aux_space1);
    for (i = 0 ; i < GDESC_HEIGHT ; i++) {
      sprintf(str, "                   |%9s      |", gdesc1[i]);
      screen_area_puts(ge->map, str);
    }

    obj[0] = '\0';

    for (i = 0 ; i < game_get_number_objects(game) ; i++) {
      if (space_contains(aux_space1, object_get_id(o = game_get_object_at(game, i)))) {
        if (obj[0] != '\0') strcat(obj, ", ");
        strcat(obj, object_get_name(o));
      }
    }
    if (strlen(obj) > SPACE_WIDTH) {
      obj[SPACE_WIDTH] = '\0';
      obj[SPACE_WIDTH - 1] = '.';
      obj[SPACE_WIDTH - 2] = '.';
      obj[SPACE_WIDTH - 3] = '.';
    }

    sprintf(str, "                   |%-15s|", obj);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   +---------------+");
    screen_area_puts(ge->map, str);

    sprintf(str, "                           ^");
    screen_area_puts(ge->map, str);
  } else {
    for (i = 0 ; i <= SPACE_HEIGHT ; i++) {
      sprintf(str, " ");
      screen_area_puts(ge->map, str);
    }
  }

  if ((west_id = space_get_west(current_space)) != NO_ID) {
    aux_space1 = game_get_space(game, west_id);
    if ((east_id = space_get_east(current_space)) != NO_ID) {
      aux_space2 = game_get_space(game, east_id);

      sprintf(str, "+---------------+  +---------------+  +---------------+");
      screen_area_puts(ge->map, str);
            
      if (space_get_character(aux_space1) == NO_ID)
        sprintf(gdesc_west, "      ");
      else
        sprintf(gdesc_west, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(aux_space1))));
      
      if (space_get_character(current_space) == NO_ID)
        sprintf(gdesc_current, "      ");
      else
        sprintf(gdesc_current, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(current_space))));
      
      if (space_get_character(aux_space2) == NO_ID)
        sprintf(gdesc_east, "      ");
      else
        sprintf(gdesc_east, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(aux_space2))));
      
      sprintf(str, "|     %s %-3ld|  | mO^ %s %-3ld|  |     %s %-3ld|", 
              gdesc_west, west_id, 
              gdesc_current, current_id, 
              gdesc_east, east_id);
      screen_area_puts(ge->map, str);

      gdesc1 = space_get_gdesc(aux_space1);
      gdesc2 = space_get_gdesc(current_space);
      gdesc3 = space_get_gdesc(aux_space2);

      for (i = 0 ; i < GDESC_HEIGHT ; i++) {
        if (i == GDESC_HEIGHT/2) {
          sprintf(str, "|%9s      |<-|%9s      |->|%9s      |", gdesc1[i], gdesc2[i], gdesc3[i]);
          screen_area_puts(ge->map, str);
          continue;
        }
        
        sprintf(str, "|%9s      |  |%9s      |  |%9s      |", gdesc1[i], gdesc2[i], gdesc3[i]);
        screen_area_puts(ge->map, str);
      }

      obj[0] = '\0';
      obj1[0] = '\0';
      obj2[0] = '\0';

      for (i = 0 ; i < game_get_number_objects(game) ; i++) {
        if (space_contains(aux_space1, object_get_id(o = game_get_object_at(game, i)))) {
          if (obj[0] != '\0') strcat(obj, ", ");
          strcat(obj, object_get_name(o));
        }

        if (space_contains(current_space, object_get_id(o))) {
          if (obj1[0] != '\0') strcat(obj1, ", ");
          strcat(obj1, object_get_name(o));
        }

        if (space_contains(aux_space2, object_get_id(o))) {
          if (obj2[0] != '\0') strcat(obj2, ", ");
          strcat(obj2, object_get_name(o));
        }

      }

      
      if (strlen(obj) > SPACE_WIDTH) {
        obj[SPACE_WIDTH] = '\0';
        obj[SPACE_WIDTH - 1] = '.';
        obj[SPACE_WIDTH - 2] = '.';
        obj[SPACE_WIDTH - 3] = '.';
      }

      if (strlen(obj1) > SPACE_WIDTH) {
        obj1[SPACE_WIDTH] = '\0';
        obj1[SPACE_WIDTH - 1] = '.';
        obj1[SPACE_WIDTH - 2] = '.';
        obj1[SPACE_WIDTH - 3] = '.';
      }

      if (strlen(obj2) > SPACE_WIDTH) {
        obj2[SPACE_WIDTH] = '\0';
        obj2[SPACE_WIDTH - 1] = '.';
        obj2[SPACE_WIDTH - 2] = '.';
        obj2[SPACE_WIDTH - 3] = '.';
      }
      
      sprintf(str, "|%-15s|  |%-15s|  |%-15s|", obj, obj1, obj2);
      screen_area_puts(ge->map, str);
      
      sprintf(str, "+---------------+  +---------------+  +---------------+");
      screen_area_puts(ge->map, str);

    } else {
      sprintf(str, "+---------------+  +---------------+");
      screen_area_puts(ge->map, str);
            
      if (space_get_character(aux_space1) == NO_ID)
        sprintf(gdesc_west, "      ");
      else
        sprintf(gdesc_west, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(aux_space1))));
      
      if (space_get_character(current_space) == NO_ID)
        sprintf(gdesc_current, "      ");
      else
        sprintf(gdesc_current, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(current_space))));
      
      sprintf(str, "|     %s %-3ld|  | mO^ %s %-3ld|", 
              gdesc_west, west_id, 
              gdesc_current, current_id);
      screen_area_puts(ge->map, str);

      gdesc1 = space_get_gdesc(aux_space1);
      gdesc2 = space_get_gdesc(current_space);

      for (i = 0 ; i < GDESC_HEIGHT ; i++) {
        if (i == GDESC_HEIGHT/2) {
          sprintf(str, "|%9s      |<-|%9s      |", gdesc1[i], gdesc2[i]);
          screen_area_puts(ge->map, str);
          continue;
        }

        sprintf(str, "|%9s      |  |%9s      |", gdesc1[i], gdesc2[i]);
        screen_area_puts(ge->map, str);
      }

      obj[0] = '\0';
      obj1[0] = '\0';

      for (i = 0 ; i < game_get_number_objects(game) ; i++) {
        if (space_contains(aux_space1, object_get_id(o = game_get_object_at(game, i)))) {
          if (obj[0] != '\0') strcat(obj, ", ");
          strcat(obj, object_get_name(o));
        }

        if (space_contains(current_space, object_get_id(o))) {
          if (obj1[0] != '\0') strcat(obj1, ", ");
          strcat(obj1, object_get_name(o));
        }
      }

      if (strlen(obj) > SPACE_WIDTH) {
        obj[SPACE_WIDTH] = '\0';
        obj[SPACE_WIDTH - 1] = '.';
        obj[SPACE_WIDTH - 2] = '.';
        obj[SPACE_WIDTH - 3] = '.';
      }

      if (strlen(obj1) > SPACE_WIDTH) {
        obj1[SPACE_WIDTH] = '\0';
        obj1[SPACE_WIDTH - 1] = '.';
        obj1[SPACE_WIDTH - 2] = '.';
        obj1[SPACE_WIDTH - 3] = '.';
      }

      sprintf(str, "|%-15s|  |%-15s|", obj, obj1);
      screen_area_puts(ge->map, str);

      sprintf(str, "+---------------+  +---------------+");
      screen_area_puts(ge->map, str);
    }
  } else {
    if ((east_id = space_get_east(current_space)) != NO_ID) {
      aux_space2 = game_get_space(game, east_id);

      sprintf(str, "                   +---------------+  +---------------+");
      screen_area_puts(ge->map, str);
      
      if (space_get_character(current_space) == NO_ID)
        sprintf(gdesc_current, "      ");
      else
        sprintf(gdesc_current, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(current_space))));
      
      if (space_get_character(aux_space2) == NO_ID)
        sprintf(gdesc_east, "      ");
      else
        sprintf(gdesc_east, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(aux_space2))));
      
      sprintf(str, "                   | mO^ %s %-3ld|  |     %s %-3ld|", 
              gdesc_current, current_id, 
              gdesc_east, east_id);
      screen_area_puts(ge->map, str);

      gdesc2 = space_get_gdesc(current_space);
      gdesc3 = space_get_gdesc(aux_space2);

      for (i = 0 ; i < GDESC_HEIGHT ; i++) {
        if (i == GDESC_HEIGHT/2) {
          sprintf(str, "                   |%9s      |->|%9s      |", gdesc2[i], gdesc3[i]);
          screen_area_puts(ge->map, str);
          continue;
        }
        
        sprintf(str, "                   |%9s      |  |%9s      |", gdesc2[i], gdesc3[i]);
        screen_area_puts(ge->map, str);
      }

      obj1[0] = '\0';
      obj2[0] = '\0';

      for (i = 0 ; i < game_get_number_objects(game) ; i++) {
        if (space_contains(current_space, object_get_id(o = game_get_object_at(game, i)))) {
          if (obj1[0] != '\0') strcat(obj1, ", ");
          strcat(obj1, object_get_name(o));
        }

        if (space_contains(aux_space2, object_get_id(o))) {
          if (obj2[0] != '\0') strcat(obj2, ", ");
          strcat(obj2, object_get_name(o));
        }

      }

      if (strlen(obj1) > SPACE_WIDTH) {
        obj1[SPACE_WIDTH] = '\0';
        obj1[SPACE_WIDTH - 1] = '.';
        obj1[SPACE_WIDTH - 2] = '.';
        obj1[SPACE_WIDTH - 3] = '.';
      }

      if (strlen(obj2) > SPACE_WIDTH) {
        obj2[SPACE_WIDTH] = '\0';
        obj2[SPACE_WIDTH - 1] = '.';
        obj2[SPACE_WIDTH - 2] = '.';
        obj2[SPACE_WIDTH - 3] = '.';
      }
      
      sprintf(str, "                   |%-15s|  |%-15s|", obj1, obj2);
      screen_area_puts(ge->map, str);
      
      sprintf(str, "                   +---------------+  +---------------+");
      screen_area_puts(ge->map, str);
    } else {

      sprintf(str, "                   +---------------+");
      screen_area_puts(ge->map, str);
      
      if (space_get_character(current_space) == NO_ID)
        sprintf(gdesc_current, "      ");
      else
        sprintf(gdesc_current, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(current_space))));
      
      sprintf(str, "                   | mO^ %s %-3ld|", gdesc_current, current_id);
      screen_area_puts(ge->map, str);

      gdesc2 = space_get_gdesc(current_space);

      for (i = 0 ; i < GDESC_HEIGHT ; i++) {
        if (i == GDESC_HEIGHT/2) {
          sprintf(str, "                   |%9s      |", gdesc2[i]);
          screen_area_puts(ge->map, str);
          continue;
        }
        
        sprintf(str, "                   |%9s      |", gdesc2[i]);
        screen_area_puts(ge->map, str);
      }

      obj1[0] = '\0';

      for (i = 0 ; i < game_get_number_objects(game) ; i++) {
        if (space_contains(current_space, object_get_id(o = game_get_object_at(game, i)))) {
          if (obj1[0] != '\0') strcat(obj1, ", ");
          strcat(obj1, object_get_name(o));
        }

      }

      if (strlen(obj1) > SPACE_WIDTH) {
        obj1[SPACE_WIDTH] = '\0';
        obj1[SPACE_WIDTH - 1] = '.';
        obj1[SPACE_WIDTH - 2] = '.';
        obj1[SPACE_WIDTH - 3] = '.';
      }
      
      sprintf(str, "                   |%-15s|", obj1);
      screen_area_puts(ge->map, str);
      
      sprintf(str, "                   +---------------+");
      screen_area_puts(ge->map, str);
    }
  }

  if ((south_id = space_get_south(current_space)) != NO_ID) {
    aux_space1 = game_get_space(game, south_id);

    sprintf(str, "                           v");
    screen_area_puts(ge->map, str);

    sprintf(str, "                   +---------------+");
    screen_area_puts(ge->map, str);
    
    if (space_get_character(aux_space1) == NO_ID)
      sprintf(gdesc_south, "      ");
    else
      sprintf(gdesc_south, "%-6s", character_get_gdesc(game_get_character(game, space_get_character(aux_space1))));
    
    sprintf(str, "                   |     %s %-3ld|", gdesc_south, south_id);
    screen_area_puts(ge->map, str);

    gdesc1 = space_get_gdesc(aux_space1);
    for (i = 0 ; i < GDESC_HEIGHT ; i++) {
      sprintf(str, "                   |%9s      |", gdesc1[i]);
      screen_area_puts(ge->map, str);
    }

    obj[0] = '\0';

    for (i = 0 ; i < game_get_number_objects(game) ; i++) {
      if (space_contains(aux_space1, object_get_id(o = game_get_object_at(game, i)))) {
        if (obj[0] != '\0') strcat(obj, ", ");
        strcat(obj, object_get_name(o));
      }
    }
    if (strlen(obj) > SPACE_WIDTH) {
      obj[SPACE_WIDTH] = '\0';
      obj[SPACE_WIDTH - 1] = '.';
      obj[SPACE_WIDTH - 2] = '.';
      obj[SPACE_WIDTH - 3] = '.';
    }

    sprintf(str, "                   |%-15s|", obj);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   +---------------+");
    screen_area_puts(ge->map, str);
  }
}

void graphic_engine_paint_feedback(Graphic_engine *ge, Game *game) {
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char str[128];
  Command *command = NULL;
  CommandCode last_cmd = UNKNOWN;

  if (!ge || !game) return;

  last_cmd = command_get_code(command = game_get_last_command(game));

  if (command_get_status(command) == ERROR) {
    sprintf(str, " %s (%s): ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  } else {
    sprintf(str, " %s (%s): OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);    
  }
  
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

  if (command_get_code(game_get_last_command(game)) == CHAT && command_get_status(game_get_last_command(game)) == OK) {
    sprintf(str, "Player has chatted with: %s", character_get_name(game_get_character(game, space_get_character(game_get_space(game, game_get_player_location(game))))));
    if (strlen(str) > WIDTH_DES) {
      str[WIDTH_DES] = '\0';
      str[WIDTH_DES - 1] = '.';
      str[WIDTH_DES - 2] = '.';
      str[WIDTH_DES - 3] = '.';      
    }

    screen_area_puts(ge->descript, str);
    sprintf(str, "Message: %s", game_get_chat_message(game));
    if (strlen(str) > WIDTH_DES) {
        str[WIDTH_DES] = '\0';
        str[WIDTH_DES - 1] = '.';
        str[WIDTH_DES - 2] = '.';
        str[WIDTH_DES - 3] = '.';
    }
    screen_area_puts(ge->descript, str);

  } else {
    sprintf(str, "Player has not chatted with anyone.");
    if (strlen(str) > WIDTH_DES) {
        str[WIDTH_DES] = '\0';
        str[WIDTH_DES - 1] = '.';
        str[WIDTH_DES - 2] = '.';
        str[WIDTH_DES - 3] = '.';
    }
    screen_area_puts(ge->descript, str);
  }

  /***********************************/
}

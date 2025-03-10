/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/** macro defines the maximum size of a command code */
#define CMD_LENGHT 30

/** macro defines the maximum size of a complement name */
#define COMPLEMENT_LENGTH 30

/** global variable to commmand.c that will match user input to the corresponding commands */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"},  {"l", "Left"},  {"r", "Right"}, {"t", "Take"}, {"d", "Drop"}, {"a", "Attack"}};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code; /*!< Name of the command */
  char complement[COMPLEMENT_LENGTH];    /*!< Name of the complement command */
};

/** command_create allocates memory for a new command
 *  and initializes its members
 * 
 */
Command* command_create(void) {
  Command* newCommand = NULL;

  newCommand = (Command*)malloc(sizeof(Command));
  if (newCommand == NULL) {
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;

   /* Initialization of an empty complement*/
   newCommand->complement[0] = '\0';

  return newCommand;
}

/** command_destroy frees memory allocated for a given command and
 * detangles pointer  
 * 
*/
Status command_destroy(Command* command) {
  if (!command) {
    return ERROR;
  }

  free(command);
  command = NULL;
  return OK;
}

/** command_set_code receives a command code and assigns it to a given 
 * command variable
 * 
*/
Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code=code;

  return OK;
}

/** command_get_code retrieves the code contained in a certain command
 * variable
 * 
*/
CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }
  return command->code;
}

/** command_set_complement receives a complement (string of chars) and assigns it to a given 
 * command variable
 * 
*/
Status command_set_complement(Command* command, char *complement) {
  if (!command) {
    return ERROR;
  }
  strcpy(command->complement, complement);


  return OK;
}

/** command_get_complement retrieves the command contained in a certain command
 * variable
 * 
*/
char* command_get_complement(Command* command) {
  if (!command) {
    return NULL;
  }
  return command->complement;
}

/** command_get_user_input interprets user input and determines which 
 * command code it is correspondent to
 * 
*/
Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  /* parameter validation */
  if (!command) {
    return ERROR;
  }

  /* input interpretation */
  if (fgets(input, CMD_LENGHT, stdin)) {
    /* break input according to empty-space or new-line characters*/
    token = strtok(input, " \n");
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      /* Match input according to its code (b/n/e/l/r/t/d) or meaning (Back/Next/Exit/Left/Right/Take/Drop) */
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
      } else {
        i++;
      }
    }
    /* Set the command code */
    command_set_code(command, cmd);

    /* If the command is TAKE, read the complement */
    if (cmd == TAKE) {
      token = strtok(NULL, " \n");
      if (token) {
        command_set_complement(command, token);
      } else {
        command_set_complement(command, ""); /*Set an empty complement if none is done*/
      }
    }

    return OK;
  }
  else
    return command_set_code(command, EXIT);
  
}

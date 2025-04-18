/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 2.0.2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 11

/** CommandType enum definition used in command_get_user_input 
 * in the command.c file
*/
typedef enum { CMDS, CMDL } CommandType;

/** Command code enum definition
 * 
*/
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, LEFT, RIGHT, TAKE, DROP, ATTACK, CHAT } CommandCode;

/** alias for the _Command struct defined in command.c
 * 
*/
typedef struct _Command Command;

/** 
 * @brief Allocates memory for a new command variable
 * @author PPROG Group 2 - GPA
 * 
 * @return Returns newly allocated command variable
*/
Command* command_create(void);

/** 
 * @brief Frees memory allocated for a given command and detangles pointer
 * @author Profesores PPROG
 * 
 * @param command pointer to command variable to be destroyed
 * @return OK if everything went well or ERROR if an error ocurred
*/
Status command_destroy(Command* command);

/** 
 * @brief Assigns a given code to a certain command->code variable
 * @author Profesores PPROG
 * 
 * @param command pointer to command variable to be modified
 * @param code CommandCode variable to be assigned
 * @return OK if everything went well or ERROR if an error ocurred
*/
Status command_set_code(Command* command, CommandCode code);

/** 
 * @brief Retrieves the code contained in a certain command structure
 * @author Profesores PPROG
 * 
 * @param command pointer to command variable to be read
 * @return command->code variable
*/
CommandCode command_get_code(Command* command);

/** 
 * @brief Assigns a given complement to a certain command->complement variable
 * @author PPROG Group 2 - AGL
 * 
 * @param command pointer to command variable to be modified
 * @param complement Complement variable to be assigned
 * @return OK if everything went well or ERROR if an error ocurred
*/
Status command_set_complement(Command* command, char *complement);

/** 
 * @brief Retrieves the complement contained in a certain command structure
 * @author PPROG Group 2 - AGL
 * 
 * @param command pointer to command variable to be read
 * @return command->complement variable (string of characters)
*/
char* command_get_complement(Command* command);

/** 
 * @brief fetches the status of a given commmand execution
 * @author PPROG Group 2 - GPA
 * 
 * @param command command variable containing result of command execution
 * @return a Status variable, OK/ERROR.
*/
Status command_get_status(Command *command);

/**
 * @brief sets whether a given command was successful or not
 * @author PPROG Group 2 - GPA
 * 
 * @param command command structure to be modified 
 * @param status Status variable containing success/failure information relative to the command
 * @return OK if everything went well or ERROR if an error occurred
*/
Status command_set_status(Command *command, Status status);

/** 
 * @brief Interprets user input and matches it to corresponding code making use of char *cmd_to_str from command.c
 * @author PPROG Group 2 - GPA
 * 
 * @param command pointer to command variable to be modified
 * @return OK if everything went well or ERROR if an error ocurred
*/
Status command_get_user_input(Command* command);

#endif

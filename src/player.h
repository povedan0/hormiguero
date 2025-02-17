/** @brief It defines the player data structure and the functions necessary for its management 
 * 
 * @file player.h
 * @author PPROG - Grupo 2 - GPA
 * @version 0
 * @date 08-02-2025
 * @copyright GNU Public License
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/** alias for the Player data structure */
typedef struct _Player Player;

/* 
    Public functions
*/

/** 
 * @brief Allocates memory for a given player and initializes its members
 * @author PPROG Group 2 (GPA)
 * 
 * @param id The id of the player to be created
 * @return NULL if an error occurred or a pointer to the newly created player variable
 * 
*/
Player *player_create(Id id);

/** 
 * @brief Frees any memory allocated for a given player
 * @author PPROG Group 2 (GPA)
 * 
 * @param player A pointer to the player variable that will be freed
 * @return OK if everything went well or ERROR if an error occurred
*/
Status player_destroy(Player *player);

/** 
 * @brief gets the id number of a given player
 * @author PPROG Group 2 (GPA)
 * 
 * @param player A pointer to the player variable whose id will be fetched
 * @return The player_id in question, or NO_ID if an error occurred
*/
Id player_get_id(Player *player);

/**
 * @brief initializes the player->name field to match a given name
 * @author PPROG Group 2 (GPA)
 * 
 * @param player a pointer to the player structure to be modified 
 * @param name an array of characters cointaining the new name
 * @return OK if everything went well or ERROR if an error occurred
*/
Status player_set_name(Player *player, char *name);

/** 
 * @brief fetches the name of a given player
 * @author PPROG Group 2 (GPA)
 * 
 * @param player a pointer to player structure whose name will be fetched
 * @return a pointer to the player name, or NULL if an error occurred
*/
const char *player_get_name(Player *player);

/** 
 * @brief initializes player->location_id to match a certain location_id
 * @author PPROG Group 2 (GPA)
 * 
 * @param player a pointer to player struct whose location will be modified
 * @param location_id the new player location_id
 * @return OK if everything went well or ERROR if an error occurred
*/
Status player_set_location(Player *player, Id location_id);

/** 
 * @brief gets the id number of a given player's location
 * @author PPROG Group 2 (GPA)
 * 
 * @param player A pointer to the player variable whose location id will be fetched
 * @return The player_location_id in question, or NO_ID if an error occurred
*/
Id player_get_location(Player *player);

/** 
 * @brief initializes player->object_id to match a certain object_id
 * @author PPROG Group 2 (GPA)
 * 
 * @param player a pointer to player struct whose location will be modified
 * @param object_id the new player object_id
 * @return OK if everything went well or ERROR if an error occurred
*/
Status player_set_object_id(Player *player, Id object_id);

/** 
 * @brief gets the id number of a given player's object 
 * @author PPROG Group 2 (GPA)
 * 
 * @param player A pointer to the player variable whose object id will be fetched
 * @return The player_object_id in question, or NO_ID if an error occurred
*/
Id player_get_object_id(Player *player);

/** 
 * @brief Prints all the player information to stdout
 * @author PPROG Group 2 (GPA)
 * 
 * @param player A pointer to the player struct whose information will be printed
 * @return OK if everything went well or ERROR if an error occurred
*/
Status player_print(Player *player);

#endif

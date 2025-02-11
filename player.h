/**
 * @brief It defines the space module interface
 *
 * @file player.h
 * @author 
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

 #ifndef PLAYER_H
 #define PLAYER_H
 
 #include "types.h"
 
 typedef struct _Player Player;
 
 /**
  * @brief It creates a new player, allocating memory and initializing its members
  * @author 
  *
  * @param 
  * @return a new player, initialized
  */
 Player* player_create(Id id);
 
 /**
  * @brief It destroys a player, freeing the allocated memory
  * @author 
  *
  * @param player a pointer to the player that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status player_destroy(Player* player);
 
 /**
  * @brief It gets the id of a player
  * @author 
  *
  * @param player a pointer to the player
  * @return the id of player
  */
 Id player_get_id(Player* player);
 
 /**
  * @brief It sets the name of a player
  * @author 
  *
  * @param player a pointer to the player
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status player_set_name(Player* player, char* name);
 
 /**
  * @brief It gets the name of a player
  * @author 
  *
  * @param player a pointer to the player
  * @return  a string with the name of the player
  */
 const char* player_get_name(Player* player);
 
  /*set the location of a player*/
  Status player_set_location(Player* player, Id location);


 /*player_get_location:  gets the location of a player*/
 Id player_get_location(Player* player);

 /*set the object carried out by a player*/
 Status player_set_object(Player* player, Id object);


 /*player_get_object:  gets the object-id carried out by a player*/
 Id player_get_object(Player* player);


 
 /**
  * @brief It prints the player information
  * @author 
  *
  * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
  * @param player a pointer to the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 /*print the player information*/
 Status player_print(Player* player);
 
 #endif
 
/**
 * @brief It implements the space module
 *
 * @file player.c
 * @author 
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

#include "player.h"
#include "object.h"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 /**
  * @brief player
  *
  * This struct stores all the information of a player.
  */
 struct _Player {
   Id id;                    /*!< Id number of the player, it must be unique */
   char name[WORD_SIZE + 1]; /*!< Name of the player */
   Id location;                 /*!< Id of the space where the player is located */
   Id object;              /*!<object carried out by the player */
 };
 
 /** player_create allocates memory for a new player and initializes its members  */
 Player* player_create(Id id) {
   Player* newPlayer = NULL;
 
   /* Error control */
   if (id == NO_ID ) return NULL;
 
   newPlayer = (Player*)malloc(sizeof(Player));
   if (newPlayer == NULL) {
     return NULL;
   }
 
   /* Initialization of an empty player*/
   newPlayer->id = id;
   newPlayer->name[0] = '\0';
   newPlayer->location = NO_ID;
   newPlayer->object=NO_ID;
  
   return newPlayer;
 }
 
 /*player_destroy: destroys a player, freeing the allocated memory*/
 Status player_destroy(Player* player) {
   if (!player) {
     return ERROR;
   }
 
   free(player);
   /*player = NULL;*/
   return OK;
 }
 
 /*player_get_id:  gets the id of a player*/
 Id player_get_id(Player* player) {
   if (!player) {
     return NO_ID;
   }
   return player->id;
 }
 
 /*set the name of a player*/
 Status player_set_name(Player* player, char* name) {
   if (!player || !name) {
     return ERROR;
   }
 
   if (!strcpy(player->name, name)) {
     return ERROR;
   }
   return OK;
 }
 
 /*get the name of a player*/
 const char* player_get_name(Player* player) {
   if (!player) {
     return NULL;
   }
   return player->name;
 }


 /*set the location of a player*/
 Status player_set_location(Player* player, Id location) {
    if (!player || location == NO_ID) {
      return ERROR;
    }
    player->location = location;
    return OK;
  }


 /*player_get_location:  gets the location of a player*/
 Id player_get_location(Player* player) {
    if (!player) {
      return NO_ID;
    }
    return player->location;
  }


 /*set the object carried out by a player*/
 Status player_set_object(Player* player, Id object) {
    if (!player || object == NO_ID) {
      return ERROR;
    }
    player->object = object;
    return OK;
  }



/*player_get_object: gets the object-id carried out by a player*/
 Id player_get_object(Player* player) {
    if (!player) {
      return NO_ID;
    }
    return player->object;
  }
 

/*print the player information*/
  Status player_print(Player* player) {
    Id idaux=NO_ID;
     
    /* Error Control */
    if (!player) {
      return ERROR;
    }
  
    /* 1. Print the id and the name of the of the player */
    fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

    /*2. Print location of the player and object if their id is different from NO_ID*/
    idaux = player_get_location(player);
    if (idaux != NO_ID) {
    fprintf(stdout, "---> Location of the player: %ld.\n", idaux);
    } else {
    fprintf(stdout, "---> Player in any location.\n");
    }

    idaux = player_get_object(player);
    if (idaux != NO_ID) {
    fprintf(stdout, "---> Object carried by the player: %ld.\n", idaux);
    } else {
    fprintf(stdout, "---> The player carries no object.\n");
    }


    return OK;
  }
 
 
  
 
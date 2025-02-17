/** 
 * @brief Implements functions relative to the Player data structure and its fields. 
 * 
 * @file player.c
 * @author PPROG Group 2 (GPA)
 * @version 0
 * @date 08-02-2025
 * @copyright GNU Public License
*/

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** 
 * @brief Player 
 * 
 * This struct contains all the information relative to a Player
*/
struct _Player {
    char name[WORD_SIZE + 1];    /*!< Name of the player */
    Id player_id;                /*!< Id of the player */
    Id object_id;                /*!< Id of the object being carried by the player */  
    Id location_id;              /*!< Id of the current player location */
};


/** player_create allocates memory for a new player variable and initializes its members */
Player *player_create(Id id) {
    Player *player=NULL; 

    /* Error checking */
    if (!(player = (Player *)malloc(sizeof(Player))) || id == NO_ID) {
        return NULL;
    }

    /* variable initializations */
    player->player_id=id;
    player->location_id=NO_ID;
    player->object_id=NO_ID;
    player->name[0] = 0;

    /* Correct exit */
    return player;
}

/** player destroy frees any previously allocated memory for a given player */
Status player_destroy(Player *player) {
    /* Error checking */
    if (!player) {
        return ERROR;
    }

    /* Memory de-allocation */
    free(player);
    return OK;
}

/** player_get_id fetches the id number of a given player */
Id player_get_id(Player *player) {
    /* Error checking */
    if (!player) return NO_ID;

    return player->player_id;
}

/** player_set_name initializes the player->name field to match a given name */
Status player_set_name(Player *player, char *name) {
    /* Error checking */
    if (!player || !name) return ERROR;

    /* variable assignment */
    if (!(strcpy(player->name, name))) return ERROR;

    /* Correct exit */
    return OK;
}

/** player_get_name fetches a given player's name */
const char *player_get_name(Player *player) {
    if (!player) return NULL;

    return player->name;
}

/** player_set_location_id initializes player->location_id to match a certain location_id */
Status player_set_location(Player *player, Id location_id) {
    /* Error checking */
    if (!player || location_id == NO_ID) {
        return ERROR;
    }
 
    player->location_id = location_id;
 
    /* Correct exit */
    return OK;
}

/** player_get_location_id gets the id number of a given player's location*/
Id player_get_location(Player *player) {
    if (!player) return NO_ID;

    return player->location_id;
}

/** player_set_object_id initializes player->object_id to match a certain object_id*/
Status player_set_object_id(Player *player, Id object_id) {
    if (!player) return ERROR; /* removed object_id != NO_ID clause, conflict with game actions drop */

    player->object_id = object_id;

    return OK;
}

/** player_get_object_id gets the id number of a given player's object */
Id player_get_object_id(Player *player) {
    if (!player) return NO_ID;

    return player->object_id;
}

/** player_print prints all the player information */
Status player_print(Player *player) {
    Id idaux = NO_ID;

    if (!player) {
        return ERROR;
    }

    fprintf(stdout, "--> Player: (id: %ld | name: %s)\n", player->player_id, player->name);

    idaux = player_get_location(player);
    if (idaux != NO_ID) {
        fprintf(stdout, "--> Player location Id: %ld \n", idaux);
    } else {
        fprintf(stdout, "--> No location Id found. \n");
    }
    idaux = player_get_object_id(player);
    if (idaux != NO_ID) {
        fprintf(stdout, "--> Object Id: %ld \n", idaux);
    } else {
        fprintf(stdout, "--> No object Id found. \n");
    }

    return OK;
}

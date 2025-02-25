/** 
 * @brief Implements functions relative to the Character data structure and its fields. 
 * 
 * @file character.c
 * @author  PPROG - Grupo 2 - AGL
 * @version 0
 * @date 25-02-2025
 * @copyright GNU Public License
*/


#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** 
 * @brief Character 
 * 
 * This struct contains all the information relative to a Character
*/
struct _Character {
    Id  character_id;               /*!< Id of the character */
    char name[WORD_SIZE + 1];       /*!< Name of the character */
    char gdesc[GDESC_SIZE];                  /*!< Graphical description of the character */
    int health;                     /*!< Number of health points of the character */
    Bool friendly;                  /*!< Boolean indicating whether the character is friendly (TRUE) */  
    char message[WORD_SIZE + 1];    /*!< Message */
};


/** character_create allocates memory for a new character variable and initializes its members */
Character *character_create(Id id) {
    Character *character=NULL; 

    /* Error checking */
    if (!(character = (Character *)malloc(sizeof(Character))) || id == NO_ID) {
        return NULL;
    }

    /* variable initializations */
    character->name[0] = '\0';
    character->gdesc[0] = '\0';
    character->health = MAX_HEALTH_POINTS;  /* Set health to the maximum health points*/
    character -> friendly = TRUE;
    character->message[0] = '\0';           /*Set friendly to TRUE*/
    
    /* Correct exit */
    return character;
}

/** character_destroy frees allocated memory for a Character variable*/
Status character_destroy(Character *character) {
    /* Error checking */
    if (!character) {
        return ERROR;
    }

    /* Memory de-allocation */
    free(character);
    /*successful free*/
    return OK;
}

/** character_get_id returns the Id of a given character */
Id character_get_id(Character *character) {
    /* Error checking */
    if (!character) return NO_ID;

    return character->character_id;
}

/** character_set_name initializes the character->name field to match a given name */
Status character_set_name(Character *character, char *name) {
    /* Error checking */
    if (!character || !name) return ERROR;

    if (strlen(name) > WORD_SIZE) return ERROR;

    /* variable assignment */
    if (!(strcpy(character->name, name))) return ERROR;

    /* Correct exit */
    return OK;
}

/** character_get_name returns the name of a given*/
const char *character_get_name(Character *character) {
    if (!character) return NULL;

    return character->name;
}

/** Initializes the character->gdesc field to match a given gdesc */
Status character_set_gdesc(Character *character, char *gdesc) {
    /* Error checking */
    if (!character || !gdesc) return ERROR;

    if (strlen(gdesc) >= sizeof(character->gdesc)) return ERROR;

    /* variable assignment */
    if (!(strcpy(character->gdesc, gdesc))) return ERROR;

    /* Correct exit */
    return OK;
}

/** character_get_gdesc returns the graphical description of a given character */
const char *character_get_gdesc(Character *character) {
    if (!character) return NULL;

    return character->gdesc;
}

/**character_get_health returns the health of a given character */
int character_get_health(Character *character){

    if (!character) return -1; /*return error code if character pointer is NULL */

    return character->health;
}

/** character_increase_health increases the health of the given character */
Status character_increase_health(Character *character, int health_points) {

    if (!character  || (health_points <= 0)) return ERROR;

    if(character ->health == MAX_HEALTH_POINTS){
        return OK;
    }else{

        character ->health += health_points;
        if(character ->health > MAX_HEALTH_POINTS){
            character ->health = MAX_HEALTH_POINTS;
        }

    }
    return OK;
}

/** character_remove_health decreases the health of the given character */
Status character_remove_health(Character *character, int health_points) {

    if (!character  || (health_points <= 0)) return ERROR;

    character->health -= health_points; 

    /*health does not go below zero */
    if (character->health < 0) {
        character->health = 0;
    }
    return OK;
}

/**character_get_friendly returns whether the character is friendly*/
Bool character_get_friendly(Character *character) { return character->friendly; }

/**character_set_friendly sets the friendly or unfrendly nature of the character*/
Status character_set_friendly(Character *character, Bool friendly) {
  character->friendly = friendly;

  return OK;
}

/** character_set_message sets the message of a given character */
Status character_set_message(Character *character, char *message) {
    /* Error checking */
    if (!character || !message) return ERROR;

    if (strlen(message) > WORD_SIZE) return ERROR;

    /* variable assignment */
    if (!(strcpy(character->message, message))) return ERROR;

    /* Correct exit */
    return OK;
}

/** character_get_message fetches a given character's message */
const char *character_get_message(Character *character) {
    if (!character) return NULL;

    return character->message;
}

/** character_print prints all the character information */
Status character_print(Character *character) {
   
    if (!character) {
        return ERROR;
    }

    fprintf(stdout, "--> Character: (id: %ld | name: %s)\n", character->character_id, character->name);

    if(character_get_friendly(character) == TRUE){
        fprintf(stdout, "--> The character %s is friendly. \n", character->name);
    }else{
        fprintf(stdout, "--> The character %s is unfriendly. \n", character->name);
    }

    fprintf(stdout, "--> Health of the character: %d \n", character_get_health(character));

    fprintf(stdout, "--> Message of the character: %s \n", character_get_message(character));

    fprintf(stdout, "--> Graphical description of the character: %s \n", character_get_gdesc(character));

    return OK;
}

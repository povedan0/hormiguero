/** 
 * @brief Defines the character test interface 
 * 
 * @file character_test.h
 * @author PPROG Group 2 - GPA
 * @version 1.0.1
 * @date 22-02-2025
 * @copyright GNU Public License
*/

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

#include "character.h"
#include "test.h"
#include "types.h"

/**  
 * @test Test character creation with valid ID  
 * @pre character_create() function must be available and used with a valid ID  
 * @post Character is successfully created  
 */  
void test1_character_create();

/**  
 * @test Test character creation with specific ID  
 * @pre character_create() function must be available and used with a specific valid ID  
 * @post Character is successfully created with the correct ID  
 */  
void test2_character_create();

/**  
 * @test Test character creation with invalid ID  
 * @pre character_create() function must be available and used with an invalid ID  
 * @post Character creation fails  
 */  
void test3_character_create();

/**  
 * @test Test character destruction with NULL pointer  
 * @pre character_destroy() function must be available and called on a NULL character  
 * @post Operation returns ERROR  
 */  
void test1_character_destroy();

/**  
 * @test Test character destruction with valid character  
 * @pre character_create() and character_destroy() functions must be available; character must be created before destruction  
 * @post Character is successfully destroyed  
 */  
void test2_character_destroy();

/**  
 * @test Test setting character name with NULL character  
 * @pre character_set_name() function must be available and called with a NULL character instance  
 * @post Operation returns ERROR  
 */  
void test1_character_set_name();

/**  
 * @test Test setting character name with NULL string  
 * @pre character_create() must be called to create a valid character; character_set_name() must be called with a NULL string  
 * @post Operation returns ERROR  
 */  
void test2_character_set_name();

/**  
 * @test Test setting an overly long character name  
 * @pre character_create() must be called to create a valid character; character_set_name() must be called with an overly long name  
 * @post Operation returns ERROR  
 */  
void test3_character_set_name();

/**  
 * @test Test setting a valid character name  
 * @pre character_create() must be called to create a valid character; character_set_name() must be used with a valid name  
 * @post Name is successfully set  
 */  
void test4_character_set_name();

/**  
 * @test Test retrieving set character name  
 * @pre character_create() must be called to create a valid character; character_set_name() must set a name before retrieval  
 * @post Retrieved name matches the set name  
 */  
void test5_character_set_name();

/**  
 * @test Test setting character graphic description with NULL character  
 * @pre character_set_gdesc() must be available and called with a NULL character instance  
 * @post Operation returns ERROR  
 */  
void test1_character_set_gdesc();

/**  
 * @test Test setting character graphic description with NULL string  
 * @pre character_create() must be called to create a valid character; character_set_gdesc() must be called with a NULL string  
 * @post Operation returns ERROR  
 */  
void test2_character_set_gdesc();

/**  
 * @test Test setting an overly long character graphic description  
 * @pre character_create() must be called to create a valid character; character_set_gdesc() must be used with an overly long description  
 * @post Operation returns ERROR  
 */  
void test3_character_set_gdesc();

/**  
 * @test Test setting a valid character graphic description  
 * @pre character_create() must be called to create a valid character; character_set_gdesc() must be used with a valid description  
 * @post Graphic description is successfully set  
 */  
void test4_character_set_gdesc();

/**  
 * @test Test retrieving set character graphic description  
 * @pre character_create() must be called to create a valid character; character_set_gdesc() must set a description before retrieval  
 * @post Retrieved graphic description matches the set description  
 */  
void test5_character_set_gdesc();

/**  
 * @test Test increasing health of NULL character  
 * @pre character_increase_health() must be available and called with a NULL character instance  
 * @post Operation returns ERROR  
 */  
void test1_character_increase_health();

/**  
 * @test Test increasing health with negative value  
 * @pre character_create() must be called to create a valid character; character_increase_health() must be called with a negative value  
 * @post Operation returns ERROR  
 */  
void test2_character_increase_health();

/**  
 * @test Test increasing health with positive value  
 * @pre character_create() must be called to create a valid character; character_increase_health() must be called with a positive value  
 * @post Health increases successfully  
 */  
void test3_character_increase_health();

/**  
 * @test Test increasing health beyond max limit  
 * @pre character_create() must be called to create a valid character; character_increase_health() must be used with a value exceeding the max limit  
 * @post Health is set to max limit  
 */  
void test4_character_increase_health();

/**  
 * @test Test increasing health after a prior health reduction  
 * @pre character_create() must be called to create a valid character; character_remove_health() must be used before increasing health again  
 * @post Health increases but does not exceed max limit  
 */  
void test5_character_increase_health();

/**  
 * @test Test removing health from NULL character  
 * @pre character_remove_health() must be available and called with a NULL character instance  
 * @post Operation returns ERROR  
 */  
void test1_character_remove_health();

/**  
 * @test Test removing health with negative value  
 * @pre character_create() must be called to create a valid character; character_remove_health() must be called with a negative value  
 * @post Operation returns ERROR  
 */  
void test2_character_remove_health();

/**  
 * @test Test removing more health than available  
 * @pre character_create() must be called to create a valid character; character_remove_health() must be used with a value exceeding the current health  
 * @post Health is set to zero  
 */  
void test3_character_remove_health();

/**  
 * @test Test removing health within valid range  
 * @pre character_create() must be called to create a valid character; character_remove_health() must be used with a valid reduction amount  
 * @post Health decreases successfully  
 */  
void test4_character_remove_health();

/**  
 * @test Test retrieving correct health after reduction  
 * @pre character_create() must be called to create a valid character; character_remove_health() must be used before retrieving health  
 * @post Retrieved health matches expected value  
 */  
void test5_character_remove_health();

/**  
 * @test Test setting friendly status on NULL character  
 * @pre character_set_friendly() must be available and called with a NULL character instance  
 * @post Operation returns ERROR  
 */  
void test1_character_set_friendly();

/**  
 * @test Test setting friendly status on valid character  
 * @pre character_create() must be called to create a valid character; character_set_friendly() must be used to set friendly status  
 * @post Friendly status is successfully set  
 */  
void test2_character_set_friendly();

/**  
 * @test Test setting message on NULL character  
 * @pre character_set_message() must be available and called with a NULL character instance  
 * @post Operation returns ERROR  
 */  
void test1_character_set_message();

/**  
 * @test Test setting message with NULL string  
 * @pre character_create() must be called to create a valid character; character_set_message() must be called with a NULL string  
 * @post Operation returns ERROR  
 */  
void test2_character_set_message();

/**  
 * @test Test setting an overly long message  
 * @pre character_create() must be called to create a valid character; character_set_message() must be used with an overly long message  
 * @post Operation returns ERROR  
 */  
void test3_character_set_message();

/**  
 * @test Test setting a valid message  
 * @pre character_create() must be called to create a valid character; character_set_message() must be used with a valid message  
 * @post Message is successfully set  
 */  
void test4_character_set_message();

/**  
 * @test Test retrieving set message  
 * @pre character_create() must be called to create a valid character; character_set_message() must set a message before retrieval  
 * @post Retrieved message matches the set message  
 */  
void test5_character_set_message();

/**  
 * @test Test retrieving ID from NULL character  
 * @pre character_get_id() must be available and called with a NULL character instance  
 * @post Operation returns NO_ID  
 */  
void test1_character_get_id();

/**  
 * @test Test retrieving ID from valid character  
 * @pre character_create() must be called to create a valid character before calling character_get_id()  
 * @post Retrieved ID matches the assigned ID  
 */  
void test2_character_get_id();

/**  
 * @test Test retrieving name from NULL character  
 * @pre character_get_name() must be available and called with a NULL character instance  
 * @post Operation returns NULL  
 */  
void test1_character_get_name();

/**  
 * @test Test retrieving name from a character with a set name  
 * @pre character_create() must be called to create a valid character; character_set_name() must be used before retrieval  
 * @post Retrieved name matches the set name  
 */  
void test2_character_get_name();

/**  
 * @test Test retrieving graphic description from NULL character  
 * @pre character_get_gdesc() must be available and called with a NULL character instance  
 * @post Operation returns NULL  
 */  
void test1_character_get_gdesc();

/**  
 * @test Test retrieving graphic description from a character with a set description  
 * @pre character_create() must be called to create a valid character; character_set_gdesc() must be used before retrieval  
 * @post Retrieved graphic description matches the set description  
 */  
void test2_character_get_gdesc();

/**  
 * @test Test retrieving health from NULL character  
 * @pre character_get_health() must be available and called with a NULL character instance  
 * @post Operation returns -1  
 */  
void test1_character_get_health();

/**  
 * @test Test retrieving initial health of a valid character  
 * @pre character_create() must be called to create a valid character before calling character_get_health()  
 * @post Retrieved health matches initial max health  
 */  
void test2_character_get_health();

/**  
 * @test Test retrieving friendly status from NULL character  
 * @pre character_get_friendly() must be available and called with a NULL character instance  
 * @post Operation returns FALSE  
 */  
void test1_character_get_friendly();

/**  
 * @test Test retrieving friendly status from valid character  
 * @pre character_create() must be called to create a valid character before calling character_get_friendly()  
 * @post Retrieved friendly status is TRUE  
 */  
void test2_character_get_friendly();

/**  
 * @test Test retrieving message from NULL character  
 * @pre character_get_message() must be available and called with a NULL character instance  
 * @post Operation returns NULL  
 */  
void test1_character_get_message();

/**  
 * @test Test retrieving message from valid character  
 * @pre character_create() must be called to create a valid character before calling character_get_message()  
 * @post Retrieved message is not NULL  
 */  
void test2_character_get_message();

#endif 

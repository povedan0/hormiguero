/**
 * @brief Defines space module test functions and macros
 * 
 * @file space_test.h
 * @author PPROG Group 2 - GPA
 * @version 0.0
 * @date 24-02-2025
 * @copyright GNU Public License 
*/

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

#include "space.h"
#include "types.h"
#include "test.h"

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

/**  
 * @test Test setting north space  
 * @pre Valid space and north ID  
 * @post Operation returns OK  
 */ 
void test1_space_set_north();

/**  
 * @test Test setting north space with NULL space  
 * @pre NULL space  
 * @post Operation returns ERROR  
 */  
void test2_space_set_north();

/**  
 * @test Test setting south space  
 * @pre Valid space and south ID  
 * @post Operation returns OK  
 */  
void test1_space_set_south();

/**  
 * @test Test setting south space with NULL space  
 * @pre NULL space  
 * @post Operation returns ERROR  
 */  
void test2_space_set_south();

/**  
 * @test Test setting east space  
 * @pre Valid space and east ID  
 * @post Operation returns OK  
 */  
void test1_space_set_east();

/**  
 * @test Test setting east space with NULL space  
 * @pre NULL space  
 * @post Operation returns ERROR  
 */  
void test2_space_set_east();

/**  
 * @test Test setting west space  
 * @pre Valid space and west ID  
 * @post Operation returns OK  
 */  
void test1_space_set_west();

/**  
 * @test Test setting west space with NULL space  
 * @pre NULL space  
 * @post Operation returns ERROR  
 */  
void test2_space_set_west();

/**  
 * @test Test adding object to space  
 * @pre Valid space and object ID  
 * @post Operation returns OK  
 */  
void test1_space_add_object_id();

/**  
 * @test Test adding object to NULL space  
 * @pre NULL space  
 * @post Operation returns ERROR  
 */  
void test2_space_add_object_id();

/**  
 * @test Test adding invalid object ID to space  
 * @pre Valid space, invalid object ID  
 * @post Operation returns ERROR  
 */  
void test3_space_add_object_id();

/**  
 * @test Test retrieving space ID  
 * @pre Valid space with ID  
 * @post Retrieved ID matches expected value  
 */  
void test1_space_get_id();

/**  
 * @test Test retrieving space ID from NULL space  
 * @pre NULL space  
 * @post Returned ID is NO_ID  
 */  
void test2_space_get_id();

/**  
 * @test Test retrieving space name  
 * @pre Valid space with set name  
 * @post Retrieved name matches expected value  
 */  
void test1_space_get_name();

/**  
 * @test Test retrieving space name from NULL space  
 * @pre NULL space  
 * @post Returned name is NULL  
 */  
void test2_space_get_name();


/**  
 * @test Test retrieving north space  
 * @pre Space with north set  
 * @post Retrieved north ID matches expected value  
 */  
void test1_space_get_north();

/**  
 * @test Test retrieving north space from NULL space  
 * @pre NULL space  
 * @post Retrieved ID is NO_ID  
 */  
void test2_space_get_north();

/**  
 * @test Test retrieving south space  
 * @pre Space with south set  
 * @post Retrieved south ID matches expected value  
 */  
void test1_space_get_south();

/**  
 * @test Test retrieving south space from NULL space  
 * @pre NULL space  
 * @post Retrieved ID is NO_ID  
 */  
void test2_space_get_south();

/**  
 * @test Test retrieving east space  
 * @pre Space with east set  
 * @post Retrieved east ID matches expected value  
 */  
void test1_space_get_east();

/**  
 * @test Test retrieving east space from NULL space  
 * @pre NULL space  
 * @post Retrieved ID is NO_ID  
 */  
void test2_space_get_east();

/**  
 * @test Test retrieving west space  
 * @pre Space with west set  
 * @post Retrieved west ID matches expected value  
 */  
void test1_space_get_west();

/**  
 * @test Test retrieving west space from NULL space  
 * @pre NULL space  
 * @post Retrieved ID is NO_ID  
 */  
void test2_space_get_west();

/**  
 * @test Test retrieving space objects  
 * @pre Space with objects  
 * @post Retrieved objects are non-NULL  
 */  
void test1_space_get_objects();

/**  
 * @test Test retrieving space objects from empty space  
 * @pre Space with no objects  
 * @post Retrieved objects are NULL  
 */  
void test2_space_get_objects();

/**  
 * @test Test retrieving space objects from NULL space  
 * @pre NULL space  
 * @post Retrieved objects are NULL  
 */  
void test3_space_get_objects();

/**  
 * @test Test retrieving number of objects from NULL space  
 * @pre NULL space  
 * @post Returned value is -1  
 */  
void test1_space_get_number_objects();

/**  
 * @test Test retrieving number of objects from empty space  
 * @pre Valid space with no objects  
 * @post Returned value is 0  
 */  
void test2_space_get_number_objects();

/**  
 * @test Test retrieving number of objects in a space  
 * @pre Space containing objects  
 * @post Retrieved number matches expected value  
 */  
void test3_space_get_number_objects();

/**  
 * @test Test checking object containment in space  
 * @pre Space with an object  
 * @post Function returns TRUE  
 */  
void test1_space_contains();

/**  
 * @test Test checking object containment in NULL space  
 * @pre NULL space  
 * @post Function returns FALSE  
 */  
void test2_space_contains();

/**  
 * @test Test checking containment of invalid object ID  
 * @pre Valid space, invalid object ID  
 * @post Function returns FALSE  
 */  
void test3_space_contains();

/**  
 * @test Test checking containment of non-existent object  
 * @pre Valid space, object not in space  
 * @post Function returns FALSE  
 */  
void test4_space_contains();

/**  
 * @test Test deleting an object ID from a space  
 * @pre Valid space with object ID  
 * @post Object ID successfully removed  
 */  
void test1_space_del_object_id();

/**  
 * @test Test deleting an object ID from a NULL space  
 * @pre NULL space  
 * @post Function returns error  
 */  
void test2_space_del_object_id();

/**  
 * @test Test deleting an invalid object ID  
 * @pre Valid space with an invalid object ID  
 * @post Function returns error  
 */  
void test3_space_del_object_id();

/**  
 * @test Test checking if space is full with a NULL space  
 * @pre NULL space  
 * @post Function returns TRUE  
 */  
void test1_space_objects_is_full();

/**  
 * @test Test checking if space is full with an empty space  
 * @pre Empty space  
 * @post Function returns FALSE  
 */  
void test2_space_objects_is_full();

/**  
 * @test Test setting a character in a space  
 * @pre Valid space and character ID  
 * @post Character successfully set  
 */  
void test1_space_set_character();

/**  
 * @test Test setting a character in a NULL space  
 * @pre NULL space  
 * @post Function returns error  
 */  
void test2_space_set_character();

/**  
 * @test Test retrieving character from a space  
 * @pre Valid space with a character  
 * @post Retrieved character matches expected value  
 */  
void test1_space_get_character();

/**  
 * @test Test retrieving character from a NULL space  
 * @pre NULL space  
 * @post Function returns NO_ID  
 */  
void test2_space_get_character();

/**  
 * @test Test setting graphical description in a space  
 * @pre Valid space with graphical description  
 * @post Function successfully sets description  
 */  
void test1_space_set_gdesc();

/**  
 * @test Test setting graphical description in a NULL space  
 * @pre NULL space  
 * @post Function returns error  
 */  
void test2_space_set_gdesc();

/**  
 * @test Test retrieving graphical description from a space  
 * @pre Valid space with graphical description  
 * @post Function returns non-NULL description  
 */  
void test1_space_get_gdesc();

/**  
 * @test Test retrieving graphical description from a NULL space  
 * @pre NULL space  
 * @post Function returns NULL  
 */  
void test2_space_get_gdesc();

/**  
 * @test Test destroying a valid space  
 * @pre Valid space  
 * @post Space successfully destroyed  
 */  
void test1_space_destroy();

/**  
 * @test Test destroying a NULL space  
 * @pre NULL space  
 * @post Function returns error  
 */  
void test2_space_destroy();


#endif

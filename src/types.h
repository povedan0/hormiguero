/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1 /** constant for an invalid ID */

typedef long Id; /** alias for long integer */

typedef enum { FALSE, TRUE } Bool; /** boolean variable declaration */

typedef enum { ERROR, OK } Status; /** define status variable for improved function readability */

typedef enum { N, S, E, W } Direction; /** define direction type with values N (North), S (South), E (East), and W (West) */

#endif

/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author PPROG - Grupo 2 - GPA, AGL
 * @version 1.0.1
 * @date 27-01-2025
 * @copyright GNU Public License
*/

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /** constant for the size of variable names */
#define NO_ID -1 /** constant for an invalid ID */

typedef long Id; /** alias for long int */

typedef enum { FALSE, TRUE } Bool; /** boolean variable declaration */

typedef enum { ERROR, OK } Status; /** define status variable for improved function readability */

#endif

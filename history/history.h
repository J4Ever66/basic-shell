/**
 * @file history.h
 * @author Stu Steiner
 * @date 12 Jan 2016
 * @brief Supporting functions for the history
 *
 * The purpose of this file is to outline functions to help build a basic
 * history linked list
 *
 * @note This file will never be changed
 */

#ifndef HISTORY_H
#define HISTORY_H


#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


/**
 * @brief The history data structure.
 *
 * A history contains an int for the number of arguments and a char ** for the actual arguments
 *
 * @note I prefer named structures and then the typedef after the structure
 */
struct hist
{
	int ID;
	int argc;
	char ** argv;
};

typedef struct hist history;

/**
 * @brief The Make Args function from the last lab
 *
 * Copy and Paste MakeArgs from the last lab
 *
 * @param s - The String to be tokenized
 * @param argv - The array to put the tokens into
 *
 * @warning - If there are no tokens or the String cant be parsed - exit(-99) 
 */
// TOOK OUT MAKEARGS ( in tokenize )
/**
 * @brief The builds the history data structure
 *
 * Builds the history structure and returns it as a void pointer
 *
 * @param argc - The int for the number of arguments
 * @param argv - The array to put the tokens into
 * @return void * - Representing the data structure history
 *
 * @warning - If there are no tokens or the String is null - exit(-99) 
 */
void * build_History(int argc, char **argv, int*);

#endif

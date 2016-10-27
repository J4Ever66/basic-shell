/**
 * @file genericData.h
 * @author Stu Steiner
 * @date 29 Dec 2015
 * @brief The basic genericData.h file contains the prototypes for your specific type functions
 *
 * The genericData.h specifies the standard set of functions required for any type to
 * work with your generic linked list.
 *
 * @note This file will never be changed
 */

#ifndef GENERICDATA_H
#define GENERICDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "requiredIncludes.h"

void printHistory(void * passedIn); 
void * buildType(FILE * fin);
void * buildType_Prompt(FILE * fin);
int compareAlias(void * p1, void * p2);
int compareHistLast(char*, void*);
int comparePaths(char*, void*);
int getHistID(void*);
char* formatHist(void*);
char** getAliasArgv(void*);
int getAliasArgc(void*);
char** getHistArgv(void*);
int getHistArgc(void*);
int compareHistID(void* p1, int histID);
void cleanHistory(void * passedIn);
void cleanAlias(void * passedIn);
void cleanUnAlias(void * passedIn);
void cleanPath(void*);


#endif // GENERICDATA_H

#ifndef PATHS_H
#define PATHS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../linkedlist/linkedList.h"
#include "../linkedlist/listUtils.h"
#include "../utils/myUtils.h"
struct path
{
	char* pathDir;
};

typedef struct path Paths;


void add2PathList(LinkedList*, char*);
void * build_Path(char*);
char* getCmdPath(char** argv);

#endif

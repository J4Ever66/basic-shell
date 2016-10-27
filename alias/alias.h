#ifndef ALIAS_H
#define ALIAS_H

//#include "../linkedlist/genericData.h"
//#include "../linkedlist/linkedList.h" 
//#include "../linkedlist/listUtils.h" -- was causing errors
#include "../tokenize/makeArgs.h"

struct ali
{
	char * aliasID; // alias name
	int argc;
	char ** argv; // actual command for alias
};

typedef struct ali Alias;

void * build_Alias(char*);
void * build_UnAlias(char*);
void * build_SearchAlias(char*);

#endif

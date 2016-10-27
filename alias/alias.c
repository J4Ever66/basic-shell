#include "alias.h"


void * build_Alias(char* aliasP){
	Alias * a1 = (Alias*)calloc(1, sizeof(Alias));	
	char *temp = NULL, *strTokenr, *copy = (char*)calloc(strlen(aliasP) + 1, sizeof(char));
	int count = 0, argc2 = 0;
	strcpy(copy, aliasP);
	temp = strtok_r(copy, " =\"", &strTokenr);  
	while(temp != NULL){
		if(count == 0){
			temp = strtok_r(NULL, " =\"", &strTokenr);
			a1->aliasID = (char*)calloc(strlen(temp) + 1, sizeof(char));
			strcpy(a1->aliasID, temp);
		}else if(count == 1){
			temp = strtok_r(NULL, "\"", &strTokenr);
			char ** tempArgs = NULL;
			argc2 = makeargs(temp, &tempArgs); 
			a1->argc = argc2;
			a1->argv = tempArgs;
		}else{
			temp = strtok_r(NULL, " =\"", &strTokenr);
		}
		count++;
	}

	free(copy);
	copy = NULL;
	return (void*)a1;
}
void * build_UnAlias(char* unaliasP){ // "unalias ALIAS"
	Alias * a1 = (Alias*)calloc(1, sizeof(Alias));	
	char *temp = NULL, *strTokr = NULL, *copy = (char*)calloc(strlen(unaliasP) + 1, sizeof(char));
	strcpy(copy, unaliasP);
	int count = 0;
	temp = strtok_r(copy, " ", &strTokr); // extracts "unalias"  
	while(temp != NULL){
		if(count == 1){
			a1->aliasID = (char*)calloc(strlen(temp) + 1, sizeof(char));
			strcpy(a1->aliasID, temp);
		}
		temp = strtok_r(NULL, " ", &strTokr);
		count++;
	}
	free(copy);
	copy = NULL;
	return (void*)a1;
}
void * build_SearchAlias(char* alias){ // "ALIAS" -- RETURNING NODE TO SEARCH FOR
	Alias * a1 = (Alias*)calloc(1, sizeof(Alias));
	a1->aliasID = (char*)calloc(strlen(alias) + 1, sizeof(char));
	strcpy(a1->aliasID, alias);
	return (void*)a1;
}

int compareAlias(void * p1, void * p2){ 
	if(p1 == NULL || p2 == NULL){ 
		printf("One or more of passed in void pointer(s) are NULL.\n"); 
		exit(-99);
	}
	Alias * a1 = (Alias*)p1;
	Alias * a2 = (Alias*)p2;
	return strcmp(a1->aliasID, a2->aliasID);
}


char** getAliasArgv(void* b){
	Alias * a1 = (Alias*)b;
	char** tempArgv = (char**)calloc(a1->argc + 1, sizeof(char*));
	int x = 0;
	for(x = 0; x < a1->argc; x++){
		tempArgv[x] = (char*)calloc(strlen(a1->argv[x]) + 1, sizeof(char));
		strcpy(tempArgv[x], a1->argv[x]);
	}
	tempArgv[x] = '\0'; // ADD ON \0 FOR ARGS IN ORDER FOR ALIAS TO EXECUTE
	return tempArgv;
}
int getAliasArgc(void* a){
	Alias * a1 = (Alias*)a;	
	return a1->argc;
}

void cleanAlias(void * passedIn){
	int x = 0;	
	Alias * a1 = (Alias*)passedIn;
	free(a1->aliasID);
	a1->aliasID = NULL;
	for(x = 0; x < a1->argc; x++){ // ARGC should NOT include \0
		free(a1->argv[x]); 
		a1->argv[x] = NULL;
	}
	a1->argv[x] = NULL;
	free(a1->argv);
	a1->argv = NULL;

}
void cleanUnAlias(void * passedIn){ // only free's ID -- removeItem will take care of freeing passedIn
	Alias * a1 = (Alias*)passedIn;
	free(a1->aliasID);
	a1->aliasID = NULL;
}

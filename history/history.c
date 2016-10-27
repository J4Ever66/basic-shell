#include "history.h"

void * build_History(int argcP, char **argvP, int* idCount){
	history * h1 = (history*)calloc(1, sizeof(history));
	h1->argc = argcP;
	h1->argv = (char**)calloc(argcP + 1, sizeof(char*)); // \0 at end
	int x = 0;
	for(x = 0; x < argcP; x++){
		h1->argv[x] = (char*)calloc(strlen(argvP[x]) + 1, sizeof(char));
		strcpy(h1->argv[x], argvP[x]);
	}
	h1->argv[x] = argvP[x]; // \0
	h1->ID = *idCount;
	*idCount = ((*idCount) + 1); // everytime a new history is made -- adds to the ID
	return (void*)h1;
}
int compareHistLast(char* cmd, void* p2){
	int res = 1;
	if(p2 == NULL){ // DATA DOES NOT EXIST(no elements)
	
	}else{
		history * h1 = (history*)p2;
		int x = 0, cmdSize = 0, y = 0;
		for(y = 0; y < h1->argc; y++){
			if(y < ((h1->argc)-1)){ // add extra index for space
				cmdSize = (cmdSize + strlen(h1->argv[y]) + 1); //WHOLE COMMAND + " " -- then for '\0' at end
			}else{ // no extra index for space
				cmdSize = (cmdSize + strlen(h1->argv[y]));
			}
		}
		char * cmd2 = (char*)calloc(cmdSize + 1, sizeof(char)); // (+1) for null terminator
		for(x = 0; x < h1->argc; x++){
			strcat(cmd2, h1->argv[x]); // add chunk of command
			if(x < ((h1->argc)-1)){ // should not execute on last run
				strcat(cmd2, " "); // add space in between commands
			}
		}
		res = strcmp(cmd, cmd2);
		free(cmd2);
		cmd2 = NULL;
	}	
	return res;
}
int compareHistID(void* p1, int histID){
	history * h1 = (history*)p1;
	return (histID - h1->ID);
}
int getHistID(void* p1){
	history * h1 = (history*)p1;
	int ret = h1->ID;
	return ret;
}
void printHistory(void * passIn){
	if(passIn == NULL){
		printf("printType: passIn is NULL.\n");
		exit(-99);
	}else{
		history * h1 = (history*)passIn;
			int x = 0;
			printf("%d ", h1->ID);
			for(x = 0; x < h1->argc; x++){
				printf("%s ", h1->argv[x]);
			}
			printf("\n");
	}
}
char* formatHist(void* p2){
	history * h1 = (history*)p2;
		int x = 0, cmdSize = 0, y = 0;
		for(y = 0; y < h1->argc; y++){
			if(y < ((h1->argc)-1)){ // add extra index for space
				cmdSize = (cmdSize + strlen(h1->argv[y]) + 1); //WHOLE COMMAND + " " -- then for '\0' at end
			}else{ // no extra index for space
				cmdSize = (cmdSize + strlen(h1->argv[y]));
			}
			
		}
		char * cmd2 = (char*)calloc(cmdSize + 1, sizeof(char)); // (+1) for null terminator
		for(x = 0; x < h1->argc; x++){
			strcat(cmd2, h1->argv[x]); // add chunk of command
			if(x < ((h1->argc)-1)){ // should not execute on last run
				strcat(cmd2, " "); // add space in between commands
			}

		}
		return cmd2;
}
void cleanHistory(void * passedIn){
	history * h1 = (history*)passedIn;
	int x = 0;
	for(x = 0; x < h1->argc; x++){ // ARGC should NOT include \0
		free(h1->argv[x]); 
		h1->argv[x] = NULL;
	}// STILL A \0 -- DO NOT FREE IT!
	h1->argv[x] = NULL;
	free(h1->argv);
	h1->argv = NULL;
}
int getHistArgc(void* b){
	history * a1 = (history*)b;
	return a1->argc;
}
char** getHistArgv(void* b){
	history * a1 = (history*)b;
	char** tempArgv = (char**)calloc(a1->argc + 1, sizeof(char*));
	int x = 0;
	for(x = 0; x < a1->argc; x++){
		tempArgv[x] = (char*)calloc(strlen(a1->argv[x]) + 1, sizeof(char));
		strcpy(tempArgv[x], a1->argv[x]);
	}
	tempArgv[x] = '\0'; // ADD ON \0 FOR ARGS IN ORDER FOR HISTORYARGV TO EXECUTE
	return tempArgv;
}

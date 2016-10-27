#include "makeArgs.h"

void clean(int argc, char **argv)
{	
	if(argc < 1 || argv == NULL){
	//printf("No elements or argv is NULL\n");
	}else{
		int x = 0;
		for(x = 0; x < argc; x++){ 
			free(argv[x]); // free data
			argv[x] = NULL; // free ptr
		}
		//free(argv[argc]); WAS TRYING TO FREE '\0' BUT DONT NEED TO
		argv[argc] = NULL;
		free(argv); // main sets to NULL for us
	}
}// end clean

void printargs(int argc, char **argv)
{
	if(argc > 0){
		int x;
		for(x = 0; x < argc; x++){
			printf("%s\n", argv[x]);
		}
	}else{
		printf("List empty.\n");
	}

}// end printargs

int makeargs(char *s, char *** argv)
{
	int argc = 0, x = 0;
	if(s == NULL){
		argc = -1;
	}else{ //s is already stripped in main, no carriage return
	//count for argc

	char *temp = NULL, *strTokr, *copy = (char*)calloc(strlen(s) + 1, sizeof(char));

	strcpy(copy, s);
	temp = strtok_r(copy, "\n\t\r ", &strTokr); 
	while(temp != NULL){
		argc++;
		temp = strtok_r(NULL, "\n\t\r ", &strTokr);
	}
	free(copy);
	copy = NULL;
	char **args = (char**)calloc(argc + 1, sizeof(char*));
	copy = (char*)calloc(strlen(s) + 1, sizeof(char)); // REMAKE COPY -- DO NOT STRIP S
	strcpy(copy, s);
	temp = strtok_r(copy, "\n\t\r ", &strTokr); // save (char*) to each index of (char**)
	while(temp != NULL){
		args[x] = (char*)calloc(strlen(temp) + 1, sizeof(char)); // not sure if need \0
		strcpy(args[x], temp);
		x++;
		temp = strtok_r(NULL, "\n\t\r ", &strTokr);
	}
	//args[x] = (char*)calloc(1, sizeof(char));
	args[x] = '\0';
	*argv = args;
	free(copy);
	copy = NULL;
	strTokr = NULL;
	}//else
   return argc;
	
}// end makeArgs

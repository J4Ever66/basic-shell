#include "myCD.h"
/*
	IN MAKE FILE THERE ARE TWO TABS AFTER myCD.o:
	NOT SURE WHY IT WASNT LETTING TAB GO MORE THAN ONE SPACE 
	NEEDED TWO AND WORKED APPARENTLY
*/
void changeDirectory(char* passIn){
	char path[PATHMAX], cd[5];
	
	if(strlen(passIn) > 255){
		printf("Path is too long.\n");
	}else{ // path is acceptable size
		sscanf(passIn, "%s%s", cd, path);
		formatPath(path);
		chdir(path);
	}//else
}

void formatPath(char* pathP){ // [./relDir] [/absolute/path]
	char path[PATHMAX], cwd[PATHMAX];
	if(pathP == NULL){
		printf("Path is null.\n");
	}else{
		if((pathP[0] == '.' && pathP[2] == '.' && pathP[3] == '.') || (pathP[0] == '.' && pathP[1] == '.')){ 
			getcwd(cwd, sizeof(cwd)); // RELATIVE PATH ADDS ON TO CURRENT ABSOLUTE PATH
			char temp[250];
			strcpy(temp, pathP);
			memset(pathP, '\0', (strlen(pathP) - 1) * sizeof(char)); // RESET PATH
			strcat(pathP, cwd); // [CWD]
			strcat(pathP, "/");
			strcat(pathP, temp); // [CWD]+[./../..]
			
		}
		if(pathP[strlen(pathP)] != '/'){
				strcat(pathP, "/");
		}

		if(pathP[0] == '/'){ // ABSOLUTE DIRECTORY "/dirs" -- MIGHT NEED TO EXTRACT THE FIRST '/' BEFORE SENDING TO FORMAT
			formatDirectPath(pathP);
		}else{ // relative directory "./dirs"
			if(pathP[0] == '.'){
				int count = 0;
				char *temp, *strTokr = NULL, pathCopy[PATHMAX], pathCopy2[PATHMAX];
				strcpy(pathCopy, pathP);
				temp = strtok_r(pathCopy, "/", &strTokr);
				while(temp != NULL){
					if(count == 0){ // should have [./] <-> [dir1/dir2/dir3] split -- ready for formatting
						strcpy(pathCopy2, strTokr);
					}
					count++;
					temp = strtok_r(NULL, "/", &strTokr);
				}
				formatDirectPath(pathCopy2);
				memset(pathP, '\0', (strlen(pathP) - 1) * sizeof(char)); // RESET PATH
				getcwd(cwd, sizeof(cwd)); // RELATIVE PATH ADDS ON TO CURRENT ABSOLUTE PATH
				strcat(pathP, cwd); // ABSOLUTE PATH
				strcat(pathP, pathCopy2); // + RELATIVE PATH
			}else{
				printf("Not a valid path.\n");
			}
		}  	
		
	
	}//else	
}//formatPath

void formatDirectPath(char* pathP){ // FORMATS PATH WITH ".."'s in it
		char pathCopy[PATHMAX], *strT = NULL, temp[PATHMAX];	//may need extra temp for STRTOK
		strcpy(pathCopy, pathP);
		strT = strtok(pathCopy, "/"); 
		int directoryCount = 0;
		while(strT != NULL){ // temp1 can NEVER be NULL in the method
			if(strcmp(strT, ".") != 0){ // COUNT NUMBER OF .
				directoryCount++;
			}
			strT = strtok(NULL, "/");	
		}//count signifies the number of directories
		char ** direct = (char**)calloc(directoryCount, sizeof(char*)); // create DOUBLE ARRAY
		memset(pathCopy, '\0', (strlen(pathCopy) - 1) * sizeof(char)); // RESET pathCopy
		//Load up directory/filename holder array
		int x = 0;
		strcpy(pathCopy, pathP);//RECOPY -- REPERFORM EXCEPT THIS TIME, SAVES INTO ARRAY!
		strT = strtok(pathCopy, "/"); 
		while(strT != NULL){ // Take out any "."
			if(strcmp(strT, ".") != 0){
				direct[x] = (char*)calloc(strlen(strT) + 1, sizeof(char));
				strcpy(direct[x], strT);
				strT = strtok(NULL, "/");	
				x++;
			}else{
				strT = strtok(NULL, "/");
			}
		}
		/* WE NOW HAVE TO ACCOUNT FOR ANY '..' */
		char noCopy[4] = {'$', '$', '$', '\0' }; // strlen copy????????
		int t = 0, howMany = 0, start = 0;
		for(t = 0; t < (directoryCount - 1); t++){
			if(strcmp(direct[t + 1], "..") == 0){
				start = t + 2;
				while((start) < directoryCount){ 	
					if(strcmp(direct[start], "..") == 0){
						howMany++; 
						start++;
					}else{ // no more remaining in this chain
						start = directoryCount; // end
					}	
				}
				if(howMany > 0){ // (t-..)(t-1)(deleteDIR)-howMany ([t][t+1]) howmany("..")(t+2)(t+..)
					int u = 0; // FIX FOR CURRENT INDEX[t] && INDEX[t + 1]='..'
					for(u = 0; u < howMany; u++){
						free(direct[(t + 2) + u]); // (t-1)(t)(t+1)(t+2)
						direct[(t + 2) + u] = NULL;
						direct[(t + 2) + u] = (char*)calloc(strlen(noCopy) + 1, sizeof(char));
						strcpy(direct[(t + 2) + u], noCopy);
	
					}//for
					int e = 0;
					for(e = 0; e < howMany; e++){
						free(direct[(t - 1) - e]);
						direct[(t - 1) - e] = NULL;
						direct[(t - 1) - e] = (char*)calloc(strlen(noCopy) + 1, sizeof(char));
						strcpy(direct[(t - 1) - e], noCopy);
					}
				}//if(howMany
				free(direct[t]); // CHANGE t and corresponding ".." (t+1)
				direct[t] = NULL;
				direct[t] = (char*)calloc(strlen(noCopy) + 1, sizeof(char));
				strcpy(direct[t], noCopy);
				free(direct[t + 1]);
				direct[t + 1] = NULL;
				direct[t + 1] = (char*)calloc(strlen(noCopy) + 1, sizeof(char));
				strcpy(direct[t + 1], noCopy);
				t = (t + howMany); // move t up # of ".."
				howMany = 0;
				start = 0;			
			}//if
		}//for
		memset(pathP, '\0', (strlen(pathP) - 1) * sizeof(char)); // RESET PATH
		int z = 0; 
		for(z = 0; z < directoryCount; z++){ // RECONSTRUCT PATH WITH '/''s
			if(strcmp(direct[z], "$$$") != 0){
				strcat(pathP, "/");
				strcat(pathP, direct[z]);
			}
		}
		if(strlen(pathP) < 1){
			printf("pathP: [%s]\n",pathP);
			strcat(pathP, "/");
			printf("pathP: [%s]\n",pathP);
		}	
		for(z = 0; z < directoryCount; z++){ // free directory char**
			free(direct[z]);
			direct[z] = NULL;
		}
		free(direct);
		direct = NULL;	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./pipes/pipes.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/listUtils.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/requiredIncludes.h"
#include "./utils/myFileUtil.h"
#include "./paths/paths.h"
#include "./mycd/myCD.h"

int main()
{
	int argc = 0, pipeCount = 0, histPrintCount = 100, histFileCount = 1000, histIDCount = 1, tempArgc = -1, histLast = 99, green4Go = -1;	
	char **argv = NULL, s[MAX], cwd[250], **tempArgv = NULL, defPaths[100];
	int preCount = 0, postCount = 0;
	char ** prePipe = NULL, ** postPipe = NULL;
 	FILE * fin = NULL, *fout = NULL;
	LinkedList *history = linkedList(), *alias = linkedList(), *paths = linkedList();

	fin = fopen(".msshrc", "r"); 
	if(fin != NULL){ // CHECK IF FILE EXISTS
		readFile(alias, paths, fin, &histPrintCount, &histFileCount);
		fclose(fin);
	}
	fin = fopen(".msshrc_history", "r");
	if(fin != NULL){ // CHECK IF FILE EXISTS
		readHist(history, fin, &histIDCount, histFileCount); // add all into history -- set histIDCount to last histID added
		fclose(fin);
	}
	strcpy(defPaths, "PATH=$PATH:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games"); // add default paths
	add2PathList(paths, defPaths);
	getcwd(cwd, sizeof(cwd)); // save cwd for history file
	printf("command?: ");
	fgets(s, MAX, stdin);
	strip(s);
	while(strcmp(s, "exit") != 0)
	{
		argc = makeargs(s, &argv);
		histLast = checkLastHistory(history, s, compareHistLast);
		if(histLast != 99){ // might make sure that s does not equal history
			if(histFileCount >= histIDCount){ // list NOT maxed out
				addLast(history, buildNode_Type(build_History(argc, argv, &histIDCount)));
			}else{
				if(histFileCount < histIDCount){ // list MAXED -- delete first add last
					removeFirstHist(history, cleanHistory);
					addLast(history, buildNode_Type(build_History(argc, argv, &histIDCount)));
				}
			}
		}
		if(s[0] == '!' && s[1] == '!'){ // execute last command in history
			clean(argc, argv); // clean argv before next run
			argv = NULL;
			char * temp = findHistory(history, &tempArgv, (histIDCount - 2) , getHistID, formatHist, compareHistID);
			strcpy(s, temp);
			argc = makeargs(temp, &argv);
			free(temp);
			temp = NULL;
		}else if(s[0] == '!' && s[1] != '!'){ // !#
			clean(argc, argv); // clean argv before next run
			argv = NULL;
			char tempC = '$';
			int tempID = 0;
			sscanf(s, "%c%d", &tempC, &tempID); // extract ! -- then ID
			char * temp = findHistory(history, &tempArgv, tempID, getHistID, formatHist, compareHistID);
			strcpy(s, temp);
			argc = makeargs(temp, &argv);
			free(temp);
			temp = NULL;
		}
		tempArgc = findAlias(alias, &tempArgv, buildNode_Type(build_SearchAlias(s)) , getAliasArgv, getAliasArgc, cleanUnAlias, compareAlias); 
		if(tempArgc != -1){ // (-1) OR ARGC(success)
		  	forkIt(tempArgv);
		  	clean(tempArgc, tempArgv); // clean tempArgv/reset tempArgc
			tempArgv = NULL;
		}else{//alias IF/Else
			if(strcmp(s, "history") == 0){
				if(histIDCount > 2){ // if type history as first command with no history -- does not display anything
         				printHistoryList(history, histPrintCount, histFileCount, histIDCount, getHistID,  printHistory);
				}
			}else if(s[0] == 'a' && s[1] == 'l' && s[2] == 'i' && s[3] == 'a' && s[4] == 's'){ // alias ADD
				addLast(alias, buildNode_Type(build_Alias(s)));
			}else if(s[0] == 'u' && s[1] == 'n' && s[2] == 'a' && s[3] == 'l' && s[4] == 'i' && s[5] == 'a' && s[6] == 's'){
				removeItem(alias, buildNode_Type(build_UnAlias(s)), cleanAlias, cleanUnAlias, compareAlias);
			}else if(s[0] == 'c', s[1] == 'd'){ 
				changeDirectory(s);
			}else if(s[0] == 'P' && s[1] == 'A' && s[2] == 'T' && s[3] == 'H'){ 
				add2PathList(paths, s);
			}else{ // REGULAR COMMAND -- POSSIBLE PIPES -- POSSIBLE REDIRECTS
	
				pipeCount = containsPipe(s);
				if(pipeCount > 0){
					prePipe = parsePrePipe(s, &preCount);
					postPipe = parsePostPipe(s, &postCount);
					pipeIt(prePipe, postPipe);
					clean(preCount, prePipe);
	        			clean(postCount, postPipe);
				}else{// end if pipeCount 
					char* cmdPath = getCmdPath(argv);
					green4Go = checkPaths(paths, cmdPath, comparePaths);
					free(cmdPath);
					cmdPath = NULL;
					if(argc != -1 && green4Go != -1){
			  			forkIt(argv);
						green4Go = -1;
					}else{
						printf("Command could not be found.\n");
					}
				}//else(noPipe)
			}//else
		}//aliasElse
		clean(argc, argv); // clean argv before next run
		argv = NULL;
		printf("command?: ");
		fgets(s, MAX, stdin);
	      	strip(s);
 	}// end while
	if(histIDCount > 1){ // only write to file if there is history to write
		char histDir[255] = "";
		strcat(histDir, cwd); // put in cwd
		strcat(histDir, "/.msshrc_history");
		fout = fopen(histDir, "w"); // reset file if exists, or create if it doesnt
		if(fout != NULL){ // should create file 
			writeHist(history, fout, getHistID, formatHist);
		}
		fclose(fout);
	}
	clearList(history, cleanHistory);//DEALLOCATE linkedLists
	free(history);
	history = NULL;
	clearList(alias, cleanAlias);
	free(alias);
	alias = NULL;
	clearList(paths, cleanPath);
	free(paths);
	paths = NULL;
	return 0;
}// end main


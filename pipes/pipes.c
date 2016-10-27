#include "pipes.h"
#include "../tokenize/makeArgs.h"

int containsPipe(char *s){
	char *temp = NULL, *copy = NULL, *strtokr = NULL;
	int pipeCount = 0;
	copy = (char*)calloc(strlen(s) + 1, sizeof(char)); // COPY
	strcpy(copy, s);
	temp = strtok_r(copy, "|", &strtokr);
	while(temp != NULL){
		temp = strtok_r(NULL, "|", &strtokr); 
		if(temp != NULL){ // need at least two parses in order to have ONE pipe
			pipeCount++;
		}
	} 
	free(copy);
	copy = NULL;
	return pipeCount;
}
char ** parsePrePipe(char *s, int * preCount){
	char ** ret = NULL, *pre = NULL, *strtokr = NULL, *copy = NULL;
	copy = (char*)calloc(strlen(s) + 1, sizeof(char)); // COPY
	strcpy(copy, s);

	pre = strtok_r(copy, "|", &strtokr);
	if(pre != NULL){
		*preCount = makeargs(pre, &ret);
	}
	free(copy);
	copy = NULL;
	return ret;
}
char ** parsePostPipe(char *s, int * postCount){
	char ** ret = NULL, *pre = NULL, *strtokr = NULL, *copy = NULL;
	copy = (char*)calloc(strlen(s) + 1, sizeof(char)); // COPY
	strcpy(copy, s);

	pre = strtok_r(copy, "|", &strtokr); // PREPOST "blah |"
	pre = strtok_r(NULL, "|", &strtokr); // pre should now contain POSTPOST " this"
	if(pre != NULL){
		*postCount = makeargs(pre, &ret);
	}
	free(copy);
	copy = NULL;
	return ret;
}
void pipeIt(char ** prePipe, char ** postPipe){
	
	pid_t pid, pid2;
	int fd[2], res = 0, status = 0;
	pid = fork(); // ONLY TOP PARENT RUNS THIS
	waitpid(pid, &status, 0);
	if(pid == 0) // child of root parent
	{
		res = pipe(fd); // CHILD 1 START
		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if
		pid2 = fork(); 
		// CHILD 2 START
		if(pid2 != 0){ // CHILD 1 -- parent of pid2
			waitpid(pid2, &status, 0); // wait for child to finish (ls -l)
			close(fd[1]); // close WRITE(right) end of pipe
			close(0); // close STDIN
			dup(fd[0]); // ALIAS LEFTPIPE -> STDIN
			close(fd[0]); // CLOSE LEFTPIPE
			//command line still executes prePost command even if postPost fails
			if(execvp(postPipe[0], postPipe) == -1){ 
				printf("Command not found.\n"); // execution failed
				exit(-1); // -1 result
			}
			
			exit(-99);
		}else{ // GRANDCHILD(CHILD 2)(its pid2 == 0)
			close(fd[0]); // close in end of PIPE
			close(1); // close STDOUT
			dup(fd[1]); // ALIAS pipe to STDOUT
			close(fd[1]); // then close it
			if(execvp(prePipe[0], prePipe) == -1){
				close(1); // CLOSE STDOUT!!! SO NO INFO GETS THROUGH!
				printf("Command not found.\n"); // execution fails
				exit(-1); // -1 result
			}
			exit(-99);
		}
	}

}

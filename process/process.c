#include "process.h"
#include <sys/types.h>
#include <sys/wait.h> // WAITPID

void forkIt(char ** argv){
	int status = 1;
	pid_t pid = fork();
	if(pid == -1){
		perror("Pid is -1.\n");
		exit(-1);
	}
	if(pid != 0){ // PARENT
		waitpid(pid, &status, 0); // wait for ANY children of THIS parent fork.
	}else{ // CHILD
		if(execvp(argv[0], argv) == -1){
			exit(-99);
		}
	}
}

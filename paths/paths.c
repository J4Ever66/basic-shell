#include "paths.h"

void add2PathList(LinkedList* paths, char* pathsStr){
	char* temp = NULL, *strTokr = NULL;
	temp = strtok_r(pathsStr, ":", &strTokr); // [PATH=$PATH:]<->[PATH1:PATH2:PATH3]
	while(temp != NULL){
		temp = strtok_r(NULL, ":", &strTokr);
		if(temp != NULL){
			addLast(paths, buildNode_Type(build_Path(temp)));
		}
	}
	
}

void * build_Path(char* passPath){
	Paths * p1 = (Paths*)calloc(1, sizeof(Paths));
	p1->pathDir = (char*)calloc(strlen(passPath) + 1, sizeof(char));
	strcpy(p1->pathDir, passPath);
	return (void*)p1;
}
void cleanPath(void* passPath){
	Paths* p1 = (Paths*)passPath;
	free(p1->pathDir);
	p1->pathDir = NULL;
}

int comparePaths(char* path, void* passP){
	Paths * p1 = (Paths*)passP;
	return (strcmp(p1->pathDir, path)); 
}

char* getCmdPath(char** argv){
	pid_t pid;
	int fd[2], res = 0, status = 0, readRes = 0;
	char cmd[255] = "";
	res = pipe(fd);
	if(res < 0){
		printf("Pipe Failure\n");
		exit(-1);
	}// end if

	pid = fork(); // ONLY TOP PARENT RUNS THIS
	if(pid != 0){ //parent
		waitpid(pid, &status, 0); // wait for child to finish
		close(fd[1]); // close WRITE(right) end of pipe
		readRes = read(fd[0], cmd, sizeof(cmd));
		close(fd[0]); // CLOSE LEFTPIPE
		strip(cmd);
		
	}else{ // child
		close(fd[0]); // close in end of PIPE
		close(1); // close STDOUT
		dup(fd[1]); // ALIAS pipe to STDOUT
		close(fd[1]); // then close it
		if(execlp("which", "which", argv[0], NULL) == -1){
			close(1); // CLOSE STDOUT!!! SO NO INFO GETS THROUGH!
			exit(-1); // -1 result
		}
		exit(-99);
	} // child proof from this point on
	int count = 0;
	char* temp = NULL, *strTokr = NULL, *copy = (char*)calloc(strlen(cmd) + 1, sizeof(char));
	strcpy(copy, cmd);
	temp = strtok_r(copy, "/", &strTokr);
	while(temp != NULL){
		count++;
		temp = strtok_r(NULL, "/", &strTokr);
	}
	free(copy);
	copy = NULL;
	char cmdPath[255] = "";
	int count2 = 0;
	temp = strtok_r(cmd, "/", &strTokr);
	while(temp != NULL){ //extract count - 1 total
		if(count2 < count - 1){
			strcat(cmdPath, "/");
			strcat(cmdPath, temp); 
		}
		count2++;
		temp = strtok_r(NULL, "/", &strTokr);
	}
	char* ret = (char*)calloc(strlen(cmdPath) + 1, sizeof(char));
	strcpy(ret, cmdPath);
	return ret;

}

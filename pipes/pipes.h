#ifndef PIPES_H
#define PIPES_H


#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int containsPipe(char *s);
char ** parsePrePipe(char *s, int * preCount);
char ** parsePostPipe(char *s, int * postCount);
void pipeIt(char ** prePipe, char ** postPipe);

#endif 


CC=gcc

lab8:	cscd340hw8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o ./linkedlist/linkedList.o ./alias/alias.o ./utils/myFileUtil.o ./paths/paths.o ./mycd/myCD.o
	gcc -g cscd340hw8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./alias/alias.o ./utils/myFileUtil.o ./paths/paths.o ./mycd/myCD.o -o mssh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

linkedList.o:	./linkedlist/linkedList.h ./linkedlist/linkedList.c ./linkedlist/genericData.h ./linkedlist/requiredIncludes.h
	gcc -c ./linkedlist/linkedList.c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -c ./linkedlist/listUtils.c

history.o:	./history/history.c ./history/history.h
	gcc -g -c ./history/history.c

alias.o:	./alias/alias.c ./alias/alias.h
	gcc -g -c ./alias/alias.c

myFileUtil.o:	./utils/myFileUtil.c ./utils/myFileUtil.h
	gcc -g -c ./utils/myFileUtil.c

paths.o:	./paths/paths.c ./paths/paths.h
	gcc -g -c ./paths/paths.c

myCD.o:		./mycd/myCD.c ./mycd/myCD.h
	gcc -g -c ./mycd/myCD.c


clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./history/history.o
	rm ./linkedlist/*.o
	rm ./alias/alias.o
	rm ./utils/myFileUtil.o
	rm ./mycd/myCD.o
	rm mssh 


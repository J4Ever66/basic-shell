#include "myFileUtil.h"
void readFile(LinkedList* alias, LinkedList* paths, FILE* fin, int* histPrintP, int* histFileP){
	char histPrintCount[25], histFileCount[25], temp[300];	
	fgets(histPrintCount, 24, fin);
	strip(histPrintCount);
	fgets(histFileCount, 24, fin);
	strip(histFileCount);
	
	histPrintCount[9] = ' '; // take out '=' so sscanf works
	sscanf(histPrintCount, "%s%d", temp, histPrintP);
	histFileCount[13] = ' ';
	sscanf(histFileCount, "%s%d", temp, histFileP);
	fgets(temp, 299, fin); // prime read -- does not crash if nothing after histCounts
	strip(temp);
	while(!(feof(fin))){ // read for alias or PATH
	if(temp[0] == 'a' && temp[1] == 'l'){ // alias    
		addLast(alias, buildNode_Type(build_Alias(temp)));
	}else if(temp[0] == 'P' && temp[1] == 'A'){ // PATH
		add2PathList(paths, temp);
	}else{} // do nothing
	fgets(temp, 299, fin);
	strip(temp);
	}//while   
	
}

void readHist(LinkedList* history, FILE* fin, int* histIDCount, int histFileCount){
	int readCount = 0, tempArgc = 0, tempHistID = 0;
	char temp[300], temp2[300], **tempArgv = NULL;
	fgets(temp, 299, fin);
	while(!(feof(fin))){
		strip(temp); // get rid of carriage return
		readCount++; // counting how many history are read in
		sscanf(temp, "%d%s", &tempHistID, temp2); // extract HISTID and command
		tempArgc = makeargs(temp2, &tempArgv); // retrieve double* format for command and argc for adding into history -- allocates for us
		addLast(history, buildNode_Type(build_History(tempArgc, tempArgv, &tempHistID)));// int argcP, char **argvP, int* idCount
		clean(tempArgc, tempArgv); // clean argv before next run
		tempArgv = NULL;
		fgets(temp, 299, fin); // last thing -- reads in NULL - breaks loop		
	}

	if(readCount > histFileCount){ // read in history # > total wanted history # -- delete (total - readInHistory)
		int count = (readCount - histFileCount); // total number we want to delete
		while(count != 0){ // 100 read limit 50 -- 100 - 50 = 50 deletes
			removeFirstHist(history, cleanHistory); // LIST IS MAXED OUT -- remove FIRST ITEM
			count--;
		}
	}
	*histIDCount = tempHistID; // assign last added ID to HISTIDCOUNT
}








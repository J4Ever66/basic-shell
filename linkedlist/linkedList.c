#include "linkedList.h"

LinkedList * linkedList(){
	LinkedList * myList = (LinkedList*)calloc(1, sizeof(LinkedList));
	myList->head = (Node*)calloc(1, sizeof(Node));
	myList->size = 0;
	return myList;
}//ll 

void addLast(LinkedList * theList, Node * nn){
	if(theList == NULL || nn == NULL){
		printf("addLast incoming parameter is NULL.\n"); 
		exit(-99);
	}
	 
	if(theList->size == 0){ addFirst(theList, nn); } 
	else{
		Node *cur = theList->head->next;
		while(cur->next != NULL){ cur = cur->next; } // ..[cur]->NULL
		cur->next = nn;
		nn->prev = cur;
		theList->size++;
	} 	
}//addlast

void addFirst(LinkedList * theList, Node * nn){
	if(theList == NULL || nn == NULL){
		printf("addLast incoming parameter is NULL.\n"); 
		exit(-99);
	} 
	nn->next = theList->head->next; // NULL or first element
	theList->head->next = nn;
	nn->prev = theList->head;
	if(nn->next != NULL){
		nn->next->prev = nn; 
	}
	theList->size++;
}//addfirst

void removeItem(LinkedList * theList, Node * nn, void (*removeData1)(void *), void (*removeData2)(void *), int (*compare)(void *, void *)){
	if(theList == NULL || nn == NULL){
		printf("addLast incoming parameter is NULL.\n"); 
		exit(-99);
	}else if(theList->size == 0){
		printf("No elements to remove. List empty.\n");
	}else{
		int check = theList->size;
		Node *cur = theList->head->next, *previ = theList->head;
		while(cur != NULL){
			if(compare(cur->data, nn->data) == 0){// FOUND 
				removeData1(cur->data); // alias
				free(cur->data);
				cur->data = NULL;
				previ->next = cur->next;
				if(previ->next != NULL){ // NOT NULL AFTER CUR(more elements)
					cur->next->prev = previ;	
				}
				cur->next = NULL;
				cur->prev = NULL;
				free(cur);
				cur = NULL;
				theList->size = (theList->size - 1);
			}else{
				previ = cur;
				cur = cur->next;
			}
		}//while
		if(check == theList->size){ // size hasn't changed since search through
			printf("Alias could not be found.\n");
		}

	}//else if
	removeData2(nn->data); // unalias
	free(nn->data);
	nn->data = NULL;
	free(nn);
	nn = NULL;
}//removeitem

void clearList(LinkedList * theList, void (*removeData)(void *)){ // remove ALL elements
	if(theList == NULL){ printf("List NULL.\n"); }else{
		if(theList->size == 0){
			theList->head->next = NULL;
			free(theList->head);
			theList->head = NULL;
		}else if(theList->size == 1){
			
			Node *cur = theList->head->next;
			removeData(cur->data);
			free(cur->data);
			cur->data = NULL;
			cur->prev = NULL;
			free(cur);
			cur = NULL;
			theList->head->next = NULL;
			free(theList->head);
			theList->head = NULL;
		}else{ // 2 or more elements
			Node *cur = theList->head->next, *prevn = theList->head->next;
			cur = cur->next;
			theList->head->next = NULL;
			free(theList->head);
			theList->head = NULL;
			while(cur != NULL){ // prev is placeholder/eraser -- cur keeps list intact
				removeData(prevn->data); // removes all data inside of void * data(book)
				free(prevn->data); // free void * data(Book)	
				prevn->data = NULL;	
				prevn->prev = NULL; 
				prevn->next = NULL;
				free(prevn); // free NODE
				prevn = NULL;
				
				prevn = cur; // move up one element for prev & cur -- same index as cur
				cur = cur->next; 
				if(cur == NULL){ // prev is on the LAST index
					prevn->prev = NULL; 
					prevn->next = NULL;
					removeData(prevn->data); // remove inner
					free(prevn->data); // free DATA(book)
					prevn->data = NULL;
					free(prevn); // free NODE
					prevn = NULL;	
				}					
			}//while
		}		
		theList->size = 0;
	} //else -- empty list by here
} // clear

void printHistoryList(LinkedList *history, int printSize, int histSize, int histIDCount, int (*getHistID)(void*), void (*convertData)(void*)){
	Node* cur = history->head->next;
	if(histIDCount > printSize){ // traverse (histIDCount - printSize) for START
		int startVal = ((histIDCount - printSize) - 1), curVal = 0;
		while(cur != NULL && curVal <= startVal){ // will traverse until cur Node's ID is equal to STARTVAL
			curVal = getHistID(cur->data);
			if(curVal <= startVal){ // prevent traverse extra node if start node found
				cur = cur->next;
			}
		} // AT THIS POINT -- we SHOULD be at the start node to start printing
		while(cur != NULL){
			convertData(cur->data);
			cur = cur->next;
		}

	}else{ // PRINT WHOLE LIST
		while(cur != NULL){
			convertData(cur->data);
			cur = cur->next;
		}	
	}

}

void writeHist(LinkedList* hist, FILE* fout, int (*getHistID)(void*), char* (*convertData)(void*)){
	if(hist == NULL || hist->size == 0){
		//do nothing
	}else{
		char * temp = NULL;
		int id = 0;
		Node *cur = hist->head->next;
		while(cur != NULL){ 
			temp = convertData(cur->data); 
			id = getHistID(cur->data);
			fprintf(fout, "%d %s\n", id, temp);
			free(temp); // temp allocated in formatHist(for only this purpose)
			temp = NULL;
			cur = cur->next;
		}
	}
}//printlist

int findAlias(LinkedList * myList, char*** tempArgv, Node *nn , char** (*getAliasArgv)(void*), int (*getAliasArgc)(void*), void (*removeData)(void*), int (*compare)(void *, void *)){
	int tempArgc = -1;	
	//printf("findAlias begin\n");
	Node * cur = myList->head;
	cur = cur->next;
	while(cur != NULL && tempArgc == -1){ 
		//printf("findAlias searching\n");
		if(compare(cur->data, nn->data) == 0){ // found
			//printf("findAlias FOUND\n");
			*tempArgv = getAliasArgv(cur->data); // \0 is tacked on!
			tempArgc = getAliasArgc(cur->data);
				
		}
		cur = cur->next;
	}
	removeData(nn->data); 
	free(nn->data);
	nn->data = NULL;
	free(nn);
	nn = NULL;
	
	return tempArgc; // nothing found --(-1)
}

char* findHistory(LinkedList * myList, char*** tempArgv, int histIDCount, int (*getHistID)(void*), char* (*formatHist)(void*), int (*compareHistID)(void *, int)){
	int tempArgc = -1;
	char* temp = NULL;	
	Node * cur = myList->head;
	cur = cur->next;
	while(cur != NULL && tempArgc == -1){ 
		if(compareHistID(cur->data, histIDCount) == 0){ // found
			temp = formatHist(cur->data);
			tempArgc = 0; // break out of loop	
		}else{
			cur = cur->next;
		}
	}
	return temp;
}

int checkLastHistory(LinkedList* history, char* cmd, int (*compareHistLast)(char*, void*)){	
	Node* cur = history->head;
	int ret = 99; 
	while(cur->next != NULL){ // go to LAST node
		cur = cur->next;
	}
	ret = compareHistLast(cmd, cur->data);
	if(ret == 0){ // same, dont add
		ret = 99; 
	}
	return ret;
}

void removeFirstHist(LinkedList* history, void (*cleanHistory)(void*)){ // LIST IS MAXED OUT -- remove FIRST ITEM
	Node* cur = history->head->next; // 1st element
	Node* connect = cur->next;
	history->head->next = connect; // detach head->[1] to head->[2]
	connect->prev = history->head; // reconnect list
	cleanHistory(cur->data);
	free(cur->data);
	cur->data = NULL;
	cur->next = NULL;
	cur->prev = NULL;
	free(cur);
	cur = NULL;
}

int checkPaths(LinkedList* paths, char* cmdPath, int (*comparePaths)(char*, void*)){
	int breaker = -1;
	Node * cur = paths->head;
	char * temp = NULL;
	cur = cur->next;
	while(cur != NULL && breaker == -1){ 
		if(comparePaths(cmdPath, cur->data) == 0){ // founds
			breaker = 0; // break out of loop	
		}else{
			cur = cur->next;
		}
	}
	return breaker;
}

#include "listUtils.h"

//DONT NEED TO CHECK PASSED IN fin's IN THIS FILE
Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ){
	Node * nn = (Node*)calloc(1, sizeof(Node));
	nn->data = buildData(fin); // returns void*, no cast necessary 
	return nn;

}//buildNode
Node * buildNode_Type(void * passedIn){
	Node * nn = (Node*)calloc(1, sizeof(Node));
	nn->data = passedIn;
	return nn;
}

void buildList(LinkedList * theList, int total, FILE * fin, void * (*buildData)(FILE * in)){
	if(total < 1){
		printf("Total less than 1.\n");
		exit(-99);
	}else if(theList == NULL){
		printf("Incoming parameter myList is NULL.\n");
		exit(-99);
	}
	int x = 0; 
	for(x = 0; x < total; x++){	
		addFirst(theList, buildNode(fin, buildData));
	}
}//buildList



#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genericData.h"


struct node
{
    void * data;
    struct node * next;
    struct node * prev;
};
typedef struct node Node;


struct linkedlist
{
	Node * head;
	int size;
};
typedef struct linkedlist LinkedList;


LinkedList * linkedList();
void addLast(LinkedList * theList, Node * nn);
void addFirst(LinkedList * theList, Node * nn);
void removeItem(LinkedList * theList, Node * nn, void (*removeData1)(void *), void (*removeData2)(void *), int (*compare)( void *,  void *));
char* findHistory(LinkedList * myList, char*** tempArgv, int histIDCount, int (*getHistID)(void*), char* (*formatHist)(void*), int (*compareHistID)(void *, int));
int findAlias(LinkedList * myList, char*** tempArgv, Node *nn , char** (*getArgv)(void*), int (*getArgc)(void*), void (*removeData)(void*), int (*compare)(void *, void *));
int checkPaths(LinkedList*, char*, int (*comparePaths)(char*, void*));
void clearList(LinkedList * theList, void (*removeData)(void *));
void writeHist(LinkedList* hist, FILE* fout, int (*getHistID)(void*), char* (*convertData)(void*));
void printHistoryList(LinkedList *history, int, int, int, int (*getHistID)(void*), void (*convertData)(void*));
int checkLastHistory(LinkedList* history, char* cmd, int (*compareHistLast)(char*, void*));
void removeFirstHist(LinkedList*, void (*cleanHistory)(void*));

#endif // LINKEDLIST_H

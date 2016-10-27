#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <stdio.h>
#include <string.h>

#include "../linkedlist/genericData.h"
#include "../linkedlist/linkedList.h"
#include "../linkedlist/listUtils.h"
#include "./myUtils.h"
#include "../tokenize/makeArgs.h"
#include "../paths/paths.h"

void readFile(LinkedList*, LinkedList*, FILE*, int*, int*);
void readHist(LinkedList*, FILE*, int*, int);
#endif

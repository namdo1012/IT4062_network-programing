#ifdef __FILE_H__
#define __FILE_H__

#include "linkedlist.h"

void readFileToList(linkedList *list);
void appendDataToFile(FILE *file, nodeValType val);
void writeListToFile(linkedList *list);

#endif
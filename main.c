#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

int main()
{
  // printf("Programing...");
  linkedList *list = createSingleList();
  // printf("Programing...");
  insertBegin(list, 2);
  insertBegin(list, 3);
  insertBegin(list, 1);
  insertBegin(list, 4);
  printSingleList(list);

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/* PLAIN TEXT FILE */
void readFileToList(linkedList *list)
{
  nodeValType node;

  // Open account file for reading
  FILE *file;
  if ((file = fopen("account.txt", "r+")) == NULL)
  {
    printf("File not found!\n");
    return;
  }

  // Read to list
  while (!feof(file))
  {
    int scan = fscanf(file, "%s %s %d\n", node.username, node.password, &node.status);
    insertEnd(list, node);
  }

  // Close file
  fclose(file);
}

void appendDataToFile(FILE *file, nodeValType val)
{
  fprintf(file, "%s %s %d\n", val.username, val.password, val.status);
}

void writeListToFile(linkedList *list)
{
  // Open account file for reading
  FILE *file;
  if ((file = fopen("account.txt", "w")) == NULL)
  {
    printf("File not found!\n");
    return;
  }

  // Loop for list to write node to file
  Node *tmp = list->root;
  while (tmp != NULL)
  {
    appendDataToFile(file, tmp->val);
    tmp = tmp->next;
  }

  // Close file
  fclose(file);
}

#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

int getLength(linkedList *list)
{
  int count = 0;
  Node *tmp = list->root;
  while (tmp != NULL)
  {
    tmp = tmp->next;
    count++;
  }

  return count;
}

void printSingleList(linkedList *list)
{
  nodeValType nodeVal;

  // printf("Running...");
  if (list == NULL)
    return;

  Node *tmp = list->root;
  while (tmp != NULL)
  {
    nodeVal = tmp->val;
    printf("%s\t%s\t%d\n", nodeVal.username, nodeVal.password, nodeVal.status);
    tmp = tmp->next;
  }
  printf("\n");
}

void *createSingleList(linkedList *list)
{
  printf("Running: ");
  // linkedList *list;
  list->root = NULL;
  list->tail = NULL;

  // return list;
}

Node *makeNewNode(nodeValType val)
{
  Node *new = (Node *)malloc(sizeof(Node));
  new->val = val;
  new->next = NULL;
  return new;
}

Node *getNodeAt(linkedList *list, int pos)
{
  // If inputed pos is negative, return the root node
  if (pos <= 0)
    return list->root;

  // If inputed pos too greater than list's length, return the tail node
  if (pos > getLength(list))
    return list->tail;

  Node *tmp = list->root;
  int i = 1;
  while (i != pos)
  {
    tmp = tmp->next;
    i++;
  }

  return tmp;
};

Node *insertBegin(linkedList *list, nodeValType val)
{
  Node *new = makeNewNode(val);
  if ((*list).root == NULL)
  {
    (*list).root = (*list).tail = new;
  }
  else
  {
    new->next = (*list).root;
    (*list).root = new;
  }
  return (*list).root;
}

Node *insertEnd(linkedList *list, nodeValType e)
{
  Node *new = makeNewNode(e);
  if (list->root == NULL)
  {
    list->root = list->tail = new;
  }
  else
  {
    list->tail->next = new;
    list->tail = new;
  }
  return list->root;
};

Node *insertAt(linkedList *list, nodeValType e, int pos)
{
  // Find node right before node in pos
  Node *tmp = getNodeAt(list, pos - 1);

  // Insert new node to pos
  Node *new = makeNewNode(e);
  new->next = tmp->next;
  tmp->next = new;

  return list->root;
}

Node *deleteBegin(linkedList *list)
{
  if (list->root != NULL)
  {
    Node *new = list->root;
    list->root = list->root->next;
    free(new);
  }

  return list->root;
};

Node *deleteEnd(linkedList *list)
{
  // Find node right before current tail node
  Node *beforeTail = getNodeAt(list, getLength(list) - 1);

  // Delete tail node
  beforeTail->next = NULL;
  free(list->tail);
  list->tail = beforeTail;

  return list->root;
};

Node *deleteAt(linkedList *list, int pos)
{
  if (pos > getLength(list))
    return NULL;

  // Find node right before node needed to delete
  Node *prevNode = getNodeAt(list, pos - 1);

  // Find current node in pos
  Node *currNode = getNodeAt(list, pos);

  // Delete it
  prevNode->next = currNode->next;
  free(currNode);

  return list->root;
};

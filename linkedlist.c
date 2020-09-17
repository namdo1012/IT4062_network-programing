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
  // printf("Running...");
  if (list == NULL)
    return;

  Node *tmp = list->root;
  while (tmp != NULL)
  {
    printf("%d", tmp->val);
    tmp = tmp->next;
  }
  printf("\n");
}

linkedList *createSingleList()
{
  printf("Running: ");
  linkedList *list;
  list->root = NULL;
  list->tail = NULL;

  return list;
}

Node *makeNewNode(int val)
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

Node *insertBegin(linkedList *list, int val)
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

Node *insertEnd(linkedList *list, int e)
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

Node *insertAt(linkedList *list, int e, int pos)
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

  return list->tail;
};

// Node *deleteSingleList(singleList *list);

// // Xóa tất cả
// node *deleteSingleList(singleList *list)
// {
//   while ((*list).root != NULL)
//     deleteBegin(list);
// }

// // Toàn bộ danh sách

// int totalSingleList(singleList list)
// {
//   int i = 0;
//   list.cur = list.root;
//   while (list.cur != NULL)
//   {
//     i++;
//     list.cur = list.cur->next;
//   }
//   return i;
// }

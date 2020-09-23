#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct
{
  char username[20];
  char password[20];
  int status;
} nodeValType;

typedef struct Node
{
  nodeValType val;
  struct Node *next;
} Node;

typedef struct
{
  Node *root;
  Node *tail;
} linkedList;

int getLength(linkedList *list);
void printSingleList(linkedList *list);

// Implementing
void *createSingleList(linkedList *list);
Node *makeNewNode(nodeValType e);

// Get
Node *getNodeAt(linkedList *list, int index);

// Insert
Node *insertEnd(linkedList *list, nodeValType e);
Node *insertBegin(linkedList *list, nodeValType e);
Node *insertAt(linkedList *list, nodeValType e, int pos);

// Delete
Node *deleteBegin(linkedList *list);
Node *deleteEnd(linkedList *list);
Node *deleteAt(linkedList *list, int pos);

#endif

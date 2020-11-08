#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 1024
typedef struct
{
  char user_name[BUFLEN];
  char password[BUFLEN];
  int status;
} elementtype;
typedef struct node node;
typedef struct node
{
  elementtype element;
  node *next;
} node;

typedef struct
{
  node *root;
  node *cur;
  node *prev;
  node *tail;
} singleList;
singleList list;
//Declare function of linked list
void createSingleList(singleList *list);
node *makeNewNode(elementtype e);
node *insertEnd(singleList *list, elementtype e);
node *deleteHead(singleList *list);
node *deleteAtPosition(singleList *list, int position);
void printSingleList(singleList list);

//Implement function of linked list
void createSingleList(singleList *list)
{
  (*list).root = (*list).prev = (*list).cur = (*list).tail = NULL;
}
node *makeNewNode(elementtype e)
{
  node *new = (node *)malloc(sizeof(node));
  new->element = e;
  new->next = NULL;
  return new;
}
node *insertEnd(singleList *list, elementtype e)
{
  node *new = makeNewNode(e);
  if ((*list).root == NULL)
  {
    (*list).root = (*list).tail = new;
  }
  else
  {
    (*list).tail->next = new;
    (*list).tail = new;
  }
  return (*list).tail;
}
node *deleteHead(singleList *list)
{
  if ((*list).root != NULL)
  {
    node *new = (*list).root;
    (*list).root = (*list).root->next;
    free(new);
  }
  return (*list).root;
}
node *deleteAtPosition(singleList *list, int position)
{
  if ((*list).root == NULL)
  {
    return (*list).root;
  }
  (*list).cur = (*list).prev = (*list).root;
  //Delete head node
  if (position == 0)
  {
    return deleteHead(list);
  }
  (*list).cur = (*list).prev = (*list).root;
  //store previous of to be deleted node
  for (int i = 0; (*list).cur != NULL && i < position - 1; i++)
  {
    (*list).prev = (*list).cur;
    (*list).cur = (*list).cur->next;
  }
  if ((*list).cur == NULL || (*list).cur->next == NULL) // If position is more than number of nodes
  {
    return (*list).cur;
  }
  if ((*list).cur->next->next == NULL)
  {
    (*list).prev = (*list).cur;
    (*list).cur = (*list).cur->next;
    node *new = (*list).cur;
    (*list).cur = (*list).cur->next;
    free(new);
    (*list).tail = (*list).prev;
    (*list).tail->next = NULL;
    return (*list).tail;
  }
  //delete node at pos (next of pos-1)
  (*list).prev = (*list).cur;
  node *next = (*list).cur->next->next;
  free((*list).cur->next);
  (*list).prev->next = next;
  return (*list).cur;
}
void printSingleList(singleList list)
{
  list.cur = list.root;
  while (list.cur != NULL)
  {
    printf("%s %s %d\n", list.cur->element.user_name, list.cur->element.password, list.cur->element.status);
    list.cur = list.cur->next;
  }
  return;
}

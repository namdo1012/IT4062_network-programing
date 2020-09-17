#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

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

Node *getValueAt(linkedList *list, int index)
{
  // If inputed index is negative, return the root node
  if (index <= 0)
    return list->root;

  Node *tmp = list->root;
  int i = 1;
  while (i != index)
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
  return list->tail;
};

/*
Thêm 1 Node
*/

// Node *insertAfter(singleList *list, elementtype e);
// Node *insertAtPosition(singleList *list, elementtype e, int n);

// /*
// Xóa Node
// */

// Node *deleteBegin(singleList *list);
// Node *deleteEnd(singleList *list);
// Node *deleteAtPosition(singleList *list, int n);
// Node *deleteSingleList(singleList *list);

// /*
// In ra màn hình tất cả list
// */

// /*
// Tất cả Node
// */
// int totalSingleList(singleList list);

// Thêm vào cuối danh sách

// Node *insertEnd(singleList *list, elementtype e)
// {
//   Node *new = makeNewNode(e);
//   if ((*list).root == NULL)
//   {
//     (*list).root = (*list).tail = new;
//   }
//   else
//   {
//     (*list).tail->next = new;
//     (*list).tail = new;
//   }
//   return (*list).tail;
// }

// // Thêm vào vị trí
// node *insertAtPosition(singleList *list, elementtype e, int n)
// {
//   node *new = makeNewNode(e);
//   if ((*list).root == NULL)
//   {
//     (*list).root = (*list).tail = (*list).cur = new;
//   }
//   else
//   {
//     if (n <= 1)
//     {
//       insertBegin(list, new->element);
//       return (*list).cur;
//     }
//     if (n > totalSingleList(*list))
//     {
//       insertEnd(list, new->element);
//       return (*list).cur;
//     }
//     else
//     {
//       (*list).cur = (*list).prev = (*list).root;
//       int i = 1;
//       while (((*list).cur->next != NULL) && (i <= n - 1))
//       {
//         i++;
//         (*list).prev = (*list).cur;
//         (*list).cur = (*list).cur->next;
//       }
//       new->next = (*list).cur;
//       (*list).prev->next = (*list).cur = new;
//     }
//   }
//   return (*list).cur;
// }

// // Xóa node đầu tiên

// node *deleteBegin(singleList *list)
// {
//   if ((*list).root != NULL)
//   {
//     node *new = (*list).root;
//     (*list).root = (*list).root->next;
//     free(new);
//   }
//   return (*list).root;
// }

// // Xóa node cuối cùng

// node *deleteEnd(singleList *list)
// {
//   if ((*list).root != NULL)
//   {
//     (*list).cur = (*list).prev = (*list).root;
//     while (((*list).cur->next != NULL))
//     {
//       (*list).prev = (*list).cur;
//       (*list).cur = (*list).cur->next;
//     }
//     node *new = (*list).cur;
//     (*list).cur = (*list).cur->next;
//     free(new);
//     (*list).tail = (*list).prev;
//     (*list).tail->next = NULL;
//     return (*list).tail;
//   }
// }

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

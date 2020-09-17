/*
Khai báo node
*/

// typedef struct node node;
typedef struct Node
{
  int val;
  struct Node *next;
} Node;

typedef struct
{
  Node *root;
  Node *tail;
} linkedList;

// Implementing
linkedList *createSingleList();
Node *makeNewNode(int e);
Node *insertBegin(linkedList *list, int e);
void printSingleList(linkedList *list);
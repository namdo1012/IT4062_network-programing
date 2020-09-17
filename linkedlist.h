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

int getLength(linkedList *list);
void printSingleList(linkedList *list);

// Implementing
linkedList *createSingleList();
Node *makeNewNode(int e);

// Get
Node *getNodeAt(linkedList *list, int index);

// Insert
Node *insertEnd(linkedList *list, int e);
Node *insertBegin(linkedList *list, int e);
Node *insertAt(linkedList *list, int e, int pos);

// Delete
Node *deleteBegin(linkedList *list);
Node *deleteEnd(linkedList *list);
Node *deleteAt(linkedList *list, int pos);

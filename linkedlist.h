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

void printSingleList(linkedList *list);

// Implementing
linkedList *createSingleList();
Node *makeNewNode(int e);

// Get
Node *getValueAt(linkedList *list, int index);

// Insert
Node *insertEnd(linkedList *list, int e);
Node *insertBegin(linkedList *list, int e);
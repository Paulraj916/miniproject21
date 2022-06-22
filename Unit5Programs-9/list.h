#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

struct node {
  int data;
  struct node *next;
};

typedef struct node Node;

typedef struct node List;

List *init_list();
Node *createnode(int data);
Node *add(int data, List *list);
void  ldisplay(List *list);
void  ldestroy(List *list);
Node *ldelete(int data, List *list);
Node *lreverse(List *list);

#endif

/*
struct list {
  Node *head;
};
*/
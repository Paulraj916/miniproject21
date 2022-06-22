// Add your includes below
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} Node;

Node *lhead = NULL;
Node *ltail;

void create();
void ndisplay();
void sort_list();      // sorting using qsort
void ssort_list();     // sorting using selection sort of values
void node_sort_list(); // sorting using selection sort of nodes
void sort_list_rec();  // sorting using recursive selection sort

int is_valid(Node *n) { return n != NULL; }

/* Traverses a list and returns a node 'steps' away
 * or returns NULL if 'steps' is not valid
 * Arguments: Starting node pointer and number of steps
 */
Node *traverse(Node *np, int steps) {
  while (is_valid(np) && steps > 0)
    np = np->next, steps--;

  return steps == 0 ? np : NULL;
}

/* Connects up two valid nodes
 * Arguments: Two nodes, the 2nd node follows the 1st node
 */
void connect(Node *current, Node *following) {
  if (is_valid(current))
    current->next = following;
}

/* Gets an integer value from stdin
 * Arguments: None
 */
int get_value() {
  int val;
  printf("\n Enter the data : ");
  scanf("%d", &val);
  printf("%d", val);
  return val;
}

/* Gets an integer value from stdin
 * and returns that value as index (value-1)
 * Arguments: None
 */
int get_position() {
  int pos;
  printf("\n Enter the position: ");
  scanf("%d", &pos);
  printf("%d", pos);
  pos = pos - 1;
  return pos;
}

Node *get_node() {
  int pos = get_position();
  return traverse(lhead, pos);
}

Node *init_node(int val) {
  Node *np = (Node *)malloc(sizeof(Node));
  np->data = val;
  np->next = NULL;
  return np;
}

void insert_after(Node *locatedNode, int val) {
  Node *next = locatedNode->next;
  Node *newN = init_node(val);
  connect(locatedNode, newN);
  connect(newN, next);
}

/* DO NOT MODIFY the function below
 *
 */
void insert() {
  Node *locatedNode = get_node();
  if (is_valid(locatedNode)) {
    int val = get_value();
    insert_after(locatedNode, val);
    return;
  }
  printf("\n No such position");
}

/* Gets an integer value from stdin
 * and return the location (index) of that
 * value in the linked list
 * Arguments: None
 */
void get_index() {
  int val;
  printf("\nEnter value to search for? ");
  scanf("%d", &val);
  int index = 0;
  int flag = 0;
  const Node *current = lhead;
  while (current) {
    if (current->data == val) {
      flag = 1;
      break;
    }
    index++;
    current = current->next;
  }
  if (!flag)
    printf("Data %d: Not in the list!", val);
  else {
    printf("Data %d: Found at index %d", val, index);
  }
}

//------- DO NOT EDIT BELOW ---------------
int main() {
  int choice, n;
  printf("\n Enter the initial no. of inputs:");
  scanf("%d", &n);
  int i;
  for (i = 1; i <= n; i++)
    create();
  printf("\n1. Insert"
         "\n3. Display"
         "\n4. Search"
         "\n5. Sort"
         "\n6. Exit"
         "\n7. Recursive sort");
  do {
    printf("\n Enter your choice: ");
    scanf("%d", &choice);
    printf("%d", choice);
    switch (choice) {
    case 1:
      insert();
      break;
    case 3:
      ndisplay();
      break;
    case 4:
      get_index();
      break;
    case 5:
      node_sort_list();
      // ssort_list();
      // sort_list();
      break;
    case 6:
      puts("\nExiting program...!");
      break;
    case 7:
      sort_list_rec();
    }
  } while (choice != 6);
  return 0;
}

void create() {
  int val = get_value();
  Node *new = init_node(val);
  if (lhead == NULL) {
    lhead = new;
    ltail = lhead;
  } else {
    connect(ltail, new);
    ltail = new;
  }
}

void ndisplay() {
  Node *iter = lhead;
  printf("\n  The list contains : [");
  for (; is_valid(iter); iter = iter->next) {
    printf("%d", iter->data);
    if (iter->next)
      printf(", ");
  }
  printf("]");
}

/* Selection sort of the nodes
 * in the linked list, recursively
 */
void sort_list_rec() { puts("Not yet implemented"); }

/* Selection sort of the nodes
 * in the linked list
 */
void node_sort_list() {
  Node *current = lhead;
  Node *prev = 0; // previous node to current
  // iterate through the list
  while (current && current->next) {
    Node *mnode = current;
    // find the minimum in the rest of the list
    Node *rest = current->next;
    Node *mprev = 0; // previous node to minimum
    Node *restp = current;
    while (rest) {
      if (rest->data < mnode->data) {
        mnode = rest;
        mprev = restp;
      }
      restp = rest;
      rest = rest->next;
    }
    // swap nodes only if necessary
    if (mnode != current) {
      Node *temp;
      // If nodes are adjacent to each other,
      // insert mnode before current
      // The desired sequence:
      //   prev >> mnode  >> current >>  mnode->next
      if (mprev == current) {
        // if(prev && mprev && mnode && current)
        //   printf("prev %d mprev %d mnode %d current %d\n",
        //     prev->data, mprev->data, mnode->data, current->data);
        temp = mnode->next;
        mnode->next = current;
        current->next = temp;
        if (!prev)
          // swapping at the lhead
          lhead = mnode;
        else
          prev->next = mnode;

      } else {
        // Swap the forward links
        temp = mnode->next;
        mnode->next = current->next;
        current->next = temp;
        // Swap the forward links of previous nodes
        if (prev) {
          temp = mprev->next;
          mprev->next = prev->next;
          prev->next = temp;
        } else {
          // swapping at the lhead
          mprev->next = lhead;
          lhead = mnode;
        }
      }
      // rejig current to mnode->next
      prev = mnode;
      current = mnode->next;
      // if(prev && mprev && mnode && current)
      //   printf("\nprev %d mprev %d mnode %d current %d\n",
      //     prev->data, mprev->data, mnode->data, current->data);
    } else {
      prev = current;
      current = current->next;
    }
    ndisplay();
  }
}

/* Selection sort of the linked list
 * based on the node values
 */
void ssort_list() {
  Node *current = lhead;
  // iterate through the list
  while (current && current->next) {
    Node *mnode = current;
    // find the minimum in the rest of the list
    Node *rest = current->next;
    while (rest) {
      if (rest->data < mnode->data)
        mnode = rest;
      rest = rest->next;
    }
    // swap only if necessary
    if (mnode != current) {
      int temp = mnode->data;
      mnode->data = current->data;
      current->data = temp;
    }
    current = current->next;
  }
}

int comparefunc(const void *a, const void *b) {
  const Node *na = *(Node **)a;
  const Node *nb = *(Node **)b;
  return na->data - nb->data;
}

/* Sorting of the linked list
 * using qsort
 */
void sort_list() {
  Node *current = lhead;
  Node *narr[100];
  int count = 0;
  while (current) {
    narr[count] = current;
    current = current->next;
    count++;
  }
  if (count > 0) {
    qsort(&narr, count, sizeof(Node *), comparefunc);
    lhead = narr[0];
    Node *current = lhead;
    Node *prev = 0;
    int i = 0;
    while (count--) {
      current->next = narr[i + 1];
      prev = current;
      current = current->next;
      i++;
    }
    prev->next = 0;
    ltail = prev;
  }
  printf("List sorted: ");
  ndisplay();
}
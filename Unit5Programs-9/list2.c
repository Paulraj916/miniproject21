// Add your includes below
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} Node;

Node *lhead = NULL;

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
  // remove the above line and write your code below
  Node *np = malloc(sizeof(Node));
  np->data = val;
  np->next = NULL;
  return np;
}

void insert_after(Node *locatedNode, int val) {
  // remove the above line and write your code below
  Node *next = locatedNode->next; 
  Node *newN = init_node(val); 
  //connect(locatedNode, newN);
  //connect(newN, next);
  locatedNode->next = newN;
  newN->next = next;
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
  // remove the above line and write your code below 
  int val = get_value(); 
  Node *current = lhead;
  int index = 0;
  int flag = 0; 
  while (current) { 
    if (current->data == val) {
      flag = 1;
      break;
    }
    index++;
    current = current->next; 
  }
  if (flag)
    printf("\nData %d: Found at index %d", val, index);
  else
    printf("\nData %d: Not found in list!", val);
}

//------- DO NOT EDIT BELOW ---------------
void create();
void ndisplay();
int main() {
  int choice, n;
  printf("\n Enter the initial no. of inputs:");
  scanf("%d", &n);
  int i;
  for (i = 1; i <= n; i++)
    create();
  printf("\n1.Insert"
         "\n3.Display"
         "\n4.Search"
         "\n6.Exit");
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
    case 6:
      break;
    }
  } while (choice != 6);
  return 0;
}

Node *ltail;
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
    if (iter->next) printf(", ");
  }
  printf("]");
}
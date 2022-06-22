#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *init_list() {
  return NULL;
}

Node *createnode(int data) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

Node *add(int data, List *list) {
  Node *newnode = createnode(data);
  // is this the first node?
  if (!list) 
    return newnode;
  
  // traverse to the tail
  while (list->next)
      list = list->next;

  list->next = newnode;
  return newnode;
}

void ldisplay(List *list) {
  Node *current = list; 
  printf("List contents [");
  while(current) {
    printf("%d", current->data);
    if (current->next)
      printf(", ");
    current = current->next;
  }
  puts("]");
}


Node *ldelete_node(Node *n, List *list) {
  Node *current = list; 
  Node *previous = 0;
  while (current) {
    // is there a match? 
    if (current == n) {
      if (previous)
        previous->next = current->next; 
      else  // match at the head node
        list = current->next; 

      free(current);
      return list;
    }  
    // else go check the nextnode 
    previous = current;
    current = current->next;
  }
  printf("%p: No match for node in list!\n", n);
  return list;
}


Node *ldelete(int data, List *list) {
  Node *current = list; 
  Node *previous = 0;
  while (current) {
    // is there a match? 
    if (current->data == data) {
      if(previous)
        previous->next = current->next; 
      else  // match at the head node
        list = current->next; 

      free(current);
      return list;
    }  
    // else go check the nextnode 
    previous = current;
    current = current->next;
  }
  printf("%d: No match for data in list!\n", data);
  return list;
}


void ldestroy(List *list) {
  Node *current = list;
  if(!current) 
    return;
  while (current->next) {
    Node *next = current->next;
    free(current);
    current = next;
  }
}

Node *lreverse(List *list) {
  Node *current = list;
  Node *prev = NULL;
  while (current) {
    Node *nextnode = current->next;
    current->next = prev;
    prev = current;
    current = nextnode;
  }
  return prev;
}


int main(void){
  List * list = 0;
  list = add(1, list);
  add(20, list);
  add(2, list);
  add(5, list);
  add(8, list);
  add(9, list);
  add(13, list);
  puts("Linked List built successfully!");
  ldisplay(list);

  printf("Deleting 2...");
  list = ldelete(2, list);
  ldisplay(list);
  
  printf("Deleting 1...");
  list = ldelete(1, list);
  ldisplay(list);

  printf("Deleting 20...");
  list = ldelete(20, list);
  ldisplay(list);

  printf("Deleting 120...");
  list = ldelete(120, list);
  ldisplay(list);

  printf("Deleting 13...");
  list = ldelete(13, list);
  ldisplay(list);

  list = lreverse(list);
  printf("reversed: \n");
  ldisplay(list);

  Node *nd = add(1000, list); 
  ldisplay(list);

  ldelete_node(nd, list); 
  ldisplay(list);

  list = lreverse(list);
  printf("reversed again: \n");
  ldisplay(list);


  ldestroy(list);
  puts("Entire list destroyed successfully!");
  return 0;
}
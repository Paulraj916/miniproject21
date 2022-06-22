/* Program to demonstrate the use of 
 * function pointers 
 */ 

#include <stdio.h> 

int add_2 (int n) { 
  return n + 2; 
} 

int main () { 
  int (*func_ptr)(int);

  func_ptr = add_2; 
  printf("%d\n", func_ptr(4));
}


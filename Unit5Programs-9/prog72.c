/* This program is also a illustrative program
 * to demonstrate the use of function pointers

 * This program converts its input to upper case
 * (if argv[0] begins with U or u) or lower case.
 * (if argv[0] begins with T or t) it toggles the case.
 * If argc is 0, it prints an error and quits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int togglecase(int c) {
  return isalpha(c) ? c ^ 32 : c;
}

int main(int argc, char **argv) {
  int (*convcase[3])(int) = {toupper, tolower, togglecase};
  int func;
  int result = EXIT_SUCCESS;

  int ch;
  if (argc > 0) {
    if (toupper((unsigned char)argv[0][0]) == 'U') {
             func = 0;
    } else if (toupper((unsigned char)argv[0][0] == 't')) {
      func = 2;
    } else {
      func = 1;
    }
    while ((ch = getchar()) != EOF) {
      //ch = (*convcase[func])((unsigned char)ch);
      ch = convcase[func](ch);
      putchar(ch);
    }
  } else {
    fprintf(stderr, "Unknown name. Can't decide what to do.\n");
    result = EXIT_FAILURE;
  }

  return result;
}
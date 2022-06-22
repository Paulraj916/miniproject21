/*
 * program sorts command line arguments in ascending order
 *   - if only 1 argument provided, the characters are sorted
 *   - sorting is accomplished using qsort and
 *   - and two comparators
 *
 *   Usage: ./a.out zyxghiabcd -> abcdghixyz
 *          ./a.out zero black argon -> argon black zero
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_strings(const void *a, const void *b) {
  const char *pa = *(const char **)a;
  const char *pb = *(const char **)b;
  // printf("%s %s\n", pa, pb);
  return strcmp(pa, pb);
}

int compare_chars(const void *a, const void *b) {
  // printf("%c %c\n", *(char *)a, *(char *)b);
  return (*(char *)a - *(char *)b);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    puts("No args to sort!\n");
    exit(0);
  }

  enum { char_compare, str_compare };
    // int (*convcase[2])(int) = {toupper, tolower};
  int (*comparators[2])(const void*, const void*) = { compare_chars,
        compare_strings };
  int func = char_compare;
  void *base = argv[1];
  int num_elements = strlen(argv[1]);
  int element_size = sizeof(char);

  if (argc > 2) {
    func = str_compare;
    base = &argv[1];
    num_elements = argc - 1;
    element_size = sizeof(char *);
  }
  qsort(base, num_elements, element_size, comparators[func]);

  if (argc == 2) {
    puts("After sorting letters in argument 1...");
    printf("%s\n", argv[1]);
  }

  if (argc > 2) {
    puts("After sorting command line arguments..");
    for (int i = 1; i < argc; i++)
      printf("%s\n", argv[i]);
  }

  return 0;
}
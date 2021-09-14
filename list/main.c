#include <stdlib.h>
#include <stdio.h>

#include "list.h"
int main(void) {
  int rvalue = EXIT_SUCCESS;
  
  list *list0 = list_empty();
  if (list0 == NULL) {
    return EXIT_FAILURE;
  }
  size_t n0 = 1;
  size_t n1 = 2;
  size_t n2 = 3;
  printf("Adding 1, 2, 3 to the main list\n");
  if (list_insert_tail(list0, &n0) != 0
      || list_insert_tail(list0, &n1) != 0
      || list_insert_tail(list0, &n2) != 0) {
    goto error;
  }
  printf("Main list length is: %zu\n\n", list_length(list0));
  
  list *list1 = list_empty();
  if (list1 == NULL) {
    goto error;
  }
  char a0 = 'a';
  char a1 = 'b';
  printf("Adding 'a', 'b' to the second list\n");
  if (list_insert_tail(list1, &a0) != 0
      || list_insert_tail(list1, &a1) != 0) {
    goto error;
  }
  printf("Second list length is: %zu\n\n", list_length(list1));
  
  printf("Moving everything from main list to second list\n");
  list_move_all_tail(list0, list1);
  printf("Main list length is: %zu\n", list_length(list0));
  printf("Second list length is: %zu\n\n", list_length(list1));
  goto dispose;
error:
  rvalue = EXIT_FAILURE;
  goto dispose;
dispose:
  if (list0 != NULL) {
    list_dispose(&list0);
  }
  if (list1 != NULL) {
    list_dispose(&list1);
  }
  
  return rvalue;
}

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

int main(void) {
  printf("Initalization of the vector...\n");
  vector* v = init_vector();
  if (v == NULL) {
      printf("error null pointer");
      return EXIT_FAILURE;
  }  
  
  print_vector(v);
  
  printf("pushing lot of pointers\n");
  int i = 5;
  push(v, &i);
  push(v, &i);
  push(v, &i);
  push(v, &i);
  push(v, &i);

  print_vector(v);
  int *ptr = (int *) pop(v);
  printf("last value was %d\n\n\n", *ptr);
  
  print_vector(v);

  printf("errasing occurence of the same pointer\n");
  erase(v, &i);

  print_vector(v);

  free_vector(v);
  return EXIT_SUCCESS;
}  

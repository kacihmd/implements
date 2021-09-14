#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "vector.h"

#define SIZE(v) v->size
#define CAP(v) v->capacity
#define ARR(v) v->array

#define DEFAULT_CAP 4
#define TRIGGER_RESIZE 1 / 4
#define COEFF_MORE 2
#define COEFF_LESS 4

// After adding an element to a vector *v, if SIZE(v) == CAP(v) then the array
// contening datas (ARR(v)) is full. __resize__ is called to resize ARR(v)
// with a new capacity of CAP(v) * COEFF_MORE.
// By default it doubles the capacity.

// After removing an element to a vector *v, calls __resize__ if
// SIZE(v) == CAP(v) / TRIGGER_RESIZE to avoid space wasting.
// Resizing ARR(v) with CAP(v) / COEFF_LESS as new capacity.
// By default if only 1/4 of the capacity is used the vetor is
// resized to half his capacity.

struct vector {
  size_t size;
  size_t capacity;
  void **array;
};

// Given a vector *v, resizes ARR(v) to a capacity new_cap
// Returns 0 on success, -1 otherwise.
int __resize__(vector *v, size_t new_cap) {
  if (v == NULL) {
    return -1;
  }
  void *p = realloc(ARR(v), new_cap * sizeof(void *));
  if (p == NULL) {
    return -1;
  }
  ARR(v) = p;
  CAP(v) = new_cap;
  return 0;
}

vector *init_vector() {
  vector *v = (vector *) malloc(sizeof(*v));
  if (v == NULL) {
    return NULL;
  }
  SIZE(v) = 0;
  CAP(v) = DEFAULT_CAP;
  ARR(v) = malloc(sizeof(void *) * DEFAULT_CAP);
  if (ARR(v) == NULL) {
    free(v);
    return NULL;
  }
  return v;
}

void free_vector(vector *v) {
  if (v != NULL) {
    free(ARR(v));
    free(v);
  }
}

size_t size(vector *v) {
  return v == NULL ? 0 : SIZE(v);
}

void print_vector(vector *v) {
  if (v != NULL) {
    printf("size: %zu\n", SIZE(v));
    printf("capacity: %zu\n", CAP(v));
  }
  printf("\n\n");
}

void *at(vector *v, size_t index) {
  if (v != NULL && index < SIZE(v)) {
    if (SIZE(v) == 0) {
      return NULL;
    }
    return ARR(v)[index];
  }
  return NULL;
}

int insert(vector *v, size_t index, void *p) {
  if (v == NULL || index > SIZE(v)) {
    return -1;
  }
  if (SIZE(v) == CAP(v)) {
    if (__resize__(v, CAP(v) * COEFF_MORE) != 0) {
      return -1;
    }
  }
  void *ptr = memmove(&(ARR(v)[index + 1]), &(ARR(v)[index]),
          (SIZE(v) - index) * sizeof(void *));
  if (ptr != &(ARR(v)[index + 1])) {
    return -1;
  }
  ARR(v)[index] = p;
  ++SIZE(v);
  return 0;
}

int push(vector *v, void *p) {
  if (v != NULL) {
    return insert(v, SIZE(v), p);
  }
  return -1;
}

int prepend(vector *v, void *p) {
  if (v != NULL) {
    return insert(v, 0, p);
  }
  return -1;
}

int delete(vector *v, size_t index) {
  if (v == NULL || index >= SIZE(v)) {
    return -1;
  }
  void *p = memmove(&(ARR(v)[index]), &(ARR(v)[index + 1]),
          (SIZE(v) - index + 1) * sizeof(void *));
  if (p != &(ARR(v)[index])) {
    printf("error mmove \n");
    return -1;
  }
  --SIZE(v);
  // If too much capacity is unused, resize ARR(v) smaller
  if (SIZE(v) == (CAP(v) / TRIGGER_RESIZE)) {
    if (__resize__(v, CAP(v) / COEFF_LESS) != 0) {
      printf("error resize less\n");
      return -1;
    }
  }
  return 0;
}

void *pop(vector *v) {
  void *p = NULL;
  if (v != NULL) {
    p = at(v, SIZE(v) - 1);
    if (delete(v, SIZE(v) - 1) != 0) {
      p = NULL;
    }
  }
  return p;
}

int erase(vector *v, void *p) {
  if (v != NULL) {
    for (size_t i = 0; i < SIZE(v); ++i) {
      if (at(v, i) == p) {
        delete(v, i);
        --i;
      }
    }
    return 0;
  }
  return -1;
}

size_t find(vector *v, void *p) {
  if (v != NULL) {
    for (size_t i = 0; i < SIZE(v); ++i) {
      if (at(v, i) == p) {
        return i;
      }
    }
  }
  return size(v) + 1;
}

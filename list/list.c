#include <stdlib.h>
#include "list.h"

#define FUN_SUCCESS 0
#define FUN_FAILURE -1

typedef struct clist clist;

struct clist {
  void *value;
  clist *next;
};

struct list {
  clist *head;
  clist *tail;
  size_t count;
};

list *list_empty(void) {
  list *p = malloc(sizeof(*p));
  if (p == NULL) {
    return NULL;
  }
  p->head = NULL;
  p->tail = NULL;
  return p;
}

bool list_is_empty(const list *p) {
  return p->head == NULL;
}

size_t list_length(const list *p) {
  size_t n = 0;
  if (p != NULL) {
    clist *ptr = p->head;
    while (ptr != NULL) {
      ++n;
      ptr = ptr->next;
    }
  }
  return n;
}

int list_head_value(const list *p, void **ptr) {
  if (!list_is_empty(p)) {
    *ptr = p->head->value;
    return FUN_SUCCESS;
  }
  return FUN_FAILURE;
}

int list_tail_value(const list *p, void **ptr) {
  if (!list_is_empty(p)) {
    *ptr = p->tail->value;
    return FUN_SUCCESS;
  }
  return FUN_FAILURE;
}

int list_insert_head(list *p, void *ptr) {
  clist *cell = malloc(sizeof(*cell));
  if (cell == NULL) {
    return FUN_FAILURE;
  }
  if (list_is_empty(p)) {
    p->tail = cell;
    cell->next = NULL;
  } else {
    cell->next = p->head;
  }
  p->head = cell;
  cell->value = ptr;
  return FUN_SUCCESS;
}

int list_insert_tail(list *p, void *ptr) {
  clist *cell = malloc(sizeof(*cell));
  if (cell == NULL) {
    return FUN_FAILURE;
  }
  if (list_is_empty(p)) {
    p->head = cell;
    p->tail = cell;
  } else {
    p->tail->next = cell;
    p->tail = cell;
  }
  cell->value = ptr;
  return FUN_SUCCESS;
}

int list_move_head_head(list *src, list *dest) {
  if (list_is_empty(src)) {
    return FUN_FAILURE;
  }
  if (list_is_empty(dest)) {
    dest->head = src->head;
    dest->tail = src->head;
    src->head = src->head->next;
  } else {
    clist *ptr = src->head;
    src->head = src->head->next;
    ptr->next = dest->head;
    dest->head = ptr;
  }
  if (list_is_empty(src)) {
    src->tail = NULL;
  }
  return FUN_SUCCESS;
}

int list_move_head_tail(list *src, list *dest) {
  if (list_is_empty(src)) {
    return FUN_FAILURE;
  }
  if (list_is_empty(dest)) {
    dest->head = src->head;
    dest->tail = src->head;
  } else {
    dest->tail->next = src->head;
    dest->tail = src->head;
  }
  src->head = src->head->next;
  dest->tail->next = NULL;
  if (list_is_empty(src)) {
    src->tail = NULL;
  }
  return FUN_SUCCESS;
}

int list_move_all_head(list *src, list *dest) {
  list *ptr = malloc(sizeof(*ptr));
  if (ptr == NULL) {
    return FUN_FAILURE;
  }
  while (!list_is_empty(src)) {
    if (list_move_head_head(src, ptr) == FUN_FAILURE) {
      return FUN_FAILURE;
    }
  }
  while (!list_is_empty(ptr)) {
    if (list_move_head_head(ptr, dest) == FUN_FAILURE) {
      return FUN_FAILURE;
    }
  }
  free(ptr);
  return FUN_SUCCESS;
}

int list_move_all_tail(list *src, list *dest) {
  while (!list_is_empty(src)) {
    if (list_move_head_tail(src, dest) == FUN_FAILURE) {
      return FUN_FAILURE;
    }
  }
  return FUN_SUCCESS;
}

int list_apply(list *p, int (*fun)(void *)) {
  clist *ptr = p->head;
  while (ptr != NULL) {
    if (fun(ptr->value) != 0) {
      return FUN_FAILURE;
    }
    ptr = ptr->next;
  }
  return FUN_SUCCESS;
}

void list_dispose(list **sptr) {
  if (*sptr != NULL) {
    clist *ptr = (*sptr)->head;
    free(*sptr);
    while (ptr != NULL) {
      clist *xptr = ptr->next;
      free(ptr);
      ptr = xptr;
    }
    *sptr = NULL;
  }
}

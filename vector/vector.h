#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

// Implementation of a vector on pointers
// Mutable array with automatic resizing
typedef struct vector vector;

// Returns a valid pointer on an initialized new vector 
// By default size=0, capacity=DEFAULT_CAP, is_empty(init_vector()) => true
// Must be freed by free_vector at the end of the program
extern vector *init_vector();

// Frees the given vector v
extern void free_vector(vector *v);

// Prints stats of the given v vector : size, capacity, and values
// Does nothing if v == NULL
extern void print_vector(vector *v);

// Returns the size of the given v vector
// Undetermined behavior if v == NULL;
extern size_t size(vector *v);

// Returns the value at the given index of v
// Assert that index < size(v)
// Returns -1 if size(v) == 0, if v == NULL or if index is out of bounds
extern void *at(vector *v, size_t index);

// Insert a value e at a given index of v
// Returns 0 on success, -1 otherwise
extern int insert(vector *v, size_t index, void *p);

// Pushs e at the end of the vector v
// Returns 0 on success, -1 otherwise
extern int push(vector *v, void *p);

// Inserts value e at the beginning of the vector v
// Equivalent to insert(v, 0, e);
// Returns 0 on success, -1 otherwise
extern int prepend(vector *v, void *p);

// Deletes the index th element from vector v
// Returns 0 on success, -1 otherwise
extern int delete(vector *v, size_t index);

// Removes the last value of v and returns it
// Returns -1 if v == NULL or if operation failed;
extern void *pop(vector *v);

// Find all the occurences of e in v and deletes them
// Returns 0 on success, -1 otherwise
extern int erase(vector *v, void *p);

// Returns the index of the first occurence of e in the vector v
// Returns a value x > size(v) if e not found 
// Undetermined behavior if v == NULL
extern size_t find(vector *v, void *p);

#endif

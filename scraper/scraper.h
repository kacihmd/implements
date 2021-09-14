#ifndef SCRAPER_H
#define SCRAPER_H

#include <stdlib.h>

typedef struct scraper scraper;

// Returns a pointer on an initialized scraper structure on the file f
// path must be a valid path to a file 
scraper *scraper_init(const char *path);

// Frees scraper structures
// Must be called on a scraper_init returned pointer
// Undefined behavior in case of a non valid pointer
void scraper_dispose(scraper **scrap);

// Returns a pointer on the string value associated to the given key
// Returns NULL if no such key of if an error occured
const char *scraper_get(scraper *p, char *key);

#endif
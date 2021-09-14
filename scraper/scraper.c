#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "scraper.h"
#include "hashtable.h"
#include "holdall.h"

#define DELIM ":="

struct scraper {
    FILE *file;
    hashtable* ht;
    holdall* ha;
    char *last_get_value;
};

scraper *scraper_init(const char *path) {
    scraper *end_return_value = NULL;

    if (path == NULL) {
        goto end_fun;
    }

    // Initializing the scraper and correctly handling allocation errors
    scraper *p = malloc(sizeof(*p));
    if (p == NULL) {
        perror("malloc scraper");
        goto end_fun;
    }
    p->file = NULL;
    p->ht = NULL;
    p->ha = NULL;
    p->last_get_value = NULL;

    p->file = fopen(path, "r");
    if (p == NULL) {
        perror("fopen scraper file");
        goto error_dispose;
    }
    p->ht = hashtable_empty((int (*)(const void *, const void *))strcmp,
                            (size_t (*)(const void *))str_hashfun);
    if (p->ht == NULL) {
        fprintf(stderr, "error initializing scraper hashtable\n");
        goto error_dispose;
    }
    p->ha = holdall_empty();
    if (p->ha == NULL) {
        fprintf(stderr, "error initializing scraper holdall\n");
        goto error_dispose;
    }
    end_return_value = p;

    if (fseek(p->file, 0, SEEK_SET) == -1) {
        perror("fseek before reading file");
        goto error_dispose;
    }

    while (!feof(p->file) && !ferror(p->file)) {

        char *line = NULL;
        size_t len = 0;
        long seek = 0;
        ssize_t rvalue = getline(&line, &len, p->file);

        while (rvalue > 0) {
            char *key = NULL;
            long *seek_pos = NULL;

            size_t len  = strlen(line);
            char *keybuf = strtok(line, DELIM);
            // If line do not contain any delimitors, strtok returns the whole line
            // wich size should be equal to len. It is not a key : value line
            // We skip this line.
            if (strlen(keybuf) == len) {
                goto iteration_step;
            }

            key = malloc(strlen(keybuf) + 1);
            if (key == NULL) {
                perror("malloc key");
                goto local_error;
            }
            strcpy(key, keybuf);

            // Adding the seek position of the first character of 
            // the line we've juste read in ht. 
            seek_pos = malloc(sizeof(*seek_pos));
            if (seek_pos == NULL) {
                perror("malloc seek_pos");
                goto local_error;
            }
            *seek_pos = seek;

            // Adding key and seek_pos into ha to free them in scraper_dispose
            if (holdall_put(p->ha, key) != 0 
                || holdall_put(p->ha, seek_pos) != 0) {
                fprintf(stderr, "error adding pointer into scraper holdall\n");
                goto local_error;
            }

            if (hashtable_add(p->ht, key, seek_pos) == NULL) {
                fprintf(stderr, "error adding pointer into scraper hashtable\n");
                goto local_error;
            }

            goto iteration_step;
            local_error:
                free(key);
                free(seek_pos);
                goto error_dispose;
            iteration_step:
            seek = ftell(p->file);
            rvalue = getline(&line, &len, p->file);
        }
        free(line);
    }
    end_return_value = p;

    goto end_fun;
    error_dispose:
        scraper_dispose(&p);
    end_fun:
        return end_return_value;
}

static int _intfree(void *ptr) {
    free(ptr);
    return 0;
}

void scraper_dispose(scraper **scrapptr) {
    if (scrapptr == NULL) {
        return;
    }
    scraper *p = *scrapptr;
    holdall_apply(p->ha, _intfree);
    holdall_dispose(&(p->ha));
    hashtable_dispose(&(p->ht));
    fclose(p->file);
    free(p->last_get_value);
    free(p);
    *scrapptr = NULL;
}

const char *scraper_get(scraper *p, char *key) {
    if (p == NULL || key == NULL) {
        return NULL;
    }

    const long *seek_pos = hashtable_search(p->ht, key);
    if (seek_pos == NULL) {
        printf("not found\n");
        return NULL;
    }
    fseek(p->file, *seek_pos, SEEK_SET);
    char *lineptr = NULL;
    size_t n = 0;
    if (getline(&lineptr, &n, p->file) <= 0) {
        return NULL;
    }

    char *c = lineptr;
    while(strchr(DELIM, *c) == NULL && *c != '\0') {
        ++c;
    }
    if (*c == '\0') {
        free(lineptr);
        return NULL;
    }
    ++c;

    p->last_get_value = realloc(p->last_get_value, strlen(c) + 1);
    if (p->last_get_value == NULL) {
        perror("realloc last_get_value");
        return NULL;
    }
    strcpy(p->last_get_value, c);

    free(lineptr);
    return p->last_get_value;
}

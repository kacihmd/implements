#include <stdlib.h>
#include <stdio.h>
#include "scraper.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please give me the name of one valid file to scrap scrap\n");
        return EXIT_FAILURE;
    }

    scraper *scrap = scraper_init(argv[1]);

    char *key = argv[2];

    const char *value = scraper_get(scrap, key);
    if (value != NULL) {
        printf("%s", value);
    } else {
        printf("%s not present\n", key);
    }

    scraper_dispose(&scrap);
    return EXIT_SUCCESS;
}

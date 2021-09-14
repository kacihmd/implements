CC = gcc
hashtabledir = ../hashtable/
holdalldir = ../holdall/
CFLAGS = -std=c18 -O2 -g -I$(hashtabledir) -I$(holdalldir) -DHASHTABLE_CHECKUP
WFLAGS = -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings 
objects = main.o scraper.o $(hashtabledir)hashtable.o $(holdalldir)holdall.o
executable = scraper

all: $(executable)

scraper: $(objects)
	$(CC) $(objects) $(CFLAGS) $(WFLAGS) -o $(executable)

clean: 
	$(RM) $(objects) $(executable)

tar:
	$(MAKE) all clean
	tar -zcvf "$(CURDIR).tar.gz" *

main.o: main.c scraper.h 
scraper.o: scraper.c scraper.h $(hashtabledir)hashtable.h \
							   $(holdalldir)holdall.h

CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -o2 -g
LDFLAGS =
objects = vector.o main.o
executable = main

all: $(executable)

clean: 
	$(RM) $(objects) $(executable)

tar:
	$(MAKE) all clean
	tar -zcf "$(CURDIR).tar.gz" *

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

vector.o: vector.c vector.h
main.o: main.c vector.h

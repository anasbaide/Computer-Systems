#Ana Baide UID: 118441368
CC = gcc

CFLAGS = -ansi -Wall -g -O0 -Werror -Wshadow -Wwrite-strings \
-pedantic-errors -fstack-protector-all

all: d8sh

d8sh: d8sh.o executor.o lexer.o parser.tab.o 
	$(CC) -lreadline -o d8sh d8sh.o executor.o lexer.o parser.tab.o

d8sh.o: d8sh.c executor.h lexer.h
	$(CC) $(CFLAGS) -c d8sh.c

executor.o: executor.c executor.h command.h
	$(CC) $(CFLAGS) -c executor.c

lexer.o: lexer.c
	$(CC) $(CFLAGS) -c lexer.c

clean:
	rm -f d8sh ./*.o
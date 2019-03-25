CC = gcc
RM = rm -f

CFLAGS = -Wall -Werror -ggdb

strsplit: strsplit.c
	@$(CC) strsplit.c $(CFLAGS) -o strsplit

clean:
	@$(RM) strsplit *~

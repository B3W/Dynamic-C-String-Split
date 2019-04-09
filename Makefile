CC = gcc
RM = rm -f
BIN = strsplt

CFLAGS = -Wall -Werror -ggdb

strsplt: strsplt.c
	@$(CC) strsplt.c $(CFLAGS) -o $(BIN)

clean:
	@$(RM) $(BIN)

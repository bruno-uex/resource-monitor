CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude
LDFLAGS=
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
BIN=resource-monitor

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(BIN)

docs:
	@echo "Documentação em docs/"

test:
	@echo "Testes em tests/"

.PHONY: all clean docs test

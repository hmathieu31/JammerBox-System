BIN=../bin/main.exe

CC=gcc

CFLAGS=-Wall -g -I../header/

OBJ=bin/y.tab.o bin/lex.yy.o bin/symbolTable.o bin/instr.o #main.o

all: $(BIN)

bin/%.o: ../source/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $@

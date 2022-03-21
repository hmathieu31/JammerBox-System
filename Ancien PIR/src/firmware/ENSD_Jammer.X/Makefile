GRM=src/comp.y
LEX=src/comp.l
TABL=src/symbolTable.c
BIN=comp.exe
TEST=testSymbol.exe

CC=gcc

CFLAGS=-Wall -g -Isrc/ -Iexternal/

OBJ=bin/y.tab.o bin/lex.yy.o bin/symbolTable.o bin/instr.o #main.o

all: $(BIN)

test_sym: $(TEST)

bin/%.o: bin/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) bin/y.tab.o bin/lex.yy.o bin/symbolTable.o bin/instr.o -o bin/$@

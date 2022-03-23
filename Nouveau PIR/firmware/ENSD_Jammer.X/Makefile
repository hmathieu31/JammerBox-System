BIN=../bin/main.exe

CC=gcc

CFLAGS=-Wall -g -I../header/

OBJ=../bin/config.o ../bin/failures.o ../bin/.o ../bin/osc.o ../bin/port_config.o ../bin/synchronization.o ../bin/system_configuration.o ../bin/timer.o ../bin/uart.o #main.o

all: $(BIN)

bin/%.o: ../source/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $@

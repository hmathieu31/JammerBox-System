BIN=main

IDIR =../header
CC=gcc
CFLAGS=-Wall -g -I$(IDIR)

ODIR=.
LDIR =../source

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = failures.o ic.o main.o osc.o port_config.o synchronization.o system_configuration.o timer.o uart.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

all: $(BIN)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

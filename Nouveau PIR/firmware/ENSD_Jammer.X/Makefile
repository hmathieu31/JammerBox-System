#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES = -I../header

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L/usr/local/lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt

# define the C source files
SRC_DIR=../source
_SRCS = failures.c ic.c osc.c synchronization.c system_configuration.c timer.c uart.c
SRCS = $(patsubst %,$(SRC_DIR)/%,$(_SRCS))

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJ_DIR=../bin
_OBJS = $(SRCS:.c=.o)
OBJS = $(subst $(SRC_DIR), $(OBJ_DIR), $(_OBJS))

# define C source test files
TEST_DIR=../test
_TESTS = test_GPIO.c
TESTS = $(patsubst %,$(TEST_DIR)/%,$(_TESTS))

# define object files associated with test source (stored in bin aswell)
_OBJS_TEST = $(TESTS:.c=.o)
OBJS_TEST = $(subst $(TEST_DIR), $(OBJ_DIR), $(_OBJS_TEST))


# define the executable file 
MAIN = ../bin/main.exe
TEST_GPIO = ../bin/test_GPIO

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)
	@echo Simple compiler named mycc has been compiled

test_GPIO: $(TEST_GPIO)
	@echo $@ was compiled
	
$(TEST_GPIO): $(OBJS_TEST)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST_GPIO) $(OBJS_TEST) $(LFLAGS) $(LIBS)


$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

$(OBJS_TEST): $(TESTS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.c.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) ../bin/*

build:
	- make all
	$(RM) *.o *~ $(OBJS)

depend: $(SRCS)
	install-depend.sh
	
#makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
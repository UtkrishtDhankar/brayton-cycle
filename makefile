# Modified from https://github.com/FanaticalFighter/nako/blob/master/makefile

CC=gcc
CFLAGS=-c -Wall -std=gnu99
LFLAGS=-Wall -std=gnu99

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

# Source files in the project. Append new files here.
SRCS=src/boiler.c src/compressor.c src/main.c src/turbine.c

# Create object files list from source files list.
OBJS= $(SRCS:.c=.o)

all: brayton-cycle
all: clean-objects

# clean completely wipes directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) brayton-cycle

# only removes objects, not final executable
clean-objects:
	$(RM) $(RMFLAGS) src/*.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: brayton-cycle

brayton-cycle: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o brayton-cycle

# the following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $<  -o $@

## ------- Build file for the Text-Based Conway's Life -------
#
#  Author:  R. Paul Wiegand
#  Date:    July 15, 2020
#
#  This is a very simple example of a makefile to help you
#  build a multi-source file.  Ideally, these files would
#  be organized in different directories, but we'll keep
#  things simple at first.
#
#  There are two programs that are built by this:
#    BoardTester    -- a unit tester for the board visualizer
#    SimulationMain -- the simulator for Conway's Life CA
#
#  These programs rely on several source files:
#    BoardVisualizer.h/cc -- displays the CA in ASCII on screen
#    TwoDCharArray.h/cc   -- helps manage a 2D matrix of chars
#    ConwayLife.h/cc      -- Applies the rules of the CA
#    BoardTester.cc       -- Unit tests the visualizer & 2D array
#    SimulationMain.cc    -- Executes the simulation
#
#  To build this, you should only have to type: 'make' at the
#  command line.  Then you can run with './SimulationMain'.
#
#  This Makefile sets up a chain of dependencies so your
#  program can be compiled in the correct order, and only
#  needs to re-compile pieces when they have changed.  Start
#  with the 'all' target as the top of the "tree"; read from there.
#

# Make this the binary you want to compile!
TARGET=SimulationMain

# Make env vars for the different directories we will use
OBJDIR=./obj
SRCDIR=./src
INCDIR=./inc
BINDIR=./bin

# Create file groups for each directory
SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)


### --- Environmental Variables --- ###
CC=g++
CFLAGS=-I$(INCDIR)  -g
LDFLAGS=-lncurses -ggdb
LINKER=g++

# Explanation:
#   The "-I." flag says 'look for include files in .'
#   The "-lncurses" flag says to link with the system ncurses library
#   The "-g" and "-ggdb" flags are needed for using the GDB debugger


### --- Build Targets --- ###


# For every target, build using the rule pattern:
#  target:	object file set
$(BINDIR)/$(TARGET):	$(OBJECTS)
	$(LINKER) -o $@  $(OBJECTS) $(LDFLAGS)

# For every object file in the object file set, build using the rule pattern:
#    object file:	subst .o file for .c file with the same name
$(OBJECTS):	$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CFLAGS)  -o $@  -c $<


# Use ".PHONY" so we don't confuse with a target named "all"
.PHONY: all
all:	$(BINDIR)/$(TARGET)


# Use ".PHONY" so we don't confuse with a target named "clean"
.PHONY:	clean
clean:
	rm -f $(OBJECTS)
	rm -f $(BINDIR)/$(TARGET)
	rm -rf docs/html
	rm -rf docs/latex

# Used to make documentation via Doxygen
.PHONY: docs
docs:
	doxygen doxygen.cfg

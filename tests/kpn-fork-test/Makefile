# uses mylib
mylib_inc = 	../../src/
mylib_a = 	../../src/mylib.a

# additional flags
# -Wall: warnings
# -g: debugging
ADD_CFLAGS := -Wall -g -I$(mylib_inc)

ADD_LDFLAGS := -lpthread $(mylib_a)

# define a list of pkg-config packages we want to use
pkg_packages := liblog4cxx

# get the necessary flags for compiling
PKG_CFLAGS := $(shell pkg-config --cflags $(pkg_packages))

# get the necessary flags for linking
PKG_LDFLAGS := $(shell pkg-config --libs $(pkg_packages))

# combine the flags (so that CFLAGS/LDFLAGS from the command line
# still work).
CFLAGS := $(PKG_CFLAGS) $(ADD_CFLAGS) $(CFLAGS)
LDFLAGS := $(PKG_LDFLAGS) $(ADD_LDFLAGS) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp

targets = kpn-fork-test

.PHONY: all

all: $(targets)

kpn-fork-test: main.o #Source2.o Adder.o Display.o Source1.o
	$(CXX) $^ -o $@ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm $(targets) *.o

# define a list of pkg-config packages we want to use
pkg_packages := 

# get the necessary flags for compiling
PKG_CFLAGS := $(shell pkg-config --cflags $(pkg_packages))

# get the necessary flags for linking
PKG_LDFLAGS := $(shell pkg-config --libs $(pkg_packages))

# additional flags
# -Wall: warnings
# -g: debugging
ADD_CFLAGS := -Wall -g

ADD_LDFLAGS := -lpthread

# combine the flags (so that CFLAGS/LDFLAGS from the command line
# still work).
CFLAGS := $(PKG_CFLAGS) $(ADD_CFLAGS) $(CFLAGS)
LDFLAGS := $(PKG_LDFLAGS) $(ADD_LDFLAGS) $(LDFLAGS)

mylib_name = 	mylib.a

mylib_srcs = 	SharedVariable.cpp \
		BlockingChannel.cpp
#		util.cpp \
#               Channel.cpp
#		BlockingQueue.h
#		Component.cpp \

mylib_objs = 	SharedVariable.o \
		BlockingChannel.o
#		util.o \
#		Channel.o 
#		Component.o \


.SUFFIXES:
.SUFFIXES: .o .cpp

targets = $(mylib_name)

.PHONY: all

all: $(targets)

$(mylib_name): $(mylib_objs)
	ar rvu $@ $^
	ranlib $@

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

#util.o: util.cpp
#	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(targets) *.o
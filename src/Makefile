SHELL = /bin/sh

CC = g++
CFLAGS = -g -Wall -std=c++11
#CFLAGS = -Wall -std=c++11

UNAME := $(shell which uname)
SYSTEM := $(shell $(UNAME) -s)
ARCH := $(shell $(UNAME) -m | sed 's/ /_/g')

#OBJDIR = ../obj/$(SYSTEM)_$(ARCH)_obj

SRCFILES := $(shell find . -maxdepth 1 -name "*.cc")
OBJFILES := $(patsubst %.cpp, %.o, $(SRCFILES))

all:
	$(MAKE) elim

clean:
	rm -rf ../elim ../elim.dSYM

tidy:
	rm -f *.cc~ *c~ *.h~ Makefile~

elim: 
	$(CC) -o ../elim $(CFLAGS) $(OBJFILES)

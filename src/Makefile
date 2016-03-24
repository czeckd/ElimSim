SHELL = /bin/sh

CC = g++
CFLAGS = -g -Wall -std=c++11
#CFLAGS = -Wall -std=c++11

LIBS =

UNAME := $(shell which uname)
SYSTEM := $(shell $(UNAME) -s)
ARCH := $(shell $(UNAME) -m | sed 's/ /_/g')

OBJDIR = ../obj/$(SYSTEM)_$(ARCH)_obj

APP := elim
SRCFILES := $(shell find *.cc -type f -print)
OBJFILES := $(patsubst %.cc, $(OBJDIR)/%.o, $(SRCFILES))

all:
	$(MAKE) $(APP)

clean:
	rm -rf ../$(APP) ../$(APP).dSYM $(OBJFILES)

tidy:
	rm -f *.cc~ *c~ *.h~ Makefile~

mkobjdir    :
	@if [ ! -x $(OBJDIR) ] ; then mkdir -p $(OBJDIR) ; fi

$(OBJDIR)/%.o : %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(APP): mkobjdir $(OBJFILES) 
	$(CC) $(CFLAGS) -o ../$(APP) $(OBJFILES) $(LIBS)

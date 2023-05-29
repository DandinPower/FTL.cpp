CC=gcc
CFLAGS=-I../include -Wall -Wextra
LIBS=-lcheck -lm -pthread -lrt

# VPATH is used for gcc to search for the .h and .c files in these directories.
VPATH=../src:../include
OBJDIR=../build/test

SRC := $(notdir $(wildcard ../src/*.c))
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

UT_SRCS := $(notdir $(wildcard *.c))
UT_OBJS := $(UT_SRCS:%.c=$(OBJDIR)/%.o)

# $@ represents the target, $< represents the first prerequisite, and $^ represents all prerequisites.
all: $(OBJDIR)/ut_test

$(OBJDIR)/ut_test: $(UT_OBJS) $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	$(OBJDIR)/ut_test

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o
# Define the compiler
CC = g++

# Define the compiler flags
CFLAGS = -Iinclude -Wall

# Define the source files and objects
SRCS = src/ftl/address_translation.cc src/ftl/flash_translation.cc src/ftl/garbage_collection.cc src/ftl/nand_controller.cc main.cc
OBJS = $(addprefix build/, $(notdir $(SRCS:.cc=.o)))

# Define the executable
TARGET = build/ftl

# Rule for building the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for building the objects
build/%.o: src/ftl/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: main.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for cleaning the build directory
.PHONY: clean
clean:
	rm -rf build/*

# Rule for creating the build directory
.PHONY: prep
prep:
	mkdir -p build

CC := gcc 
CFLAGS := -Wall -Wextra -Iinclude
SRCDIR := src
INCDIR := include
BUILDDIR := build

# List all the source files
SOURCES := $(wildcard $(SRCDIR)/*.c)
# Generate a list of object files by replacing .c with .o
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Main target
$(BUILDDIR)/ftl_simulator: $(OBJECTS) $(BUILDDIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@ 

# Compile the source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the main file
$(BUILDDIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files and the executable
clean:
	rm -f $(BUILDDIR)/*.o 

# Define phony targets
.PHONY: clean
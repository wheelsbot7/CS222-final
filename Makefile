################################################################################
# Makefile for the project
# TODO: Makefile should generate two executables in the build folder: 
#       proj3 and test_proj3. 
#       Ensure to split the object files for the two executables.
#       Use variables to make the Makefile more readable.
################################################################################

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I.

# Directories
MAIN = src
TEST = tests

# Source files for each folder
SRC_MAIN = $(wildcard $(MAIN)/*.c)
SRC_TEST = $(wildcard $(TEST)/*.c)

# Object files for each folder
OBJ_MAIN = $(patsubst $(MAIN)/%.c, build/%.o, $(SRC_MAIN))
OBJ_TEST = $(patsubst $(TEST)/%.c, build/%.o, $(SRC_TEST))

# Executables
EXEC_MAIN = build/final_proj
EXEC_TEST = build/test_final_proj

# Default target
all: $(EXEC_MAIN) $(EXEC_TEST)

# Target for folder1
$(EXEC_MAIN): $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $@ $^

# Target for folder2
$(EXEC_TEST): $(OBJ_TEST) build/card.o 
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c files in folder1
build/%.o: $(MAIN)/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile .c files in folder2
build/%.o: $(TEST)/%.c src/card.c 
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
build:
	mkdir -p build

# Clean build artifacts
clean:
	rm -f $(EXEC_MAIN) $(EXEC_TEST) $(OBJ_MAIN) $(OBJ_TEST)

run:
	./$(EXEC_MAIN)

# Phony targets
.PHONY: all clean


# Variables
CC = gcc 
CFLAGS = -std=c99 -Wall -Wextra -g
OBJ = shell.o 
TARGET = shell
TEST_SCRIPT = ./test.sh

# Default rule (runs when you just type 'make') Build the executable
all: $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) 

# Compile shell.c to shell.o
shell.o: shell.c 
	$(CC) $(CFLAGS) -c shell.c 

# Run test script
test: $(TARGET)
	@chmod +x $(TEST_SCRIPT)
	@echo "Running automated tests..."
	@$(TEST_SCRIPT)


# Run Valgrind to find memory leaks
memcheck: $(TARGET)
	valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         ./$(TARGET)


# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Mark these as non-file targets
.PHONY: all clean test memcheck
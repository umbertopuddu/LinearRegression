# Source files
C = main.c LR_Model.c matrix.c vector.c

# Object files (linear.o and main.o)
OBJ = $(C:.c=.o)

# Output binary
TARGET = linear_test

# Compiler
CC = gcc -g

# Flags (optional: enable warnings and debug info)
CFLAGS = -Wall -Wextra -g

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c linear.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

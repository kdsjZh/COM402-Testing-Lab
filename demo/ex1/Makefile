# Makefile for ex1.c

CC = gcc            # Compiler
CFLAGS = -g -Wall   # Compiler flags: -g for debugging symbols, -Wall to enable warnings
TARGET = ex1        # Name of the executable

all: $(TARGET)

$(TARGET): ex1.c
	$(CC) $(CFLAGS) -o $(TARGET) ex1.c

clean:
	rm -f $(TARGET)

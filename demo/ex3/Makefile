# Makefile for ex1.c

CC ?= gcc              # Compiler
CFLAGS = -g -Wall -O0  # Compiler flags: -g for debugging symbols, -Wall to enable warnings
TARGET = ex3           # Name of the executable

all: $(TARGET)

$(TARGET): ex3.c
	$(CC) $(CFLAGS) -o $(TARGET) ex3.c

clean:
	rm -f $(TARGET)

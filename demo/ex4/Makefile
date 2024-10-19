# Makefile for ex1.c

CC ?= gcc              # Compiler
CFLAGS = -g -Wall -O0  # Compiler flags: -g for debugging symbols, -Wall to enable warnings
TARGET = ex4           # Name of the executable

all: $(TARGET)

$(TARGET): ex4.c
	$(CC) $(CFLAGS) -o $(TARGET) ex4.c

clean:
	rm -f $(TARGET)

# Makefile for ex1.c

CC ?= gcc              # Compiler
CFLAGS = -g -Wall -O0  # Compiler flags: -g for debugging symbols, -Wall to enable warnings
TARGET = ex2           # Name of the executable

all: $(TARGET)

$(TARGET): ex2.c
	$(CC) $(CFLAGS) -o $(TARGET) ex2.c

clean:
	rm -f $(TARGET)

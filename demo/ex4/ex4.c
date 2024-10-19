#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    // Read the first 4 bytes to determine the size
    unsigned int size;
    if (read(fd, &size, 4) != 4) {
        perror("Failed to read size");
        close(fd);
        return 1;
    }

    unsigned char *size_bytes = (unsigned char *)&size;
    unsigned char magic_bytes[2] = { 0xef, 0xbe}; 
    
    // Check and print messages for each matching byte
    if (size_bytes[0] == magic_bytes[0]) {
        printf("Byte 1 is match!\n");
    } else {
        printf("Byte 1 does not match.\n");
        return 1;
    }

    if (size_bytes[1] == magic_bytes[1]) {
        printf("Byte 2 is match!\n");
    } else {
        printf("Byte 2 does not match.\n");
        return 1;
    }

    // Vulnerable buffer: fixed-size but could overflow based on file contents
    char *buffer = (char *)malloc(MAX_BUFFER_SIZE); // Vulnerable buffer of size MAX_BUFFER_SIZE

    // Read 'size' bytes into the buffer, potential buffer overflow if size > MAX_BUFFER_SIZE
    if (read(fd, buffer, size) < 0) {
        perror("Failed to read file content");
        close(fd);
        return 1;
    }

    // Null-terminate the buffer
    buffer[MAX_BUFFER_SIZE - 1] = '\0';

    // Print buffer content
    printf("Buffer content: %s\n", buffer);

    close(fd);
    return 0;
}

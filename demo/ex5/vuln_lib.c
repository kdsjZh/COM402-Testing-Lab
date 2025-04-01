#include "vuln_lib.h"
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100
#define MAGIC_BYTES_1 0x6562785c // , 6461785c, 6564785c0xdeadbeef
#define MAGIC_BYTES_2 0x6461785c
#define MAGIC_BYTES_3 0x6564785c

void process_file(const char *data, unsigned int size) {
    if (size < 12) {
        printf("Input too small.\n");
        return;
    }

    // Extract first 12 bytes
    unsigned int extracted_1, extracted_2, extracted_3;
    memcpy(&extracted_1, data, 4);
    memcpy(&extracted_2, data + 4, 4);
    memcpy(&extracted_3, data + 8, 4);

    // Compare magic values
    if (extracted_1 == MAGIC_BYTES_1 &&
        extracted_2 == MAGIC_BYTES_2 &&
        extracted_3 == MAGIC_BYTES_3) {
        printf("All Magic Bytes match!\n");
    } else {
        printf("Magic Bytes do not match, %llx, %llx, %llx.\n", extracted_1, extracted_2, extracted_3);
        return;
    }

    // Vulnerable buffer: possible overflow if size > MAX_BUFFER_SIZE
    char buffer[MAX_BUFFER_SIZE];

    // Unsafe copy, possible buffer overflow
    memcpy(buffer, data + 12, size - 12);

    // Null-terminate buffer to prevent over-read issues
    buffer[MAX_BUFFER_SIZE - 1] = '\0';

    // printf("Buffer content: %s\n", buffer);
}


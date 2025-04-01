#include "vuln_lib.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>  

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 4) return 0;

    unsigned int extracted_size;
    memcpy(&extracted_size, data, 4);

    process_file((const char *)(data + 4), extracted_size);
    return 0;
}


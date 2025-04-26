#include <stdio.h>
#include <stdlib.h>
#include "nvml.h"

int main() {
    nvmlReturn_t result;

    // Initialize NVML library
    result = nvmlInit();
    if (NVML_SUCCESS != result) {
        fprintf(stderr, "Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return EXIT_FAILURE;
    }

    // Shutdown NVML library
    nvmlShutdown();

    return EXIT_SUCCESS;
}


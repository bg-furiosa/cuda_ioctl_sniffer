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

    // Get the device count
    unsigned int device_count;
    result = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result) {
        fprintf(stderr, "Failed to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return EXIT_FAILURE;
    }

    printf("Found %u GPU(s)\n", device_count);

    // Shutdown NVML library
    nvmlShutdown();

    return EXIT_SUCCESS;
}


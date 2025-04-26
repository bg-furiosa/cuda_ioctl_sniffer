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
    unsigned int device_count, i, temp;
    result = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result) {
        fprintf(stderr, "Failed to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return EXIT_FAILURE;
    }

    printf("Found %u GPU(s)\n", device_count);

    // Iterate over each device
    for (unsigned int i = 0; i < device_count; i++) {
        nvmlDevice_t device;
        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        char serial[NVML_DEVICE_SERIAL_BUFFER_SIZE];
        char uuid[NVML_DEVICE_UUID_BUFFER_SIZE];

        // Get device handle
        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (NVML_SUCCESS != result) {
            fprintf(stderr, "Failed to get handle for GPU %u: %s\n", i, nvmlErrorString(result));
            continue;
        }

        result = nvmlDeviceGetHandleByIndex(0, &device);
        if (NVML_SUCCESS != result) {
            printf("Failed to get handle for GPU 0: %s\n", nvmlErrorString(result));
            nvmlShutdown();
            return -1;
        }

        result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
        if (NVML_SUCCESS != result) {
            printf("Failed to get temperature for GPU 0: %s\n", nvmlErrorString(result));
        } else {
            printf("GPU 0 Temperature: %u C\n", temp);
        }



    }

    // Shutdown NVML library
    nvmlShutdown();

    return EXIT_SUCCESS;
}


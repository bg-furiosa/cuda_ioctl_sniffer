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

        // Get device name
        result = nvmlDeviceGetName(device, name, sizeof(name));
        if (NVML_SUCCESS != result) {
            fprintf(stderr, "Failed to get name for GPU %u: %s\n", i, nvmlErrorString(result));
            continue;
        }

        // Get device serial
        result = nvmlDeviceGetSerial(device, serial, sizeof(serial));
        if (NVML_SUCCESS != result) {
            fprintf(stderr, "Failed to get serial for GPU %u: %s\n", i, nvmlErrorString(result));
            continue;
        }

        // Get device UUID
        result = nvmlDeviceGetUUID(device, uuid, sizeof(uuid));
        if (NVML_SUCCESS != result) {
            fprintf(stderr, "Failed to get UUID for GPU %u: %s\n", i, nvmlErrorString(result));
            continue;
        }

        // Print device information
        printf("GPU #%u\n", i);
        printf("  Name  : %s\n", name);
        printf("  Serial: %s\n", serial);
        printf("  UUID  : %s\n", uuid);
    }

    // Shutdown NVML library
    nvmlShutdown();

    return EXIT_SUCCESS;
}


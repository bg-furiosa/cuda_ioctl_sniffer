#include <stdio.h>
#include <stdlib.h>
#include "nvml.h"

int main() {
    nvmlReturn_t result;
    unsigned int device_count;

    // Initialize NVML library
    result = nvmlInit();
    if (NVML_SUCCESS != result) {
        fprintf(stderr, "Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return EXIT_FAILURE;
    }

    result = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result) {
        printf("Failed to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return -1;
    }


    for (unsigned int i = 0; i < device_count; i++) {
	nvmlDevice_t device;
        unsigned int graphicsClockMHz;
        unsigned int smClockMHz;

        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (NVML_SUCCESS != result) {
            printf("Failed to get handle for GPU %d: %s\n", i, nvmlErrorString(result));
            continue;
        }

        result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_GRAPHICS, &graphicsClockMHz);
        if (NVML_SUCCESS != result) {
            printf("Failed to get graphics clock for GPU %d: %s\n", i, nvmlErrorString(result));
            continue;
        }

        result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_SM, &smClockMHz);
        if (NVML_SUCCESS != result) {
            printf("Failed to get SM clock for GPU %d: %s\n", i, nvmlErrorString(result));
            continue;
        }

        printf("GPU #%d\n", i);
        printf("  Graphics Clock: %u MHz\n", graphicsClockMHz);
        printf("  SM Clock: %u MHz\n", smClockMHz);


    }

    // Shutdown NVML library
    nvmlShutdown();

    return EXIT_SUCCESS;
}


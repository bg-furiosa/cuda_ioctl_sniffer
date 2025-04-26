#include <stdio.h>
#include <nvml.h>

int main(void) {
    nvmlReturn_t result;
    nvmlDevice_t device;
    unsigned int device_count;

    result = nvmlInit();
    if (NVML_SUCCESS != result) {
        printf("NVML initialization failed: %s\n", nvmlErrorString(result));
        return 1;
    }

    result = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result) {
        printf("Unable to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }

    for (unsigned int i = 0; i < device_count; i++) {
        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (NVML_SUCCESS != result) {
            printf("Unable to get device handle for GPU %u: %s\n", i, nvmlErrorString(result));
            continue;
        }

        unsigned long long error_count;
        result = nvmlDeviceGetMemoryErrorCounter(
            device,
            NVML_MEMORY_ERROR_TYPE_CORRECTED, // Corrected error
            NVML_VOLATILE_ECC,                // Volatile ECC errors (e.g., DRAM)
            NVML_MEMORY_LOCATION_DEVICE_MEMORY, // GPU memory
            &error_count
        );

        if (NVML_SUCCESS == result) {
            printf("GPU %u Volatile ECC Corrected Device Memory Errors: %llu\n", i, error_count);
        } else if (result == NVML_ERROR_NOT_SUPPORTED) {
            printf("GPU %u does not support ECC or requested error counter type.\n", i);
        } else {
            printf("Failed to get memory error counter for GPU %u: %s\n", i, nvmlErrorString(result));
        }
    }

    nvmlShutdown();
    return 0;
}

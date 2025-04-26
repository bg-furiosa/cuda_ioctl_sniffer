#include <stdio.h>
#include <nvml.h>

int main() {
    nvmlReturn_t result;
    nvmlDevice_t device;
    unsigned int device_count, memory_temp;

    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return 1;
    }

    result = nvmlDeviceGetCount(&device_count);
    if (result != NVML_SUCCESS) {
        printf("Failed to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }

    for (unsigned int i = 0; i < device_count; i++) {
        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (result != NVML_SUCCESS) {
            printf("Failed to get handle for device %u: %s\n", i, nvmlErrorString(result));
            continue;
        }

        result = nvmlDeviceGetTemperature(device, NVML_THERMAL_TARGET_MEMORY, &memory_temp);
        if (result == NVML_SUCCESS) {
            printf("GPU %u Memory Temperature: %u °C\n", i, memory_temp);
        } else {
            printf("Failed to get memory temperature for GPU %u: %s\n", i, nvmlErrorString(result));
        }
    }

    nvmlShutdown();
    return 0;
}

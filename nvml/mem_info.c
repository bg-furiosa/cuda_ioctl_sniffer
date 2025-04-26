#include <stdio.h>
#include <nvml.h>

int main(void) {
    nvmlReturn_t result;
    nvmlDevice_t device;
    nvmlMemory_t memInfo;

    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return -1;
    }

    result = nvmlDeviceGetHandleByIndex(0, &device);
    if (result != NVML_SUCCESS) {
        printf("Failed to get handle for device 0: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return -1;
    }

    result = nvmlDeviceGetMemoryInfo(device, &memInfo);
    if (result != NVML_SUCCESS) {
        printf("Failed to get memory info: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return -1;
    }

    printf("GPU Memory Information:\n");
    printf("  Total memory: %llu MB\n", memInfo.total / (1024 * 1024));
    printf("  Used memory : %llu MB\n", memInfo.used / (1024 * 1024));
    printf("  Free memory : %llu MB\n", memInfo.free / (1024 * 1024));

    nvmlShutdown();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <nvml.h>

int main() {
    nvmlReturn_t result;
    nvmlDevice_t device;
    nvmlUtilization_t utilization;

    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        fprintf(stderr, "Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return 1;
    }

    result = nvmlDeviceGetHandleByIndex(0, &device);
    if (result != NVML_SUCCESS) {
        fprintf(stderr, "Failed to get device handle: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }

    result = nvmlDeviceGetUtilizationRates(device, &utilization);
    if (result != NVML_SUCCESS) {
        fprintf(stderr, "Failed to get GPU utilization: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 1;
    }

    printf("GPU Utilization: %u%%\n", utilization.gpu);
    printf("Memory Utilization: %u%%\n", utilization.memory);

    nvmlShutdown();
    return 0;
}

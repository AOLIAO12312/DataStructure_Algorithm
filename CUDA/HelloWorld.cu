#include <stdio.h>
#include "cuda_runtime.h"

__global__ void helloworld() {
    printf("Hello world from CUDA\n");
}

int main() {
    helloworld <<<1, 12>>> ();
    cudaDeviceSynchronize();
    return 0;
}
#include <cuda_runtime.h>

void TaskAddValuesGPU()
{
    int* values;
    cudaMalloc( &values, 10 );
    cudaFree( values );
}

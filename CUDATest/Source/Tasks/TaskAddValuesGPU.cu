#include <cuda_runtime.h>
#include <cmath>
#include <assert.h>
#include "Utility/Helpers.h"

// CUDA Kernel function to add the elements of two arrays on the GPU
__global__
void addNElementsGPU1Thread(int n, float* x, float* y)
{
    for( int i = 0; i < n; i++ )
    {
        y[i] = x[i] + y[i];
    }
}

__global__
void addNElementsGPU1Block(int n, float* x, float* y)
{
    int index = threadIdx.x;
    int stride = blockDim.x;
    for( int i = index; i < n; i += stride)
    {
        y[i] = x[i] + y[i];
    }
}

__global__
void addNElementsGPUManyBlocks(int n, float* x, float* y)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for( int i = index; i < n; i += stride)
    {
        y[i] = x[i] + y[i];
    }
}

double TaskAddValuesGPU(int numElements, int method)
{
    float* x;
    float* y;

    // Allocate Unified Memory – accessible from CPU or GPU.
    cudaMallocManaged( &x, numElements*sizeof(float) );
    cudaMallocManaged( &y, numElements*sizeof(float) );

    // Initialize x and y arrays on the host.
    for( int i=0; i<numElements; i++ )
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    double startTime = MyGetSystemTime();

    // Run kernel on all elements on the GPU.
    if( method == 0 )
    {
        addNElementsGPU1Thread<<<1, 1>>>( numElements, x, y );
    }
    if( method == 1 )
    {
        int blockSize = 256;
        addNElementsGPU1Block<<<1, blockSize>>>( numElements, x, y );
    }
    if( method == 2 )
    {
        int blockSize = 256;
        int numBlocks = (numElements + blockSize - 1) / blockSize;
        addNElementsGPUManyBlocks<<<numBlocks, blockSize>>>( numElements, x, y );
    }

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    double endTime = MyGetSystemTime();
    double runTime = endTime - startTime;

    // Check for errors (all values should be 3.0f).
    float maxError = 0.0f;
    for( int i=0; i<numElements; i++ )
    {
        float error = fabs( y[i] - 3.0f );
        maxError = fmax( maxError, error );
    }

    // There should be no error with this function.
    assert( maxError == 0.0f );

    // Free memory.
    cudaFree( x );
    cudaFree( y );

    return runTime;
}

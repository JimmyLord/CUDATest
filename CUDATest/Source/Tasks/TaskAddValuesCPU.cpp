#include <Windows.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "Utility/Helpers.h"

// Following tutorial on NVIDIA Blog:
// https://developer.nvidia.com/blog/even-easier-introduction-cuda/

void addNElements(int n, float* x, float* y)
{
    for( int i=0; i<n; i++ )
        y[i] = x[i] + y[i];
}

void TaskAddValuesCPU()
{
    int numElements = 1<<27; // 134 million elements.

    float* x = new float[numElements];
    float* y = new float[numElements];

    // Initialize x and y arrays on the host.
    for( int i=0; i<numElements; i++ )
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // Run kernel on 1M elements on the CPU.
    addNElements( numElements, x, y );

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
    delete[] x;
    delete[] y;
}

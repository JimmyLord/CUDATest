#include <Windows.h>
#include <cmath>
#include <assert.h>
#include "Utility/Helpers.h"

// Following tutorial on NVIDIA Blog:
// https://developer.nvidia.com/blog/even-easier-introduction-cuda/

void addNElementsCPU(int n, float* x, float* y)
{
    for( int i = 0; i < n; i++ )
    {
        y[i] = x[i] + y[i];
    }
}

double TaskAddValuesCPU(int numElements)
{
    // Allocate storage.
    float* x = new float[numElements];
    float* y = new float[numElements];

    // Initialize x and y arrays on the host.
    for( int i=0; i<numElements; i++ )
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    double startTime = MyGetSystemTime();

    // Run kernel on all elements on the CPU.
    addNElementsCPU( numElements, x, y );

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
    delete[] x;
    delete[] y;

    return runTime;
}

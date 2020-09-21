#include <Windows.h>
#include <iostream>
#include <math.h>
#include <assert.h>

// Following tutorial on NVIDIA Blog:
// https://developer.nvidia.com/blog/even-easier-introduction-cuda/

double GetSystemTime()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
    QueryPerformanceCounter( (LARGE_INTEGER*)&time );

    double timeseconds = (double)time / freq;

    return timeseconds;
}

void addNElements(int n, float* x, float* y)
{
    for( int i=0; i<n; i++ )
        y[i] = x[i] + y[i];
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
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

    double startTime = GetSystemTime();

    // Run kernel on 1M elements on the CPU.
    addNElements( numElements, x, y );

    double endTime = GetSystemTime();
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

    return 0;
}

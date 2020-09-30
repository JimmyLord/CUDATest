#include <Windows.h>

#include "Utility/Helpers.h"
#include "Tasks/TaskAddValuesCPU.h"
#include "Tasks/TaskAddValuesGPU.cuh"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    double runTimeCPU = 0;
    double runTimeGPU0 = 0;
    double runTimeGPU1 = 0;
    double runTimeGPU2 = 0;
    double innerLoopTimeCPU = 0;
    double innerLoopTimeGPU0 = 0;
    double innerLoopTimeGPU1 = 0;
    double innerLoopTimeGPU2 = 0;

    int numElements = 1<<20; // 1 million elements.

    // Run task on CPU.
    {
        double startTime = MyGetSystemTime();

        innerLoopTimeCPU = TaskAddValuesCPU( numElements );

        double endTime = MyGetSystemTime();
        runTimeCPU = endTime - startTime;
    }

    // Run task on GPU (1 thread).
    {
        double startTime = MyGetSystemTime();

        innerLoopTimeGPU0 = TaskAddValuesGPU( numElements, 0 );

        double endTime = MyGetSystemTime();
        runTimeGPU0 = endTime - startTime;
    }

    // Run task on GPU (1 block).
    {
        double startTime = MyGetSystemTime();

        innerLoopTimeGPU1 = TaskAddValuesGPU( numElements, 1 );

        double endTime = MyGetSystemTime();
        runTimeGPU1 = endTime - startTime;
    }

    // Run task on GPU (many blocks).
    {
        double startTime = MyGetSystemTime();

        innerLoopTimeGPU2 = TaskAddValuesGPU( numElements, 2 );

        double endTime = MyGetSystemTime();
        runTimeGPU2 = endTime - startTime;
    }

    OutputMessage( "         CPU time: %0.4f (%0.4f)\n", runTimeCPU, innerLoopTimeCPU );
    OutputMessage( "GPU time 1 thread: %0.4f (%0.4f)\n", runTimeGPU0, innerLoopTimeGPU0 );
    OutputMessage( "GPU time 1 block:  %0.4f (%0.4f)\n", runTimeGPU1, innerLoopTimeGPU1 );
    OutputMessage( "GPU time n blocks: %0.4f (%0.4f)\n", runTimeGPU2, innerLoopTimeGPU2 );

    return 0;
}

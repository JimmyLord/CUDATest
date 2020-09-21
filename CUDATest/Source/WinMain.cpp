#include <Windows.h>

#include "Utility/Helpers.h"
#include "Tasks/TaskAddValuesCPU.h"
#include "Tasks/TaskAddValuesGPU.cuh"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    double runTimeCPU = 0;
    double runTimeGPU = 0;

    // Run task on CPU.
    {
        double startTime = MyGetSystemTime();

        TaskAddValuesCPU();

        double endTime = MyGetSystemTime();
        runTimeCPU = endTime - startTime;
    }

    // Run task on GPU.
    {
        double startTime = MyGetSystemTime();

        TaskAddValuesGPU();

        double endTime = MyGetSystemTime();
        runTimeGPU = endTime - startTime;
    }

    OutputMessage( "CPU time: %0.4f\n", runTimeCPU );
    OutputMessage( "GPU time: %0.4f\n", runTimeGPU );

    return 0;
}

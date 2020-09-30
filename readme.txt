All of this can be ignored for now, the solution and vcproj are
    prebuilt in the build folder.
    There are too many settings I'm not sure can be set with premake5.

Current hardcoded values that will need updating:
premake5.lua: contains "BuildCustomizations/CUDA 11.0"

Build Instructions:
    Project files are currently being created with premake5,
        but premake5 doesn't support CUDA or at least I didn't try

    First time setup:
        - Copy "SetupPaths.bat - rename me" and rename to "SetupPaths.bat"
        - Update paths to tools in SetupPath.bat
        - Run GenerateProjectFiles.bat

    Whenever project files are regenerated:
        - Project Properties
            -> All Configurations
                -> CUDA C/C++ -> General -> Target Machine Platform -> 64 bit

        - .cu file Properties -> General -> Item Type -> Cuda C/C++

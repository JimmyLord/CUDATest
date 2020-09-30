workspace "CUDATest"
	configurations	{ "Debug", "Release" }
	platforms		{ "x64" }
	location		"build"
	characterset	"MBCS"
	startproject	"CUDATest"

project "CUDATest"
	kind				"WindowedApp"
	location			"build/CUDATest"
	debugdir			"CUDATest"
	buildcustomizations "BuildCustomizations/CUDA 11.0"

	files {
		"CUDATest/Source/**.cpp",
		"CUDATest/Source/**.h",
		"CUDATest/Source/**.cu",
		"CUDATest/Source/**.cuh",
		".gitignore",
		"GenerateProjectFiles.bat",
		"SetupPaths.bat",
		"premake5.lua",
		"readme.txt",
	}

	includedirs {
		"CUDATest/Source",
	}

	links {
	}

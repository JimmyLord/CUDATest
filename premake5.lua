workspace "CUDATest"
	configurations	{ "Debug", "Release" }
	platforms		{ "x64" }
	location		"build"
	characterset	"MBCS"
	startproject	"CUDATest"

project "CUDATest"
	kind		"WindowedApp"
	location	"build/CUDATest"
	debugdir	"CUDATest"

	files {
		"CUDATest/Source/**.cpp",
		"CUDATest/Source/**.h",
	}

	includedirs {
		"CUDATest/Source",
	}

	links {
	}

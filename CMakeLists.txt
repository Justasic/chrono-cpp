cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(cppchrono
	VERSION 1.0.0
	DESCRIPTION "C++ time parsing library"
	LANGUAGES CXX
)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

message(STATUS "Files: ${SOURCE_FILES}")

add_library(time ${SOURCE_FILES})
target_compile_options(time PUBLIC -Wall -Wfloat-conversion)
target_include_directories(time PRIVATE
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
set_target_properties(time
	PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
)


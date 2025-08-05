cmake_minimum_required(VERSION 3.30)

project("project" LANGUAGES CXX)

## Default options
# set(CMAKE_CXX_MODULE_STD ON) # waiting for clang 19
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_LINK_DEPENDS_NO_SHARED ON) # Do not relink all depended targets on .so
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


## Built-in modules
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckLinkerFlag)
include(CMakePrintHelpers)
enable_testing()

## Project modules
# Do not reorder include
include(cmake/PreventInSourceBuild.cmake)
include(cmake/ProjectOptions.cmake)
include(cmake/DetectCompiler.cmake)
include(cmake/SanitizerSupport.cmake)
include(cmake/Utility.cmake)
include(cmake/Warnings.cmake)
# include(cmake/HandleToolchain.cmake) # disable for now
include(cmake/PrintInfo.cmake)

add_subdirectory(third_party)
add_subdirectory(example)

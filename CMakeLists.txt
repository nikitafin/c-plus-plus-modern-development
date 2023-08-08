# FIXME(Nikita): version + cfg for all targets
cmake_minimum_required(VERSION 3.21)
project(c-plus-plus-modern-development)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API bf70d4b0-9fb7-465c-9803-34014e70d112)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# FIXME(Nikita): OFF default
option(ENABLE_TESTS "Enable tests" ON)

if (UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif ()


# FIXME(Nikita): into lib
include_directories(stuff)

# FIXME(Nikita): flags for all platrforms
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

# FIXME(Nikita): sanitizers as CMake Options
add_compile_options(-fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

# FIXME(Nikita): FIXME
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

add_subdirectory(shared)

if (${ENABLE_TESTS})
    enable_testing()
endif ()

# FIXME(Nikita): fix old project conf+build
# add_subdirectory(c-plus-plus-red)
add_subdirectory(c-plus-plus-brown)

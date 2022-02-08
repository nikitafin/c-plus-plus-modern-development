project(merge_sort3
        VERSION 1.0.0
        LANGUAGES CXX
        )

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")
file(GLOB_RECURSE src *.c* *.h*)
add_executable(${PROJECT_NAME} ${src})

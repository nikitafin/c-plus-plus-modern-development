project(week-5)
message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond  -Wextra-semi -Wfloat-equal -Wnon-virtual-dtor -Wsign-conversion")
endif ()


add_subdirectory(josephus_permutation)
add_subdirectory(simple_vector_copy_assignment_operator)
add_subdirectory(tokenizer)
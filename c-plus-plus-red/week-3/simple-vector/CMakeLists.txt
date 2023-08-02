project(
        simple-vector
        VERSION 0.1.0
        HOMEPAGE_URL "https://github.com/nikitafin/c-plus-plus-modern-development"
        LANGUAGES CXX)

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")

add_executable(simple-vector simple_vector.cpp simple_vector.h)

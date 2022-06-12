project(
  simple_vector_copy_assignment_operator
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/nikitafin/c-plus-plus-modern-development"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")
add_executable(simple_vector_copy_assignment_operator
               simple_vector_copy_assignment.cpp simple_vector.h)

project(
  PriorityCollection
  VERSION 1.0.0
  LANGUAGES CXX)

find_program(iwyu_path NAMES include-what-you-use iwyu REQUIRED)

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")
file(GLOB_RECURSE src *.c* *.h*)
add_executable(${PROJECT_NAME} ${src})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE
                                             ${iwyu_path})

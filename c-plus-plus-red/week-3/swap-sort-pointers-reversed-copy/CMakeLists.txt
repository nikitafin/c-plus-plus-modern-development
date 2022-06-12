project(
  swap-sort-reversed
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/nikitafin/c-plus-plus-modern-development"
  LANGUAGES CXX)

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")

add_executable(main swap_sort_copy.cpp)

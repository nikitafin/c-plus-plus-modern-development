project(
  server_stats
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/nikitafin/c-plus-plus-modern-development"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")
add_executable(server_stats server_stats.cpp http_request.h stats.h stats.cpp)

if(UNIX)
  set(CMAKE_CXX_FLAGS -Wall)
endif()

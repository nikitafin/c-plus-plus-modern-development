project(
        text_editor
        VERSION 1.0.0
        HOMEPAGE_URL "https://github.com/nikitafin/c-plus-plus-modern-development"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")
add_executable(text_editor text_editor.cpp)

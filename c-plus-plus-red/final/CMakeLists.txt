project(red_final)
message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")

add_executable(
        part1

        main.cpp
        iterator_range.h

        parse.cpp
        parse.h

        search_server.cpp
        search_server.h
)

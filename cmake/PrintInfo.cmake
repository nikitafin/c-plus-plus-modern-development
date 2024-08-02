message(STATUS "Build Info:")
message(STATUS "  Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Host System: ${CMAKE_HOST_SYSTEM}")
message(STATUS "  Host System Name: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "  Host System Processor: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "  Host System Version: ${CMAKE_HOST_SYSTEM_VERSION}")

message(STATUS)
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Compiler Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler Standard Required: ${CMAKE_CXX_STANDARD_REQUIRED}")
message(STATUS "  Compiler Extensions: ${CMAKE_CXX_EXTENSIONS}")

message(STATUS)
message(STATUS "  Linker: ${CMAKE_CXX_COMPILER_LINKER}")

message(STATUS)
message(STATUS "  Default FLAGS: ${PROJECT_DEFAULT_CXX_FLAGS}")
message(STATUS "  Compile options: ${PROJECT_COMPILE_OPTIONS}")
message(STATUS "  Compile definitions: ${PROJECT_COMPILE_DEFINITIONS}")
message(STATUS "  Link options: ${PROJECT_LINK_OPTIONS}")



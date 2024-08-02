include_guard(GLOBAL)
message(STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}")

string(TOUPPER ${CMAKE_BUILD_TYPE} PROJECT_BUILD_TYPE)

# Variables to fill
set(PROJECT_COMPILE_OPTIONS)
set(PROJECT_COMPILE_DEFINITIONS)
set(PROJECT_LINK_OPTIONS)

# Grab defaults
set(PROJECT_DEFAULT_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${PROJECT_BUILD_TYPE}}")
separate_arguments(PROJECT_DEFAULT_CXX_FLAGS)

list(SORT PROJECT_DEFAULT_CXX_FLAGS)
list(REMOVE_DUPLICATES PROJECT_DEFAULT_CXX_FLAGS)
list(APPEND PROJECT_COMPILE_OPTIONS ${PROJECT_DEFAULT_CXX_FLAGS})

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_${PROJECT_BUILD_TYPE} "")

# Sanitizers
if (PROJECT_SANITIZERS)
    append_compile_option(PROJECT_COMPILE_OPTIONS -g)
    append_compile_option(PROJECT_COMPILE_OPTIONS -fno-omit-frame-pointer)

    # BUG(nikitafin): -fsanitize=address check failed no idea why
    list(APPEND PROJECT_COMPILE_OPTIONS -fsanitize=${PROJECT_SANITIZERS_STRING})
    #    append_compile_option(PROJECT_COMPILE_OPTIONS -fsanitize=${PROJECT_SANITIZERS_STRING})

    append_link_option(PROJECT_LINK_OPTIONS -fsanitize=${PROJECT_SANITIZERS_STRING})
endif ()

# Per compiler tune
if (PROJECT_COMPILER_CLANG)
    append_compile_option(PROJECT_COMPILE_OPTIONS -static)

    append_link_option(PROJECT_LINK_OPTIONS -stdlib=libc++)

endif ()


## Some (body)
#list(SORT PROJECT_COMPILE_OPTIONS)
#list(SORT PROJECT_COMPILE_DEFINITIONS)
#list(SORT PROJECT_LINK_OPTIONS)

# Apply
add_compile_options(${PROJECT_COMPILE_OPTIONS})
add_compile_definitions(${PROJECT_COMPILE_DEFINITIONS})
add_link_options(${PROJECT_LINK_OPTIONS})
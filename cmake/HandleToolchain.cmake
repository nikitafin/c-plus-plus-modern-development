#####################################################################
# Handle Compiler/Linker/Asm
# NOTE: We apply this options to both ThirdParty and Own sources
#####################################################################
INCLUDE_GUARD ( GLOBAL )
MESSAGE ( STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}" )

# Enable the ability to organize targets into hierarchies of "folders" for capable GUI-based IDEs.
SET_PROPERTY ( GLOBAL PROPERTY USE_FOLDERS ON )

#####################################################################
# Variables to determine
SET ( PROJECT_COMPILE_OPTIONS       )
SET ( PROJECT_COMPILE_DEFINITIONS   )
SET ( PROJECT_LINK_OPTIONS          )

#####################################################################
# Default compiler options
SET  ( PROJECT_DEFAULT_COMPILE_OPTIONS )
LIST ( APPEND PROJECT_DEFAULT_COMPILE_OPTIONS
    ${CMAKE_CXX_FLAGS}
    ${CMAKE_CXX_FlAGS_${PROJECT_BUILD_TYPE_UC}}
)
UNIFY_LIST ( PROJECT_DEFAULT_COMPILE_OPTIONS )

#####################################################################
# Default linker options
SET  ( PROJECT_DEFAULT_LINK_OPTIONS )
LIST ( APPEND PROJECT_DEFAULT_LINK_OPTIONS
    ${CMAKE_EXE_LINKER_FLAGS}
    ${CMAKE_EXE_LINKER_FLAGS_${PROJECT_BUILD_TYPE_UC}}
)
UNIFY_LIST ( PROJECT_DEFAULT_LINK_OPTIONS )

#####################################################################
# Both GCC/Clang options
IF ( PROJECT_COMPILER_GCC  OR PROJECT_COMPILER_CLANG )
    APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fexceptions" )

    # improve debugger support
    APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fno-omit-frame-pointer"   )
    IF ( PROJECT_BUILD_TYPE STREQUAL "Debug" )
        APPEND_UNIQUE ( PROJECT_COMPILE_DEFINITIONS "_GLIBCXX_DEBUG"    )
    ENDIF ()
    IF ( CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" )
        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-g"    )
    ENDIF ( )

    # Enable checks in standard library
    REMOVE_DEFINITIONS ( _FORTIFY_SOURCE )

    APPEND_UNIQUE ( PROJECT_COMPILE_DEFINITIONS "_FORTIFY_SOURCE=3"     )
    APPEND_UNIQUE ( PROJECT_COMPILE_DEFINITIONS "_GLIBCXX_ASSERTIONS"   )
ENDIF ( )

#####################################################################
# Clang options
IF ( PROJECT_COMPILER_CLANG )
    IF ( CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" )
        # improve debugger support
        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fstandalone-debug" )
    ENDIF ( )

    APPEND_UNIQUE ( PROJECT_COMPILE_DEFINITIONS "_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE" )
ENDIF ( )

#####################################################################
# Sanitizers
IF ( PROJECT_SANITIZER_USING )
    IF ( PROJECT_COMPILER_GCC OR PROJECT_COMPILER_CLANG )
        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-g"                          )
        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fno-omit-frame-pointer"     )
        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fno-optimize-sibling-calls" )
        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fno-common"                 )


        APPEND_UNIQUE ( PROJECT_COMPILE_OPTIONS "-fsanitize=${PROJECT_SANITIZER_STRING}" )
        APPEND_UNIQUE ( PROJECT_LINK_OPTIONS    "-fsanitize=${PROJECT_SANITIZER_STRING}" )
    ENDIF ( )
ENDIF ( )

#####################################################################
# Apply options
ADD_COMPILE_OPTIONS     ( ${PROJECT_COMPILE_OPTIONS}        )
ADD_COMPILE_DEFINITIONS ( ${PROJECT_COMPILE_DEFINITIONS}    )
ADD_LINK_OPTIONS        ( ${PROJECT_LINK_OPTIONS}           )

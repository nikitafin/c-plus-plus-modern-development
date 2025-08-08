#####################################################################
# Detect various stuff
#####################################################################
INCLUDE_GUARD ( GLOBAL )
MESSAGE ( STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}" )

#####################################################################
# Compiler
#####################################################################
SET ( PROJECT_COMPILER ${CMAKE_CXX_COMPILER_ID} )

SET ( PROJECT_COMPILER_CLANG OFF )
SET ( PROJECT_COMPILER_GCC   OFF )

IF ( WIN32 )
    IF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        SET ( PROJECT_COMPILER_CLANG ON )
    ELSEIF (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
        SET ( PROJECT_COMPILER_GCC ON )
    ELSE ()
        MESSAGE ( WARNING "Unsupported compiler: ${PROJECT_COMPILER}" )
    ENDIF ()
ELSE ( )
    IF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        SET ( PROJECT_COMPILER_CLANG ON )
    ELSEIF (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
        SET ( PROJECT_COMPILER_GCC ON )
    ELSE ()
        MESSAGE ( WARNING "Unsupported compiler: ${PROJECT_COMPILER}" )
    ENDIF ()
ENDIF ()

#####################################################################
# Build type
#####################################################################
SET ( USER_CMAKE_BUILD_TYPE_VALUES "Release" "Debug" "RelWithDebInfo" "MinSizeRel" )
IF ( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
    SET ( CMAKE_BUILD_TYPE "RelWithDebInfo" )
    MESSAGE ( STATUS "CMAKE_BUILD_TYPE is not set, set to default = ${CMAKE_BUILD_TYPE}" )
    MESSAGE ( "
You can pass -DCMAKE_BUILD_TYPE=<type> in order to configure.
Available options are:
  * -DCMAKE_BUILD_TYPE=Release - For an optimized build with no assertions or debug info.
  * -DCMAKE_BUILD_TYPE=Debug - For an unoptimized build with assertions and debug info.
  * -DCMAKE_BUILD_TYPE=RelWithDebInfo - For an optimized build with no assertions but with debug info.
  * -DCMAKE_BUILD_TYPE=MinSizeRel - For a build optimized for size instead of speed.
" )
ELSE ( )
    IF ( NOT ${CMAKE_BUILD_TYPE} IN_LIST USER_CMAKE_BUILD_TYPE_VALUES )
        MESSAGE ( FATAL_ERROR "Unsupported CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} (Available: ${USER_CMAKE_BUILD_TYPE_VALUES})" )
    ENDIF ( )
ENDIF ( )

STRING ( TOUPPER "${CMAKE_BUILD_TYPE}" PROJECT_BUILD_TYPE_UC )

#####################################################################
# Sanitizers
#####################################################################
SET ( PROJECT_SANITIZER_ADDRESS_SUPPORTED   OFF )
SET ( PROJECT_SANITIZER_UNDEFINED_SUPPORTED OFF )
SET ( PROJECT_SANITIZER_THREAD_SUPPORTED    OFF )
SET ( PROJECT_SANITIZER_LEAK_SUPPORTED      OFF )
SET ( PROJECT_SANITIZER_MEMORY_SUPPORTED    OFF )

IF ( WIN32 )
    IF ( PROJECT_COMPILER_CLANG AND NOT MINGW )
        SET ( PROJECT_SANITIZER_ADDRESS_SUPPORTED   ON )
        SET ( PROJECT_SANITIZER_UNDEFINED_SUPPORTED ON )
    ENDIF( )
ELSEIF ( LINUX )
    SET ( PROJECT_SANITIZER_ADDRESS_SUPPORTED   ON )
    SET ( PROJECT_SANITIZER_UNDEFINED_SUPPORTED ON )

    IF ( PROJECT_COMPILER_CLANG )
        SET ( PROJECT_SANITIZER_THREAD_SUPPORTED    ON )
        SET ( PROJECT_SANITIZER_LEAK_SUPPORTED      ON )
        SET ( PROJECT_SANITIZER_MEMORY_SUPPORTED    ON )
    ENDIF ( )
ELSE ( )
    MESSAGE ( FATAL_ERROR "Unsupported platform CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
ENDIF ()

SET ( PROJECT_SANITIZER_LIST   )
SET ( PROJECT_SANITIZER_STRING )
SET ( PROJECT_SANITIZER_USING OFF )

SET ( PROJECT_SANITIZER_ADDRESS_USING     OFF)
SET ( PROJECT_SANITIZER_UNDEFINED_USING   OFF)
SET ( PROJECT_SANITIZER_THREAD_USING      OFF)
SET ( PROJECT_SANITIZER_LEAK_USING        OFF)
SET ( PROJECT_SANITIZER_MEMORY_USING      OFF)

IF ( PROJECT_SANITIZER_ADDRESS_ENABLED AND PROJECT_SANITIZER_ADDRESS_SUPPORTED )
    SET  ( PROJECT_SANITIZER_ADDRESS_USING ON      )
    SET  ( PROJECT_SANITIZER_USING ON              )
    LIST ( APPEND PROJECT_SANITIZER_LIST "address" )
ELSEIF ( PROJECT_SANITIZER_ADDRESS_ENABLED AND NOT PROJECT_SANITIZER_ADDRESS_SUPPORTED )
    MESSAGE ( FATAL_ERROR "Try to using AddressSanitizer but it's not supported" )
ENDIF ( )

IF ( PROJECT_SANITIZER_UNDEFINED_ENABLED AND PROJECT_SANITIZER_UNDEFINED_SUPPORTED )
    SET  ( PROJECT_SANITIZER_UNDEFINED_USING ON      )
    SET  ( PROJECT_SANITIZER_USING ON                )
    LIST ( APPEND PROJECT_SANITIZER_LIST "undefined" )
ELSEIF ( PROJECT_SANITIZER_UNDEFINED_ENABLED AND NOT PROJECT_SANITIZER_UNDEFINED_SUPPORTED )
    MESSAGE ( FATAL_ERROR "Try to using UndefinedBehaviourSanitizer but it's not supported" )
ENDIF ()

# TODO ( nikitafin ) : add other sanitizer support
LIST ( JOIN PROJECT_SANITIZER_LIST "," PROJECT_SANITIZER_STRING)

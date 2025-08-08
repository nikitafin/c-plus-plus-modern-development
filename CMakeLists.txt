#####################################################################
# TODO ( nikitafin ) : support using this project as submodule
CMAKE_MINIMUM_REQUIRED( VERSION 3.30 )

#####################################################################
## Default options
SET ( CMAKE_CXX_STANDARD            17  )
SET ( CMAKE_CXX_STANDARD_REQUIRED   ON  )
SET ( CMAKE_CXX_EXTENSIONS          OFF )
SET ( CMAKE_EXPORT_COMPILE_COMMANDS ON  )

# NOTE ( nikitafin ) : place library dll and exe in same folder
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )

SET ( CMAKE_SHARED_LIBRARY_PREFIX "" )
SET ( CMAKE_STATIC_LIBRARY_PREFIX "" )

SET ( CMAKE_PLATFORM_NO_VERSIONED_SONAME ON )

#####################################################################
PROJECT( "ModernCXX" LANGUAGES CXX )

#####################################################################
# Built-in modules
INCLUDE (GoogleTest)
INCLUDE (CheckCXXCompilerFlag)

#####################################################################
# Project modules ( do not reorder without reason )
INCLUDE ( cmake/PreventInSourceBuild.cmake  )
INCLUDE ( cmake/ProjectOptions.cmake        )
INCLUDE ( cmake/Detector.cmake              )
INCLUDE ( cmake/Utility.cmake               )
INCLUDE ( cmake/HandleToolchain.cmake       )
INCLUDE ( cmake/Warnings.cmake              )
INCLUDE ( cmake/PrintInfo.cmake             )

IF ( BUILD_TESTING ) # TODO ( nikitafin ) : can we move this into handle toolchain file ?
    ENABLE_TESTING ( )
ENDIF ( )

#####################################################################
# Global dependencies
FIND_PACKAGE ( Threads REQUIRED )

ADD_SUBDIRECTORY ( third_party )
ADD_SUBDIRECTORY ( example )
ADD_SUBDIRECTORY ( libraries )
ADD_SUBDIRECTORY ( brown )
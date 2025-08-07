#####################################################################
# TODO ( nikitafin ) : support using this project as submodule
CMAKE_MINIMUM_REQUIRED( VERSION 3.30 )

#####################################################################
## Default options
SET ( CMAKE_CXX_STANDARD            17  )
SET ( CMAKE_CXX_STANDARD_REQUIRED   ON  )
SET ( CMAKE_CXX_EXTENSIONS          OFF )
SET ( CMAKE_EXPORT_COMPILE_COMMANDS ON  )

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

ADD_SUBDIRECTORY ( third_party )
ADD_SUBDIRECTORY ( example )
ADD_SUBDIRECTORY ( libraries )

#####################################################################
# Prevent build if configure in source directory
INCLUDE_GUARD ( GLOBAL )
MESSAGE ( STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}" )

# make sure the user doesn't play dirty with symlinks
GET_FILENAME_COMPONENT ( SRCDIR "${CMAKE_SOURCE_DIR}" REALPATH )
GET_FILENAME_COMPONENT ( BINDIR "${CMAKE_BINARY_DIR}" REALPATH )

# disallow in-source builds
IF ( "${SRCDIR}" STREQUAL "${BINDIR}" )
    MESSAGE ( "######################################################"              )
    MESSAGE ( "Warning: in-source builds are disabled"                              )
    MESSAGE ( "Please create a separate build directory and run cmake from there"   )
    MESSAGE ( "######################################################"              )
    MESSAGE ( FATAL_ERROR "Quitting configuration"                                  )
ENDIF ( )

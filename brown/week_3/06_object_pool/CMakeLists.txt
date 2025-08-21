ADD_EXECUTABLE        ( 06_object_pool object_pool.cpp )
TARGET_LINK_LIBRARIES ( 06_object_pool
        PRIVATE
        Threads::Threads
        Utility::Warnings
        ThirdParty::Doctest
)

IF ( MINGW )
    TARGET_COMPILE_OPTIONS     ( 06_object_pool PRIVATE -femulated-tls )
ENDIF ( )

TARGET_COMPILE_DEFINITIONS ( 06_object_pool PRIVATE WITH_TESTS                     )
SET_TARGET_PROPERTIES      ( 06_object_pool PROPERTIES COMPILE_WARNING_AS_ERROR ON )
ADD_TEST                   ( NAME 06_object_pool COMMAND 06_object_pool            )
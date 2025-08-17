ADD_EXECUTABLE        ( 04_concurrent_map_2 concurrent_map_2.cpp )
TARGET_LINK_LIBRARIES ( 04_concurrent_map_2
    PRIVATE
        Threads::Threads
        Utility::Warnings
        ThirdParty::Doctest
)

IF ( MINGW )
    TARGET_COMPILE_OPTIONS     ( 04_concurrent_map_2 PRIVATE -femulated-tls )
ENDIF ( )

TARGET_COMPILE_DEFINITIONS ( 04_concurrent_map_2 PRIVATE WITH_TESTS                       )
SET_TARGET_PROPERTIES      ( 04_concurrent_map_2 PROPERTIES COMPILE_WARNING_AS_ERROR ON   )
ADD_TEST                   ( NAME 04_concurrent_map_2 COMMAND 04_concurrent_map_2         )
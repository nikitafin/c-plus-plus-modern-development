ADD_EXECUTABLE        ( 03_synchronized_2 synchronized_2.cpp )
TARGET_LINK_LIBRARIES ( 03_synchronized_2
    PRIVATE
        Threads::Threads
        Utility::Warnings
        ThirdParty::Doctest
)

IF ( MINGW )
    TARGET_COMPILE_OPTIONS     ( 03_synchronized_2 PRIVATE -femulated-tls )
ENDIF ( )

TARGET_COMPILE_DEFINITIONS ( 03_synchronized_2 PRIVATE WITH_TESTS                       )
SET_TARGET_PROPERTIES      ( 03_synchronized_2 PROPERTIES COMPILE_WARNING_AS_ERROR ON   )
ADD_TEST                   ( NAME 03_synchronized_2 COMMAND 03_synchronized_2           )
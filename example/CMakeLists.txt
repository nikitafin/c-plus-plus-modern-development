IF ( NOT BUILD_EXAMPLES )
    RETURN ( )
ENDIF ()

IF ( BUILD_TESTING )
    ADD_EXECUTABLE ( some_body_test tests/some_body_src_test.cxx )
    TARGET_LINK_LIBRARIES ( some_body_test PRIVATE ThirdParty::GTestAll )
    ADD_TEST ( NAME some_body_test COMMAND some_body_test )
ENDIF ()

IF ( PROJECT_SANITIZER_ADDRESS_USING )
    ADD_EXECUTABLE ( ExampleAsan src/asan_example.cxx )
    TARGET_LINK_LIBRARIES( ExampleAsan PRIVATE Utility::Warnings)
ENDIF ()


GET_ALL_TARGETS ( EXAMPLE_TARGETS )

FOREACH ( TARGET IN LISTS EXAMPLE_TARGETS )
    SET_TARGET_PROPERTIES ( ${TARGET} PROPERTIES FOLDER "brown" )
endforeach ( )

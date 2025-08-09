ADD_EXECUTABLE ( 05_aggregator 
    main.cpp 
    stats_aggregator.cpp 
    stats_aggregator_test.cpp 
    stats_aggregator.h
)
TARGET_LINK_LIBRARIES ( 05_aggregator PRIVATE Utility::Warnings Library::TestRunner )
SET_TARGET_PROPERTIES ( 05_aggregator PROPERTIES COMPILE_WARNING_AS_ERROR ON        )

IF ( LINUX ) # NOTE ( nikitafin ) : how to run this test on windows ?
    ADD_TEST     ( NAME 05_aggregator COMMAND bash -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/testdata.txt | $<TARGET_FILE:05_aggregator>" )
    SET_PROPERTY ( TEST 05_aggregator PROPERTY PASS_REGULAR_EXPRESSION ".*10.*50.*150.*"                                            )
ENDIF ( )

FILE ( ARCHIVE_CREATE
    OUTPUT "${CMAKE_BINARY_DIR}/05_aggregator.zip"
    PATHS 
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/stats_aggregator.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/stats_aggregator_test.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/stats_aggregator.h"
    FORMAT "zip"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
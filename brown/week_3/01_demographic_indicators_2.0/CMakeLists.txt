###############################################################################
# Test
ADD_EXECUTABLE ( 01_demographic_indicators_2 print_stats_2.cpp )
TARGET_LINK_LIBRARIES ( 01_demographic_indicators_2 
    PRIVATE
        ThirdParty::Doctest
        Utility::Warnings
)
TARGET_COMPILE_DEFINITIONS ( 01_demographic_indicators_2 PRIVATE WITH_TESTS                       )
SET_TARGET_PROPERTIES      ( 01_demographic_indicators_2 PROPERTIES COMPILE_WARNING_AS_ERROR ON   )
ADD_TEST                   ( NAME 01_demographic_indicators_2 COMMAND 01_demographic_indicators_2 )

###############################################################################
# Cli
ADD_EXECUTABLE             ( 01_demographic_indicators_2_cli print_stats_2.cpp                      )
TARGET_LINK_LIBRARIES      ( 01_demographic_indicators_2_cli PRIVATE Utility::Warnings              )
SET_TARGET_PROPERTIES      ( 01_demographic_indicators_2_cli PROPERTIES COMPILE_WARNING_AS_ERROR ON )

ADD_CUSTOM_COMMAND (
    TARGET 01_demographic_indicators_2_cli
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running $<TARGET_FILE_NAME:01_demographic_indicators_2_cli> ..."
    COMMAND 01_demographic_indicators_2_cli < 1_in.txt > 1_out.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testdata
)

ADD_TEST(
    NAME 01_demographic_indicators_2_cli 
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol 1_out.txt 1_out_expected.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testdata
)


#[[
FILE ( TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/testdata/1_in.txt" TEST_INPUT )
FILE ( TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/testdata/1_out.txt" TEST_OUT  )

IF      ( WIN32 )
    ADD_TEST ( NAME 01_demographic_indicators_2_cli 
        COMMAND ${CMAKE_COMMAND} -E chdir $<TARGET_FILE_DIR:01_demographic_indicators_2_cli> $ENV{ComSpec} /c "$<TARGET_FILE_NAME:01_demographic_indicators_2_cli> < ${TEST_INPUT} > ${TEST_OUT}" )
ELSEIF  ( UNIX )
    ADD_TEST ( NAME 01_demographic_indicators_2_cli 
        COMMAND sh -c "$<TARGET_FILE:01_demographic_indicators_2_cli> ${TEST_INPUT} > ${TEST_OUT}" )
ENDIF   ()
]]
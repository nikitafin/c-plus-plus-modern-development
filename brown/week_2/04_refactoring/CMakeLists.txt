OPTION ( BROWN_REFACTORING_USE_GTEST "Use gtest instead of test_runner in refactoring task (brown_2_4)" ON )

ADD_EXECUTABLE ( 04_refactoring refactoring.cpp )
TARGET_LINK_LIBRARIES ( 04_refactoring
    PRIVATE
    Library::Xml2
    Library::Json2
    Utility::Warnings
)

SET_TARGET_PROPERTIES ( 04_refactoring PROPERTIES COMPILE_WARNING_AS_ERROR ON )

IF ( BROWN_REFACTORING_USE_GTEST )
    TARGET_LINK_LIBRARIES ( 04_refactoring PRIVATE ThirdParty::GTestAll)
    TARGET_COMPILE_DEFINITIONS ( 04_refactoring PRIVATE WITH_TESTS )
    GTEST_ADD_TESTS ( TARGET 04_refactoring )
ELSE ( )
    TARGET_LINK_LIBRARIES ( 04_refactoring PRIVATE Library::TestRunner)
    ADD_TEST ( NAME 04_refactoring COMMAND 04_refactoring)
ENDIF ( )



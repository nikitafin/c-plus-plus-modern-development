ADD_EXECUTABLE ( 01_spendings_xml spendings_xml.cpp )
TARGET_LINK_LIBRARIES ( 01_spendings_xml
    PRIVATE
        ThirdParty::GTestAll
        Library::Xml
        Utility::Warnings
)
TARGET_COMPILE_DEFINITIONS ( 01_spendings_xml PRIVATE WITH_TESTS )
GTEST_ADD_TESTS ( TARGET 01_spendings_xml )
ADD_EXECUTABLE ( 02_sendings_json spendings_json.cpp )
TARGET_LINK_LIBRARIES ( 02_sendings_json
    PRIVATE
    ThirdParty::GTestAll
    Library::Json
    Utility::Warnings
)
TARGET_COMPILE_DEFINITIONS ( 02_sendings_json PRIVATE WITH_TESTS )
GTEST_ADD_TESTS ( TARGET 02_sendings_json )

#####################################################################
# Googletest self build
#####################################################################

SET ( GOOGLETEST_ROOT_PATH "${CMAKE_SOURCE_DIR}/third_party/googletest" )
SET ( GOOGLETEST_PATH      ${GOOGLETEST_ROOT_PATH}/googletest           )

SET ( GOOLGETEST_SOURCES
    ${GOOGLETEST_PATH}/src/gtest-all.cc
)

SET ( GOOLGETEST_MAIN_SOURCES
    ${GOOGLETEST_PATH}/src/gtest_main.cc
)

#####################################################################
# GTest

ADD_LIBRARY ( ThirdPartyGTest ${GOOLGETEST_SOURCES}   )
ADD_LIBRARY ( ThirdParty::GTest ALIAS ThirdPartyGTest )

TARGET_INCLUDE_DIRECTORIES ( ThirdPartyGTest SYSTEM AFTER PUBLIC  ${GOOGLETEST_PATH}/include    )
TARGET_INCLUDE_DIRECTORIES ( ThirdPartyGTest SYSTEM AFTER PRIVATE ${GOOGLETEST_PATH} )

TARGET_COMPILE_DEFINITIONS ( ThirdPartyGTest PUBLIC GTEST_HAS_POSIX_RE=0 )

SET_TARGET_PROPERTIES ( ThirdPartyGTest PROPERTIES
    VERSION "1.15.3"
    FOLDER "third_party"
)

#####################################################################
# GTestMain
ADD_LIBRARY ( ThirdPartyGTestMain ${GOOLGETEST_MAIN_SOURCES}   )
ADD_LIBRARY ( ThirdParty::GTestMain ALIAS ThirdPartyGTestMain )

TARGET_LINK_LIBRARIES ( ThirdPartyGTestMain PRIVATE ThirdParty::GTest)

SET_TARGET_PROPERTIES ( ThirdPartyGTestMain PROPERTIES
    VERSION "1.15.3"
    FOLDER "third_party"
)

#####################################################################
# GTestAll
ADD_LIBRARY ( ThirdPartyGTestAll INTERFACE )
ADD_LIBRARY ( ThirdParty::GTestAll ALIAS ThirdPartyGTestAll)

TARGET_LINK_LIBRARIES ( ThirdPartyGTestAll INTERFACE ThirdParty::GTest ThirdParty::GTestMain )

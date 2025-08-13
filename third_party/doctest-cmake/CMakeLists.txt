#####################################################################
# Doctest self build
#####################################################################
SET ( DOCTEST_ROOT_PATH "${CMAKE_SOURCE_DIR}/third_party/doctest" )

ADD_LIBRARY ( ThirdPartyDoctest INTERFACE ${DOCTEST_ROOT_PATH}/doctest/doctest.h )
ADD_LIBRARY ( ThirdParty::Doctest ALIAS ThirdPartyDoctest                        )

TARGET_INCLUDE_DIRECTORIES ( ThirdPartyDoctest SYSTEM AFTER INTERFACE  ${DOCTEST_ROOT_PATH} )

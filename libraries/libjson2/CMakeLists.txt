ADD_LIBRARY ( LibraryJson2 json.cpp json.h )
ADD_LIBRARY ( Library::Json2 ALIAS LibraryJson2 )
TARGET_INCLUDE_DIRECTORIES ( LibraryJson2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
TARGET_LINK_LIBRARIES ( LibraryJson2 PRIVATE Utility::DisableWarnings )

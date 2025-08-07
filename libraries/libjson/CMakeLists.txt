ADD_LIBRARY ( LibraryJson json.cpp json.h )
ADD_LIBRARY ( Library::Json ALIAS LibraryJson )
TARGET_INCLUDE_DIRECTORIES ( LibraryJson PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
TARGET_LINK_LIBRARIES ( LibraryJson PRIVATE Utility::DisableWarnings )

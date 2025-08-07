ADD_LIBRARY ( LibraryXml xml.cpp xml.h )
ADD_LIBRARY ( Library::Xml ALIAS LibraryXml )
TARGET_INCLUDE_DIRECTORIES ( LibraryXml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
TARGET_LINK_LIBRARIES ( LibraryXml PRIVATE Utility::DisableWarnings )

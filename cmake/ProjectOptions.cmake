#####################################################################
# Project Options
INCLUDE_GUARD ( GLOBAL )
MESSAGE ( STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}" )

OPTION ( BUILD_SHARED_LIBS "Build libraries targets as shared libraries"    ON )
OPTION ( BUILD_TESTING     "Build test targets"                             ON )
OPTION ( BUILD_EXAMPLES    "Build example targets"                          ON )

OPTION ( PROJECT_DEV_BUILD                   "Development build with extra checks"  OFF )
OPTION ( PROJECT_SANITIZER_ADDRESS_ENABLED   "Enable address sanitizer"             OFF )
OPTION ( PROJECT_SANITIZER_UNDEFINED_ENABLED "Enable undefined sanitizer"           OFF )

# TODO(nikitafin): implement me
#option(PROJECT_SANITIZER_THREAD_ENABLED "Enable thread sanitizer" OFF)
#option(PROJECT_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
#option(PROJECT_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
#option(PROJECT_ENABLE_IPO "Enable IPO/LTO" OFF)
#option(PROJECT_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
#option(PROJECT_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
#option(PROJECT_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
#option(PROJECT_ENABLE_PCH "Enable precompiled headers" OFF)
#option(PROJECT_ENABLE_CACHE "Enable ccache" OFF)

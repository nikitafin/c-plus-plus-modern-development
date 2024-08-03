set(DEP_DIR ${CMAKE_SOURCE_DIR}/third_party/ut)

## CANNOT BE USED AS MODULE FOR NOW (clang18) MAYBE LATTER
#if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ut.cxxm)
#    add_custom_command(
#        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ut.cxxm
#        COMMAND ${CMAKE_COMMAND} -E copy ${DEP_DIR}/include/boost/ut.hpp ${CMAKE_CURRENT_SOURCE_DIR}/ut.cxxm
#    )
#endif()
#target_sources(third_party_ut PUBLIC
#        FILE_SET CXX_MODULES
#        FILES ut.cxxm
#)


add_library(third_party_ut INTERFACE)
target_include_directories(third_party_ut SYSTEM AFTER INTERFACE ${DEP_DIR}/include)
target_compile_definitions(third_party_ut INTERFACE BOOST_UT_DISABLE_MODULE)
add_library(third_party::ut ALIAS third_party_ut)

add_library(third_party_ut_main STATIC)
target_sources(third_party_ut_main PRIVATE "./src/main.cxx")
target_link_libraries(third_party_ut_main PUBLIC third_party::ut)
add_library(third_party::ut_main ALIAS third_party_ut_main)

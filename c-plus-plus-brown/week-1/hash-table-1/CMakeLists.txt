add_executable(hash_set_test hash_set_test.cxx)

target_sources(hash_set_test PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES hash_set.cxx
)
target_link_libraries(hash_set_test PUBLIC shared::gtest_all)

add_test(NAME hash_set_test COMMAND hash_set_test)
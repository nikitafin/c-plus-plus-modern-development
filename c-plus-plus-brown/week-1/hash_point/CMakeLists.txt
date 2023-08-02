add_executable(hash_point_test hash_point_test.cxx)

target_sources(hash_point_test PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES hash_point.cxx
)
target_link_libraries(hash_point_test PUBLIC shared::gtest_all)

add_test(NAME hash_point_test COMMAND hash_point_test)

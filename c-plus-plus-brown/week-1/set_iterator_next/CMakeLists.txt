add_executable(set_iterator_next_test set_iterator_next_test.cxx)

target_sources(set_iterator_next_test PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES set_iterator_next.cxx
)
target_link_libraries(set_iterator_next_test PUBLIC shared::gtest_all)

add_test(NAME set_iterator_next_test COMMAND set_iterator_next_test)
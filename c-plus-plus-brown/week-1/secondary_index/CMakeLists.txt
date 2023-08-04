add_executable(secondary_index_test secondary_index_test.cxx)

target_sources(secondary_index_test PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${cmake_current_source_dir}/
        FILES secondary_index.cxx
)
target_link_libraries(secondary_index_test PUBLIC shared::gtest_all)

add_test(NAME secondary_index_test.cxx COMMAND secondary_index_test.cxx)
add_executable(hash_person_test hash_person_test.cxx)

target_sources(hash_person_test PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES hash_person.cxx
)
target_link_libraries(hash_person_test PUBLIC shared::gtest_all)

add_test(NAME hash_person_test COMMAND hash_person_test)

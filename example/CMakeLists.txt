if (PROJECT_TEST_ENABLED)
    add_executable(some_body_test)
    target_sources(some_body_test
            PRIVATE "src/some_body_main_test.cxx" "src/some_body_suite_test.cxx"
    )
    target_sources(some_body_test
            PRIVATE FILE_SET CXX_MODULES FILES "src/some_body_module_test.cxxm"
    )
    target_link_libraries(some_body_test PRIVATE third_party::ut)

    add_test(NAME some_body_test COMMAND some_body_test)
endif ()

if (PROJECT_SANITIZER_ADDRESS)
    add_executable(asan_example)
    target_sources(asan_example PRIVATE "./src/asan_example.cxx")
    target_link_libraries(asan_example PRIVATE utility::project_warnings)
endif ()

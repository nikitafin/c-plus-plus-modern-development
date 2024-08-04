set(dependency_dir "${CMAKE_SOURCE_DIR}/third_party/googletest")

add_library(third_party_gtest)
add_library(third_party::gtest ALIAS third_party_gtest)

target_sources(third_party_gtest PRIVATE "${dependency_dir}/googletest/src/gtest-all.cc")
target_compile_definitions(third_party_gtest PUBLIC GTEST_HAS_POSIX_RE=0)
target_include_directories(third_party_gtest SYSTEM AFTER PUBLIC "${dependency_dir}/googletest/include")
target_include_directories(third_party_gtest SYSTEM AFTER PRIVATE "${dependency_dir}/googletest")
set_target_properties(third_party_gtest PROPERTIES VERSION "1.15.3")
set_target_properties(third_party_gtest PROPERTIES FOLDER "third_party")

add_library(third_party_gtest_main)
add_library(third_party::gtest_main ALIAS third_party_gtest_main)

target_sources(third_party_gtest_main PRIVATE "${dependency_dir}/googletest/src/gtest_main.cc")
set_target_properties(third_party_gtest_main PROPERTIES VERSION "1.15.3")
target_link_libraries(third_party_gtest_main PUBLIC third_party_gtest)


add_library(third_party_gtest_all INTERFACE)
add_library(third_party::gtest_all ALIAS third_party_gtest_all)
target_link_libraries(third_party_gtest_all INTERFACE third_party_gtest third_party_gtest_main)
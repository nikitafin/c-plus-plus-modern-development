project(week-5)
message("Project: " ${PROJECT_NAME} ". Module: " ${CMAKE_PROJECT_NAME} ".")

add_executable(simple_vector_assignment simple_vector.h simple_vector.cpp)
add_executable(simple_vector_move simple_vector_2.h simple_vector_2.cpp)
add_executable(tokenizer split_into_sentences.cpp)
add_executable(synchronized synchronized.cpp)
add_executable(prioriy_container priority_collection_2.cpp)
add_executable(concurrent_map concurrent_map.cpp)
add_executable(merge_sort_3 merge_sort_3.cpp)
add_executable(matrix_sum matrix_sum.cpp)
add_executable(josephus_permutation josephus_permutation.cpp)
add_executable(explore_key_words explore_key_words.cpp)

file(GLOB_RECURSE src "*.c*")
file(GLOB_RECURSE headers "*.h*")

add_executable(explore_key_words ${src} ${headers})

install(TARGETS explore_key_words DESTINATION bin)

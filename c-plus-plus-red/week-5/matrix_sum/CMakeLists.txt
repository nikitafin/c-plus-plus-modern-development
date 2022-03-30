file(GLOB_RECURSE src "*.c*")
file(GLOB_RECURSE headers "*.h*")

add_executable(matrix_sum ${src} ${headers})

install(TARGETS matrix_sum DESTINATION bin)

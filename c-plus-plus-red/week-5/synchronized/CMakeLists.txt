file(GLOB_RECURSE src "*.c*")
file(GLOB_RECURSE headers "*.h*")

add_executable(synchronized ${src} ${headers})

install(TARGETS synchronized DESTINATION bin)

ADD_EXECUTABLE ( 06_double_dispatch 
    collide.cpp
    game_object.h
    geo2d.cpp
    geo2d.h
)

TARGET_LINK_LIBRARIES ( 06_double_dispatch PRIVATE Utility::Warnings Library::TestRunner )
# NOTE ( nikitafin ) : does not using Werror due to various errors in lib code
SET_TARGET_PROPERTIES ( 06_double_dispatch PROPERTIES COMPILE_WARNING_AS_ERROR OFF       )

ADD_TEST ( NAME 06_double_dispatch COMMAND 06_double_dispatch )
ADD_EXECUTABLE        ( 02_lazy_value lazy_value.cpp )
TARGET_LINK_LIBRARIES ( 02_lazy_value 
    PRIVATE
        ThirdParty::Doctest
        Utility::Warnings
)
TARGET_COMPILE_DEFINITIONS ( 02_lazy_value PRIVATE WITH_TESTS                       )
SET_TARGET_PROPERTIES      ( 02_lazy_value PROPERTIES COMPILE_WARNING_AS_ERROR ON   )
ADD_TEST                   ( NAME 02_lazy_value COMMAND 02_lazy_value               )
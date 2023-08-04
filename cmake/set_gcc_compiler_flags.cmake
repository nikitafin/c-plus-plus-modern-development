macro(set_gcc_compiler_flags)
    add_compile_options(
            -Wall           # Enables all warnings
            -Wextra         # Enables extra warnings not enabled by -Wall
            -Werror         # Treats warnings as errors
            -pedantic       # Strict ISO:C, ISO:C++
            -pedantic-error # Treats pedantic warnings as errors
            -Waddress       # Suspicious uses of address expressions
            -Wbool-compare
            -Wbool-operation
            -Wcatch-value
            -Wchar-subscripts
            -Wint-in-bool-context
            -Winit-self
            -Wlogical-not-parentheses
            -Wmaybe-uninitialized
            -Wmisleading-indentation
            -Wmissing-attributes
            -Wmultistatement-macros
            -Wpessimizing-move
            -Wreorder
            -Wreturn-type
            -Wsequence-point
            -Wsign-compare
            -Wsizeof-pointer-div
            -Wstrict-aliasing
            -Wtautological-compare
            -Wuninitialized
            -Wunused-function
            -Wunused-variable
            -Wempty-body
            -Wmissing-field-initializers
            -Wredundant-move
            -Wtype-limits
            -Wshift-negative-value
            -Wunused-parameter
            -Wunused-but-set-parameter
            -Wctor-dtor-privacy
            -Wnon-virtual-dtor
            -Woverloaded-virtual
            -Wsign-promo
            -Wduplicated-branches
            -Wduplicated-cond
            -Wfloat-equal
            -Wshadow=compatible-local
            -Wcast-qual
            -Wconversion
            -Wextra-semi
            -Wsign-conversion
            -Wlogical-op
    )

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(
                -O0 # Disable optimization to make debugging easier
                -g  # Generates debugging information that can be used by a debugger
        )
    elseif (CMAKE_BUILD_TYPE MATCHES Release)
        add_compile_options(
                -O3 # Enable maximum optimization
        )
    elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
        add_compile_options(
                -O2 # Enable optimization
                -g  # Generates debugging information that can be used by a debugger
                -Warray-bounds=1
        )
    else ()
        message(FATAL_ERROR "Unsupported BUILD_TYPE for gcc-config")
    endif ()
endmacro()

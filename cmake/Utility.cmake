include_guard(GLOBAL)
message(STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}")

##
function(option_check_name option option_name)
    #    string(REGEX REPLACE "[-]" " " new_option_str ${option})
    #    string(STRIP ${new_option_str} new_option_str)
    #    string(REGEX REPLACE "[ ]" "_" new_option_str ${new_option_str})
    #    string(REGEX REPLACE "[=]" "_" new_option_str ${new_option_str})
    #    string(TOUPPER ${new_option_str} ${option_name})
    #    string(SUBSTRING ${option} 1 -1 ${option_name})
    set(${option_name} ${option})

    return(PROPAGATE ${option_name})
endfunction()

##
function(append_compile_option options new_option)
    option_check_name(${new_option} new_option_str)
    set(new_option_str "COMPILE:${new_option_str}")

    check_cxx_compiler_flag(${new_option} ${new_option_str})

    if (${${new_option_str}})
        if (${new_option} IN_LIST ${options})
            # TODO(nikitafin): handle somehow
        else ()
            list(APPEND ${options} ${new_option})
        endif ()
    endif ()
    return(PROPAGATE ${options})
endfunction()

##
function(append_link_option options new_option)
    option_check_name(${new_option} new_option_str)
    set(new_option_str "LINK:${new_option_str}")

    check_linker_flag(CXX ${new_option} ${new_option_str})

    if (${${new_option_str}})
        if (${new_option} IN_LIST ${options})
            # TODO(nikitafin): handle somehow
        else ()
            list(APPEND ${options} ${new_option})
        endif ()
    endif ()
    return(PROPAGATE ${options})
endfunction()

##
function(append_warning options new_option)
    option_check_name(${new_option} new_option_str)
    set(new_option_str "WARNING:${new_option_str}")

    check_cxx_compiler_flag(${new_option} ${new_option_str})

    if (${${new_option_str}})
        if (${new_option} IN_LIST ${options})
            # TODO(nikitafin): handle somehow
        else ()
            list(APPEND ${options} ${new_option})
        endif ()
    endif ()
    return(PROPAGATE ${options})
endfunction()

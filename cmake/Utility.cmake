#####################################################################
# Utility
#####################################################################
INCLUDE_GUARD ( GLOBAL )
MESSAGE ( STATUS "Load module: ${CMAKE_CURRENT_LIST_FILE}" )

#####################################################################
# UNIFY_LIST - Unify list
FUNCTION ( UNIFY_LIST OPTION_LIST )
    SEPARATE_ARGUMENTS ( ${OPTION_LIST} )

    LIST( REMOVE_DUPLICATES ${OPTION_LIST}  )
    list( REMOVE_ITEM ${OPTION_LIST} ""     )
    list( SORT ${OPTION_LIST}               )

    SET(${OPTION_LIST} ${${OPTION_LIST}} PARENT_SCOPE)
ENDFUNCTION ( )

#####################################################################
# APPEND_UNIQUE - append unique value in list
FUNCTION ( APPEND_UNIQUE LIST_NAME VALUE )
    IF ( NOT ${LIST_NAME} )
        SET ( ${LIST_NAME} ${VALUE} PARENT_SCOPE )
    ELSE ( )
        LIST (FIND ${LIST_NAME} ${VALUE} INDEX )
        IF ( INDEX EQUAL -1 )
            LIST ( APPEND ${LIST_NAME} ${VALUE} )
            SET ( ${LIST_NAME} ${${LIST_NAME}} PARENT_SCOPE )
        ENDIF ( )
    ENDIF ( )
ENDFUNCTION ( )

#####################################################################
# APPEND_WARNING - append warning new_option to options list
FUNCTION ( APPEND_WARNING OPTIONS NEW_OPTION )
    SET ( NEW_OPTION_STR "WARNING:${NEW_OPTION}")

    CHECK_CXX_COMPILER_FLAG ( ${NEW_OPTION} ${NEW_OPTION_STR} )

    IF ( ${${NEW_OPTION_STR}} )
        IF (NOT ${NEW_OPTION} IN_LIST ${OPTIONS} )
            LIST ( APPEND ${OPTIONS} ${NEW_OPTION} )
        ENDIF ( )
    ENDIF ( )
    SET ( ${OPTIONS} ${${OPTIONS}} PARENT_SCOPE )
ENDFUNCTION ( )

#####################################################################
# ADD_THIRD_PARTY - add self builded third party
FUNCTION ( ADD_THIRD_PARTY CMAKE_FOLDER)
    IF ( ARGN )
        SET ( BASE_FOLDERS ${ARGN} )
    ELSE ( )
        SET ( BASE_FOLDERS ${CMAKE_FOLDER} )
    ENDIF ( )

    FOREACH ( BASE_FOLDER ${BASE_FOLDERS} )
        # some typos in the code
        IF ( NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${BASE_FOLDER}" )
            MESSAGE ( FATAL_ERROR "No such base folder '${BASE_FOLDER}' (for '${CMAKE_FOLDER}' cmake folder). Typo in the base folder name?")
        ENDIF ( )

        FILE ( GLOB THIRD_PARTY_FILES "${base_folder}/*" )

        IF ( NOT THIRD_PARTY_FILES )
            MESSAGE ( STATUS "submodule ${BASE_FOLDER} is missing or empty. to fix try run:" )
            MESSAGE ( STATUS "    git submodule update --init" )
            RETURN ( )
        ENDIF ( )
    ENDFOREACH ( )

    MESSAGE ( STATUS "Adding third_party module ${BASE_FOLDERS} (configuring with ${CMAKE_FOLDER})")
    ADD_SUBDIRECTORY ( ${CMAKE_FOLDER} )
ENDFUNCTION ( )

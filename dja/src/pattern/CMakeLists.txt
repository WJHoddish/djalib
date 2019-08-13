aux_source_directory( . DIR_SRCS_DJA_APPLICATION )
add_library( dja_application ${DIR_SRCS_DJA_APPLICATION} )
target_link_libraries( dja_application dja_element )
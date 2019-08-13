aux_source_directory( . DIR_SRCS_DJA_TOOL )
add_library( dja_tool ${DIR_SRCS_DJA_TOOL} )
target_link_libraries( dja_tool dja_math dja_core )
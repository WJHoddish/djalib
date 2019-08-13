aux_source_directory( . DIR_SRCS_DJA_FRAME )
add_library( djalib ${DIR_SRCS_DJA_FRAME} )
target_link_libraries( djalib dja_tool )
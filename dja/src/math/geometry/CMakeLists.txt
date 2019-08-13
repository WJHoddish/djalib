aux_source_directory( . DIR_SRCS_DJA_MATH_GEOMETRY )
add_library( dja_math ${DIR_SRCS_DJA_MATH_GEOMETRY} )
target_link_libraries( dja_math dja_math_algebra )
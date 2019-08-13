add_compile_options(-fPIC)

# process such cmake files in sub-directories
add_subdirectory( ./dja/core )
add_subdirectory( ./dja/math/algebra )
add_subdirectory( ./dja/math/geometry )
add_subdirectory( ./dja/tool )

# djalib entrance
add_subdirectory( ./dja/frame )
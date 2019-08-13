# Djalib: A C++ library established during my learning process

## Purpose
The main purpose of using this library is to introduce an IoC framework (cpp implementation) into your project.
However, there are also plenty of typical cpp components include general data structures and tools for the specific use.
Please be aware of that the folder: "frame" is the interface of this library, where includes the cmake file.
As a default, the name used in the link_library is djalib.

## Usage
include_directories( ${path}/dja/include )

add_subdirectory( ${path}/dja/src )
target_link_libraries( ${your_project_name} djalib )

## Components

## Features
- use Google cpp style
- support Doxygen
- support separation compilation

## FAQs
If you meet any suspected bug, please contact me through <wjhgeneral@outlook.com>.
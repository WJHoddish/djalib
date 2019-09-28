# Djalib: A C++ library organized by Jiaheng

## Purpose
The main purpose of using this library is to introduce an IoC framework into your cpp project.
There are also plenty of typical cpp components include data structures and tools for specific use.
Please be aware of that the folder: "frame" is regarded as the entrance of this library, where includes the cmake file.
As a default, the name used in the "target_link_libraries" is "djalib".

## Usage
include_directories( ${path}/dja/include )

add_subdirectory( ${path}/dja/src )

target_link_libraries( ${your_project_name} djalib )

## Components

## Features
- Google cpp style
- support Doxygen

## FAQs
If you met any suspected bug, please contact me through <wjhgeneral@outlook.com>.

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project( VLG )
include_directories( /usr/local/include/igraph/
                     src/
                     )


link_directories( /usr/local/lib/ )
add_executable( vlg
    src/main.cpp
    src/BoudingEccentricities.cpp
    )


target_link_libraries( vlg LINK_PUBLIC igraph )
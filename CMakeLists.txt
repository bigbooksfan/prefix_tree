cmake_minimum_required(VERSION 3.14)
project(Prefix_tree_project)

set(CMAKE_CXX_STANDARD 20)

set(FILES
    src/source.cpp
    src/prefix_tree.h
    src/prefix_tree.cpp
)

add_executable(Tree ${FILES})

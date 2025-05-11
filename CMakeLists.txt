cmake_minimum_required(VERSION 3.5)

project(07.templates)

add_executable(metafunctions metafunctions.h
        print_ip.h)
set_target_properties(metafunctions PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(sfinae sfinae.cpp)
set_target_properties(sfinae PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(sfinae_sort sfinae_sort.cpp)
set_target_properties(sfinae_sort PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
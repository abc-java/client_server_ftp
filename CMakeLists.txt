cmake_minimum_required(VERSION 3.12)
project(ClientServer)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(server)
add_subdirectory(client)










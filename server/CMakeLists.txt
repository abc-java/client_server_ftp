cmake_minimum_required(VERSION 3.12)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp)

target_link_libraries(Server ${Boost_LIBRARIES})

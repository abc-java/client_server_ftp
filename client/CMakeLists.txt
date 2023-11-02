cmake_minimum_required(VERSION 3.12)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp)

target_link_libraries(Client ${Boost_LIBRARIES})

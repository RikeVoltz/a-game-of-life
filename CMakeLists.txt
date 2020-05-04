cmake_minimum_required(VERSION 3.15)
project(life_game)

set(CMAKE_CXX_STANDARD 17)

include(conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(life_game main.cpp)

target_link_libraries(life_game CONAN_PKG::sfml)

install(TARGETS life_game DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -lflint -lntl -lmpfr -lgmp -fopenmp")

project(Weirds)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tree
  main.cpp
)

#target_link_libraries(tree ntl m gmp)

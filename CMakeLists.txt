cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -lflint -lntl -lmpfr -lgmp -fopenmp")

project(Weirds)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(run
  main.cpp
  listfix.cpp
  opnalg.cpp
  tree.cpp
  tools.cpp
  expalg.cpp
)

target_link_libraries(run ntl m gmp)

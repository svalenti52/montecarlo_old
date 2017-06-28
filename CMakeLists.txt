cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MonteCarloSim.cpp MonteCarloSim.h Distribution.cpp Distribution.h Differences.cpp Differences.h)
add_library(montecarlo ${SOURCE_FILES})

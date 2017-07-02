cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MonteCarloSim.h Distribution.h Differences.h MonteCarloSim.cpp Histogram.h)
add_library(montecarlo ${SOURCE_FILES})

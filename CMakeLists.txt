cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MonteCarloSim.cpp MonteCarloSim.h MCS_Real.cpp MCS_Real.h MCS_Integer.cpp MCS_Integer.h)
add_library(montecarlo ${SOURCE_FILES})
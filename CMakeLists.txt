cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MonteCarloSim.cpp MonteCarloSim.h MCS_Real.cpp MCS_Real.h MCS_Integer.cpp MCS_Integer.h MCS_Real_and_Integer.cpp MCS_Real_and_Integer.h Random_Event.cpp Random_Event.h Deque_of_Difference.cpp Deque_of_Difference.h)
add_library(montecarlo ${SOURCE_FILES})
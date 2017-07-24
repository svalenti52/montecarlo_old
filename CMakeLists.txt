cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MonteCarloSim.cpp MonteCarloSim.h Distribution.h Differences.h Histogram.h StateMatrix.h State.h Chronology.h List_Without_Repetition.h)

add_library(Monte_Carlo ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES MonteCarloSim.cpp MonteCarloSim.h Distribution.h Differences.h Histogram.h StateMatrix.h State.h Chronology.h List_Without_Repetition.h MonteCarloSim_alpha.h Distribution_alpha.h Distribution_beta.h MonteCarloSim_beta.h Combinatorics.h)

add_library(Monte_Carlo ${SOURCE_FILES})
#add_executable(Monte_Carlo MonteCarloSim.cpp)

cmake_minimum_required(VERSION 3.7)
project(montecarlo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MonteCarloSim.h Distribution.h Differences.h MonteCarloSim.cpp Histogram.h StateMatrix.h State.h Chronology.h List_Without_Repetition.h)
add_library(montecarlo MonteCarloSim.h Distribution.h Differences.h MonteCarloSim.cpp Histogram.h StateMatrix.h State.h Chronology.h List_Without_Repetition.h)

#target_compile_definitions(montecarlo INTERFACE $(SOURCE_FILES))
#target_include_directories(montecarlo INTERFACE /usr/local/include/val/montecarlo)
#target_link_libraries(montecarlo LINK_INTERFACE_LIBRARIES /usr/local/include/val/montecarlo)

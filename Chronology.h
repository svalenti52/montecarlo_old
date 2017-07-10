/**
 * \file Chronology.h
 * \date 9-Jul-2017
 *
 * \brief Class Chronology with time-based facilities for the
 * Monte Carlo Simulation (possibly more general).
 * 
 * \details Added the StopWatch class which allows the timing
 * of programs in milliseconds. The StopWatch is used by several
 * of the programs from the Digital Dice, Duelling Idiots, and
 * Alive 10 Years suites.
 */

#ifndef MONTECARLO_CHRONOLOGY_H
#define MONTECARLO_CHRONOLOGY_H

#include <chrono>
#include <iostream>

class Chronology {

};

class StopWatch {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point finish;
    using duration_type = decltype(start - finish);
    duration_type start_to_finish;
public:

    StopWatch() : start(std::chrono::system_clock::now()) {}
    void stop() {
        finish = std::chrono::system_clock::now();
        start_to_finish = finish - start;
        std::cout << "elapsed time = " <<
                  std::chrono::duration_cast<std::chrono::milliseconds>(start_to_finish).count() <<
                  " milliseconds\n";
    }
};

#endif //MONTECARLO_CHRONOLOGY_H

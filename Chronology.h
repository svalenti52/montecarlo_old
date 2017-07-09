//
// Created by svalenti on 7/9/2017.
//

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

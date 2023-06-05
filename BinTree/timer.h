#pragma once

#include "using_head.h"

class Timer {
public:
    Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

    void reset() {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    long long elapsed() const {
        std::chrono::nanoseconds elapsed_time = std::chrono::high_resolution_clock::now() - start_time_;
        return elapsed_time.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};
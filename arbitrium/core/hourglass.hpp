// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef HOURGLASS_HPP
#define HOURGLASS_HPP

#include <chrono>

using namespace std::chrono; // NOLINT

class Hourglass {
  private:
    milliseconds end_time;

    milliseconds current_time() const {
        return duration_cast<milliseconds>(
            system_clock::now().time_since_epoch());
    }

  public:
    bool out_of_time() const { return current_time() > end_time; }
    void set_time(const unsigned clock) {
        end_time = current_time() + milliseconds(clock);
    }
};

#endif // HOURGLASS_HPP

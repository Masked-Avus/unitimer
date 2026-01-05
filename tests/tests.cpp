#include "../src/unitimer.hpp"
#include <iostream>

using namespace unitimer;

static void run(int iterations) {
    std::cout << "Iterations: " << iterations << '\n';

    {
        Timer timer { [](const Timer& timer) {
            std::cout << "    Seconds:      " << timer.get_duration(Measurement::Seconds) << '\n';
            std::cout << "    Milliseconds: " << timer.get_duration(Measurement::Milliseconds) << '\n';
            std::cout << "    Microseconds: " << timer.get_duration(Measurement::Microseconds) << '\n';
            std::cout << "    Nanoseconds:  " << timer.get_duration(Measurement::Nanoseconds) << '\n';
        } };

        timer.reset();

        for (int i {}; i < 100000000; ++i) {}
   }
}

int main() {
    run(1000);
    run(1000000);
    run(1000000000);
    return 0;
}

# UniTimer

## Description

UniTimer is a dead-simple implementation of a `Timer` class in C++. It consists of a single header, so just `#include "unitimer.hpp"` in your project, and you're good to go!

## Features

The central feature of UniTimer is a `Timer` class. It can be run as-is just to get the amount of time that has transpired between two points, or it can be given a callback function that will be run once the timer stops. A `Timer::Callback`, if it exists, will be run once the `stop` function is called on it, either manually or via the `Timer`'s destructor when it exits its resident scope.

## Requirements
### Source

UniTimer requires a minimum of C++11.

### Unit Tests

To create and run this project's unit tests, you will need to have [Premake](https://premake.github.io/) installed. If you do, use it to run the `premake5.lua` file with your toolset of choice and run the generated build files. Below is an example using Makefiles.

```
premake5 gmake
```

## Example

```cpp
#include "unitimer.hpp"
#include <iostream>

using namespace unitimer;

int main() {
    std::cout << "\nStart\n\n";

    {
        Timer timer { [](const Timer& timer) {
            std::cout << "Seconds:      " << timer.get_duration(Measurement::Seconds) << '\n';
            std::cout << "Milliseconds: " << timer.get_duration(Measurement::Milliseconds) << '\n';
            std::cout << "Microseconds: " << timer.get_duration(Measurement::Microseconds) << '\n';
            std::cout << "Nanoseconds:  " << timer.get_duration(Measurement::Nanoseconds) << '\n';
        } };

        for (int i {}; i < 100000000; ++i) {}
    }

    std::cout << "\nEnd\n";

    return 0;
}

```

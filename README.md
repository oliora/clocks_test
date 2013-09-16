# Clocks Test

Tests for behavior of STL and Boost <chrono>'s system/steady clocks and related stuff like sleeps and waits.

## Tests included

### chrono_test

Tests `chrono::system_clock` and `chrono::steady_clock` of STL and Boost.

To test:
* Execute `chrono_test`.
* Change system time for several minutes back or forward.
* Press Enter to finish `chrono_test` execution.

Enjoy the results:

                  std system_clock    std steady_clock  boost system_clock  boost steady_clock
    t0, ticks    13790857389794140   13790857389794140   13790857389794140    2016885602890439
    t1, ticks    13790856336881722   13790856336881722   13790856336881722    2016905101856938
    t1 - t0, s            -105.291            -105.291            -105.291              19.499

Where *t0* is the clock's value at program start and *t1* the same at the program's finish.


### sleep_test executable

### wait_test executable


## Prerequisities

* MS Visual Studio 2012 or any other compiler supporting C++11 ([clang](http://clang.llvm.org/) + [libc++](http://libcxx.llvm.org/) is the best choice, btw ;).
* [CMake](http://www.cmake.org/) version 2.8 or newer.
* [Boost](http://www.boost.org) version 1.54 or above. Most probably the earlier versions are also OK. The following Boost libraries are needed: *system*, *chrono*, *thread*.


##How To Build

### *nix / OS X:

    mkdir workspace
    cd workspace
    cmake ..
    make

### Windows:

    mkdir workspace
    cd workspace
    cmake .. -G "Visual Studio 11" -DBOOST_INCLUDEDIR=<path_to_boost_headers> -DBOOST_LIBRARYDIR=<path_to_boost_libs>

Then either build it by

    cmake --build . --config Release

or open generated solution file.

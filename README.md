# Clocks Test

Tests for behavior of STL and Boost <chrono>'s system/steady clocks and related stuff like sleeps and waits.

## Tests included

### clocks_test

Tests `chrono::system_clock` and `chrono::steady_clock` of STL and Boost.

To test:
* Run `clocks_test`.
* Change system time for several minutes back or forward when prompted.
* Press Enter to finish test execution.

Enjoy the results:

                                        t0, ticks           t1, ticks          t1 - t0, s
    std          system_clock    1379539687034393    1379539658598580            -28.4358
    std          steady_clock      11785328391541      11819486797225             34.1584
    boost        system_clock 1379539687034400000 1379539658598582000            -28.4358
    boost        steady_clock      11785328412464      11819486798474             34.1584

Where *t0* is the clock's value at program start and *t1* the one at the program's finish.


### sleep_test executable

### wait_test executable


## Prerequisities

* MS Visual Studio 2012 or any other compiler supporting C++11 ([clang](http://clang.llvm.org/) + [libc++](http://libcxx.llvm.org/) is the best choice, btw ;).
* [CMake](http://www.cmake.org/) version 2.8.10 or newer. Most probably the earlier versions are also OK but you have to change version requirement in *CMakeLists.txt* file.
* [Boost](http://www.boost.org) version 1.54 or above. Most probably the earlier versions are also OK, but you have to change version requirement in *CMakeLists.txt* file. The following Boost libraries are need to be compiled: *system*, *chrono*, *thread*.


##How To Build

### *nix / OS X:

    mkdir workspace
    cd workspace
    cmake ..
    make

### Windows (Visual Studio 2012):

    mkdir workspace
    cd workspace
    cmake .. -G "Visual Studio 11" -DBOOST_INCLUDEDIR=<path_to_boost_headers> -DBOOST_LIBRARYDIR=<path_to_boost_libs>

Then either build it by

    cmake --build . --config Release

or open generated solution file.

Please read [CMake documentation](http://www.cmake.org/cmake/help/documentation.html) to get more options and stronger control over build.

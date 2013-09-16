# Clocks Test

Tests for behavior of &lt;chrono>'s system/steady clocks and related stuff like sleeps and waits.


## Prerequisities

* MS Visual Studio 2012 or any other compiler supporting C++11 ([clang](http://clang.llvm.org/) + [libc++](http://libcxx.llvm.org/) is the best choice, btw ;).
* [CMake](http://www.cmake.org/) version 2.8 or newer.
* [Boost](http://www.boost.org) version 1.54 or above. Most probably the earlier versions are also OK. The following Boost libraries are needed: *system*, *chrono*, *thread*.


##How To Build

### *nix / OSX:

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

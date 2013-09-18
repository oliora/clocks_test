# Clocks Test

Set of tools which allow to test how STL and Boost performs on your platform in case of system time changed.
Currently contains tests for `chrono::steady_clock`, `chrono::system_clock`, sleep methods of `this_thread` and wait methods of `condition_variable` and `future`.

And yes, **this project is released to public domain.**


## Prerequisities

* MS Visual Studio 2012 or any other compiler supporting C++11.
  [Clang](http://clang.llvm.org/) in conjunction with [libc++](http://libcxx.llvm.org/) (both included in Xcode now) is the best choice btw ;)
* [CMake](http://www.cmake.org/) version 2.8.10 or newer.
* [Boost](http://www.boost.org) version 1.54 or above. The following Boost libraries are need to be compiled: *system*, *chrono*, *thread*.

Most probably the earlier versions of CMake and Boost are also OK. Note that before using them you have to change version requirements in *CMakeLists.txt* file.


##How To Build

### *nix / OS X:

    mkdir workspace
    cd workspace
    cmake <project_dir>
    make

### Windows (Visual Studio 2012):

    mkdir workspace
    cd workspace
    cmake <project_dir> -G "Visual Studio 11" -DBOOST_INCLUDEDIR=<path_to_boost_headers> -DBOOST_LIBRARYDIR=<path_to_boost_libs>

Then either build it by

    cmake --build . --config Release

or open generated solution file.

Please read [CMake documentation](http://www.cmake.org/cmake/help/documentation.html) to get more options and take complete control over build.


## Tests included

### clocks_test

Tests `chrono::system_clock` and `chrono::steady_clock`.

To test:
* Run `./clocks_test`.
* When prompted, change system time for one minute back or forward or back and forward or whatever you want to test.
* Press Enter to finish test execution.

Output format:

                                        t0, ticks           t1, ticks          t1 - t0, s
    std          system_clock    1379539687034393    1379539658598580            -28.4358
    std          steady_clock      11785328391541      11819486797225             34.1584
    boost        system_clock 1379539687034400000 1379539658598582000            -28.4358
    boost        steady_clock      11785328412464      11819486798474             34.1584

Where *t0* is the clock's value at program start and *t1* the one at the program finish.


### sleep_test

Tests `this_thread` methods:
* `sleep_for(duration)`
* `sleep_until(steady_clock::time_point)`
* `sleep_until(system_clock::time_point)`

To test:
* Prepare to be ready to change system clock in several seconds (open corresponding page of System Preferences or similar).
* Run `./sleep_test`.
* Change system time for one minute back or forward or back and forward or whatever you want to test. But do it quickly!
* Wait until test execution finished.

Output format:

    std         sleep_until_steady  timings, s:    15.0011 (std)   15.0011 (boost)
    std                  sleep_for  timings, s:    15.0011 (std)   15.0011 (boost)
    boost       sleep_until_steady  timings, s:    15.0012 (std)   15.0012 (boost)
    boost                sleep_for  timings, s:    15.0012 (std)   15.0012 (boost)
    std         sleep_until_system  timings, s:    77.1577 (std)   77.1577 (boost)
    boost       sleep_until_system  timings, s:    77.1578 (std)   77.1578 (boost)

Where timings are taken from STL and Boost `steady_clock`.


### wait_test

Tests `condition_variable` and `future` methods:
* `wait_for(duration)`
* `wait_until(steady_clock::time_point)`
* `wait_until(system_clock::time_point)`

To test:
* Prepare to be ready to change system clock in several seconds (open corresponding page of System Preferences or similar).
* Run `./wait_test`.
* Change system time for one minute back or forward or back and forward or whatever you want to test. But do it quickly!
* Wait until test execution finished.

Output format:

    std future        wait_until_steady  timings, s:    15.0005 (std)   15.0005 (boost)     timeout
    std cv                     wait_for  timings, s:    15.0005 (std)   15.0006 (boost)     timeout
    boost cv                   wait_for  timings, s:    15.0006 (std)   15.0007 (boost)     timeout
    std cv            wait_until_steady  timings, s:    15.0006 (std)   15.0007 (boost)     timeout
    std future                 wait_for  timings, s:    15.0005 (std)   15.0006 (boost)     timeout
    boost future               wait_for  timings, s:    15.0006 (std)   15.0006 (boost)     timeout
    std cv            wait_until_system  timings, s:    15.0007 (std)   15.0009 (boost)  no_timeout
    boost cv          wait_until_system  timings, s:    15.0007 (std)   15.0009 (boost)     timeout
    boost future      wait_until_steady  timings, s:    15.0008 (std)   15.0008 (boost)     timeout
    boost future      wait_until_system  timings, s:    15.0008 (std)   15.0008 (boost)     timeout
    boost cv          wait_until_steady  timings, s:    15.0008 (std)   15.0009 (boost)     timeout
    std future        wait_until_system  timings, s:    77.3298 (std)   77.3298 (boost)     timeout

Where timings are taken from STL and Boost `steady_clock`.
Last column is a result of wait. It either `cv_status` or `future_status` type.

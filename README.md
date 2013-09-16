clocks_test
===========

Tests for behavior of &lt;chrono>'s system/steady clocks and related stuff like sleeps and waits.

Prerequisities
--------------

MS Visual Studio 2012 or any other compiler supporting C++11 (Clang is the best of thems, btw).
Boost 1.54. The following libraries should be compiled: system, chrono, thread.

How To Build
------------

*nix / OSX:
# mkdir workspace
# cd workspace
# cmake ..
# cmake --build .

Windows:
# mkdir workspace
# cd workspace
# cmake [-G "Visual Studio 11"] ..
# cmake --build . --config release


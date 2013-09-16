# (c) 2013 Andrey Upadyshev aka oliora <oliora@gmail.com>.
# File released to public domain.
cmake_minimum_required(VERSION 2.8)

project(clocks_test)

if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    
    add_definitions(-DBOOST_ALL_NO_LIB) # Turn off Boost's auto-linking
    set(Boost_USE_STATIC_LIBS ON) # Use static libs
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif()

# Find Boost
find_package(Boost 1.54 REQUIRED COMPONENTS chrono thread system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(clocks_test "clocks_test.cpp")
target_link_libraries(clocks_test ${Boost_LIBRARIES})

add_executable(sleep_test "sleep_test.cpp")
target_link_libraries(sleep_test ${Boost_LIBRARIES})

add_executable(wait_test "wait_test.cpp")
target_link_libraries(wait_test ${Boost_LIBRARIES})

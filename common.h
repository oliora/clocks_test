// (c) 2013 Andrey Upadyshev aka oliora <oliora@gmail.com>.
// File released to public domain.
#pragma once

#ifdef WIN32
#define WINVER 0x0600
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#endif

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <boost/chrono/chrono.hpp>
#include <mutex>


namespace chrono_test
{
template<class _Rep, class _Period>
double seconds(const std::chrono::duration<_Rep, _Period>& d)
{
    return std::chrono::nanoseconds(d).count() / 1E9;
}

template<class _Rep, class _Period>
double seconds(const boost::chrono::duration<_Rep, _Period>& d)
{
    return boost::chrono::nanoseconds(d).count() / 1E9;
}

class synced_cout
{
public:
    template<typename T>
    synced_cout& operator<< (const T& t)
    {
        m_buf << t;
        return *this;
    }

    ~synced_cout()
    {
        static std::mutex m;
    
        std::lock_guard<std::mutex> lock(m);

        std::cout << m_buf.str();
    }

private:
    std::stringstream m_buf;
};
}

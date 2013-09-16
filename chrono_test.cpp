// (c) 2013 Andrey Upadyshev aka oliora <oliora@gmail.com>.
// File released to public domain.
#include "common.h"


namespace std { namespace chrono {
    template<class _Elem, class _Traits, class _Clock, class _Duration>
    std::basic_ostream<_Elem, _Traits> & operator<< (std::basic_ostream<_Elem, _Traits>& os, const time_point<_Clock, _Duration>& tp)
    {
        os << tp.time_since_epoch().count();
        return os;
    }
}}

namespace boost { namespace chrono {
    template<class _Elem, class _Traits, class _Clock, class _Duration>
    std::basic_ostream<_Elem, _Traits> & operator<< (std::basic_ostream<_Elem, _Traits>& os, const time_point<_Clock, _Duration>& tp)
    {
        os << tp.time_since_epoch().count();
        return os;
    }
}}


int main(int argc, char *argv[])
{
    using namespace chrono_test;

    const auto std_system_time_0 = std::chrono::system_clock::now();
    const auto std_steady_time_0 = std::chrono::steady_clock::now();
    const auto boost_system_time_0 = boost::chrono::system_clock::now();
    const auto boost_steady_time_0 = boost::chrono::steady_clock::now();

    std::cout << "Change system clock and press Enter..." << std::endl;
    getchar();

    const auto std_system_time_1 = std::chrono::system_clock::now();
    const auto std_steady_time_1 = std::chrono::steady_clock::now();
    const auto boost_system_time_1 = boost::chrono::system_clock::now();
    const auto boost_steady_time_1 = boost::chrono::steady_clock::now();

    std::cout
        << std::setw(10) << "" << std::right
            << std::setw(20) << "std system time"
            << std::setw(20) << "std steady time"
            << std::setw(20) << "boost system time"
            << std::setw(20) << "boost steady time"
            << std::endl
        << std::setw(10) << std::left << "t0, ticks" << std::right
            << std::setw(20) << std_system_time_0
            << std::setw(20) << std_steady_time_0
            << std::setw(20) << boost_system_time_0
            << std::setw(20) << boost_steady_time_0
            << std::endl
        << std::setw(10) << std::left << "t1, ticks" << std::right
            << std::setw(20) << std_system_time_1
            << std::setw(20) << std_steady_time_1 
            << std::setw(20) << boost_system_time_1
            << std::setw(20) << boost_steady_time_1
            << std::endl
        << std::setw(10) << std::left << "t1 - t0, s" << std::right
            << std::setw(20) << seconds(std_system_time_1 - std_system_time_0)
            << std::setw(20) << seconds(std_steady_time_1 - std_steady_time_0)
            << std::setw(20) << seconds(boost_system_time_1 - boost_system_time_0)
            << std::setw(20) << seconds(boost_steady_time_1 - boost_steady_time_0)
            << std::endl;

    return 0;
}

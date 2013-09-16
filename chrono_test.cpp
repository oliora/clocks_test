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

using namespace chrono_test;

namespace
{
    template<typename T>
    void print_result(const char *group, const char *name, const T& t0, const T& t1)
    {
        std::cout
            << std::left << std::setw(10) << group << std::right
            << std::setw(15) << name
            << std::setw(20) << t0
            << std::setw(20) << t1
            << std::setw(20) << seconds(t1-t0)
            << std::endl;
    }
}


int main(int argc, char *argv[])
{
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
        << std::setw(25) << ""
        << std::setw(20) << "t0, ticks"
        << std::setw(20) << "t1, ticks"
        << std::setw(20) << "t1 - t0, s"
        << std::endl;

    print_result("std", "system_clock", std_system_time_0, std_system_time_1);
    print_result("std", "steady_clock", std_steady_time_0, std_steady_time_1);
    print_result("boost", "system_clock", boost_system_time_0, boost_system_time_1);
    print_result("boost", "steady_clock", boost_steady_time_0, boost_steady_time_1);

    return 0;
}

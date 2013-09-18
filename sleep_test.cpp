// (c) 2013 Andrey Upadyshev aka oliora <oliora@gmail.com>.
// File released to public domain.
#include "common.h"
#include <thread>
#include <boost/thread.hpp>
#include <vector>

using namespace chrono_test;

namespace
{
    template<typename D1, typename D2>
    void print_result(const char *group, const char *name, const D1& duration1, const D2& duration2)
    {
        synced_cout()
            << std::left << std::setw(10) << group << std::right
            << std::setw(20) << name << "  timings, s: "
            << std::setw(10) << seconds(duration1) << " (std)"
            << std::setw(10) << seconds(duration2) << " (boost)\n";
    }
}


int main(int argc, char *argv[])
{
    typedef void (*func)();
    
    enum { SLEEP = 15 }; // seconds

    func functions[] = {
        // std
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::this_thread::sleep_for(std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();

            print_result("std", "sleep_for", std_t1 - std_t0, boost_t1 - boost_t0);
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();

            print_result("std", "sleep_until_steady", std_t1 - std_t0, boost_t1 - boost_t0);
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();

            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(SLEEP));

            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            print_result("std", "sleep_until_system", std_t1 - std_t0, boost_t1 - boost_t0);
        },
        
        // boost
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::this_thread::sleep_for(boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();

            print_result("boost", "sleep_for", std_t1 - std_t0, boost_t1 - boost_t0);
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::this_thread::sleep_until(boost::chrono::steady_clock::now() + boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();

            print_result("boost", "sleep_until_steady", std_t1 - std_t0, boost_t1 - boost_t0);
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::this_thread::sleep_until(boost::chrono::system_clock::now() + boost::chrono::seconds(SLEEP));

            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            print_result("boost", "sleep_until_system", std_t1 - std_t0, boost_t1 - boost_t0);
        },
    };

    std::vector<std::thread> threads;

    for (const auto& f: functions)
        threads.emplace_back(f);

    boost::this_thread::sleep_for(boost::chrono::seconds(1)); // to let all threads come into sleep. Bad style, but this is a test...
    synced_cout() << "You have less than " << (SLEEP - 1) << " seconds to change system clock. GO!!!\n";

    for(auto& t: threads)
        t.join();
    
    return 0;
}

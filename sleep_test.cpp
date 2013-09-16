// (c) 2013 Andrey Upadyshev aka oliora <oliora@gmail.com>.
// File released to public domain.
#include "common.h"
#include <thread>
#include <boost/thread.hpp>
#include <vector>


int main(int argc, char *argv[])
{
    using namespace chrono_test;
    
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
            
            synced_cout()
                << std::left << std::setw(10) << "std" << std::right
                << std::setw(35) << "sleep_for  timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() 
                << std::left << std::setw(10) << "std" << std::right
                << std::setw(35) << "sleep_until_steady  timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();

            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(SLEEP));

            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout()
                << std::left << std::setw(10) << "std" << std::right
                << std::setw(35) << "sleep_until_system  timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)\n";
        },
        
        // boost
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::this_thread::sleep_for(boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout()
                << std::left << std::setw(10) << "boost" << std::right
                << std::setw(35) << "sleep_for  timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::this_thread::sleep_until(boost::chrono::steady_clock::now() + boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout()
                << std::left << std::setw(10) << "boost" << std::right
                << std::setw(35) << "sleep_until_steady  timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::this_thread::sleep_until(boost::chrono::system_clock::now() + boost::chrono::seconds(SLEEP));

            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout()
                << std::left << std::setw(10) << "boost" << std::right
                << std::setw(35) << "sleep_until_system  timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)\n";
        },
    };

    std::vector<boost::thread> threads;

    for (const auto& f: functions)
        threads.emplace_back(f);

    boost::this_thread::sleep_for(boost::chrono::seconds(1)); // to let all threads come into sleep. Bad style, but this is a test...
    synced_cout() << "You have less than " << (SLEEP - 1) << " seconds to change system clock. GO!!!\n";

    for(auto& t: threads)
        t.join();
    
    return 0;
}

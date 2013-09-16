// (c) 2013 Andrey Upadyshev aka oliora <oliora@gmail.com>.
// File released to public domain.

#include "common.h"
#include <thread>
#include <condition_variable>
#include <future>
#include <boost/thread.hpp>
#include <vector>


namespace
{
    std::string to_str(std::cv_status::cv_status status)
    {
        switch (status)
        {
        case std::cv_status::timeout:
            return "timeout";
        case std::cv_status::no_timeout:
            return "NO timeout";
        default:
            throw std::logic_error("wrong cv status");
        }
    }

    std::string to_str(boost::cv_status status)
    {
        switch (status)
        {
        case boost::cv_status::timeout:
            return "timeout";
        case boost::cv_status::no_timeout:
            return "NO timeout";
        default:
            throw std::logic_error("wrong cv status");
        }
    }

    std::string to_str(std::future_status::future_status status)
    {
        switch (status)
        {
        case std::future_status::timeout:
            return "timeout";
        case std::future_status::ready:
            return "ready";
        case std::future_status::deferred:
            return "deferred";
        default:
            throw std::logic_error("wrong future status");
        }
    }

    std::string to_str(boost::future_status status)
    {
        switch (status)
        {
        case boost::future_status::timeout:
            return "timeout";
        case boost::future_status::ready:
            return "ready";
        case boost::future_status::deferred:
            return "deferred";
        default:
            throw std::logic_error("wrong future status");
        }
    }
}    


int main(int argc, char *argv[])
{
    using namespace chrono_test;
    
    typedef void (*func)();
    
    enum { SLEEP = 15 }; // seconds

    func functions[] = {
        // std condition_variable
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::mutex std_m;
            std::condition_variable std_c;
            std::unique_lock<std::mutex> l(std_m);
            std::cv_status::cv_status s = std_c.wait_for(l, std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "wait_for_std" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::mutex std_m;
            std::condition_variable std_c;
            std::unique_lock<std::mutex> l(std_m);
            std::cv_status::cv_status s = std_c.wait_until(l, std::chrono::steady_clock::now() + std::chrono::seconds(SLEEP));

            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "wait_until_steady_std" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::mutex std_m;
            std::condition_variable std_c;
            std::unique_lock<std::mutex> l(std_m);
            std::cv_status::cv_status s = std_c.wait_until(l, std::chrono::system_clock::now() + std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "wait_until_system_std" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        
        // boost condition_variable
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::mutex boost_m;
            boost::condition_variable boost_c;
            boost::unique_lock<boost::mutex> l(boost_m);
            boost::cv_status s = boost_c.wait_for(l, boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "wait_for_bst" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::mutex boost_m;
            boost::condition_variable boost_c;
            boost::unique_lock<boost::mutex> l(boost_m);
            boost::cv_status s = boost_c.wait_until(l, boost::chrono::steady_clock::now() + boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "wait_until_steady_bst" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::mutex boost_m;
            boost::condition_variable boost_c;
            boost::unique_lock<boost::mutex> l(boost_m);
            boost::cv_status s = boost_c.wait_until(l, boost::chrono::system_clock::now() + boost::chrono::seconds(SLEEP));

            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "wait_until_system_bst" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },

        // std future
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::future<int> f = std::async(std::launch::async, [](){ boost::this_thread::sleep_for(boost::chrono::hours(24)); });
            std::future_status::future_status s = f.wait_for(std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "fufute_wait_for_std" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::future<int> f = std::async(std::launch::async, [](){ boost::this_thread::sleep_for(boost::chrono::hours(24)); });
            std::future_status::future_status s = f.wait_until(std::chrono::steady_clock::now() + std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "fufute_wait_until_steady_std" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            std::future<int> f = std::async(std::launch::async, [](){ boost::this_thread::sleep_for(boost::chrono::hours(24)); });
            std::future_status::future_status s = f.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "future_wait_until_system_std" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },

        // boost future
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::promise<int> pt;
            boost::unique_future<int> f=pt.get_future();
            boost::future_status s = f.wait_for(boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "fufute_wait_for_bst" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::promise<int> pt;
            boost::unique_future<int> f=pt.get_future();
            boost::future_status s = f.wait_until(boost::chrono::steady_clock::now() + boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "fufute_wait_until_steady_bst" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
        [] {
            const auto boost_t0 = boost::chrono::steady_clock::now();
            const auto std_t0 = std::chrono::steady_clock::now();
            
            boost::promise<int> pt;
            boost::unique_future<int> f=pt.get_future();
            boost::future_status s = f.wait_until(boost::chrono::system_clock::now() + boost::chrono::seconds(SLEEP));
            
            const auto boost_t1 = boost::chrono::steady_clock::now();
            const auto std_t1 = std::chrono::steady_clock::now();
            
            synced_cout() << std::setw(30) << "future_wait_until_system_bst" << " finished. Timings, s: "
                << std::setw(10) << seconds(std_t1 - std_t0) << " (std)"
                << std::setw(10) << seconds(boost_t1 - boost_t0) << " (boost)"
                << std::setw(12) << to_str(s) << "\n";
        },
    };

    std::vector<boost::thread> threads;

    for (const auto& f: functions)
        threads.emplace_back(f);

    boost::this_thread::sleep_for(boost::chrono::seconds(1)); // to let all threads come into wait. Bad style, but this is a test...
    synced_cout() << "You have less than " << (SLEEP - 1) << " seconds to change system clock. GO!!!\n";

    for(auto& t: threads)
        t.join();
    
    return 0;
}

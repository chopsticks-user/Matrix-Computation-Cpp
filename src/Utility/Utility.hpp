#ifndef ULTILITY_HPP
#define ULTILITY_HPP

#include "Expect.hpp"

#include <type_traits>
#include <iostream>
#include <chrono>
#include <random>

namespace utility
{
    using mic = std::chrono::microseconds;
    using mil = std::chrono::milliseconds;
    using sec = std::chrono::seconds;
    using min = std::chrono::minutes;
    using hr = std::chrono::hours;

    template <typename DurationType = mic>
    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::string time_unit;

    public:
        Timer()
        {
            if (std::is_same_v<DurationType, mic>)
                this->time_unit = "μs";
            else if (std::is_same_v<DurationType, mil>)
                this->time_unit = "ms";

            else if (std::is_same_v<DurationType, sec>)
                this->time_unit = "s";

            else if (std::is_same_v<DurationType, min>)
                this->time_unit = "mins";

            else if (std::is_same_v<DurationType, hr>)
                this->time_unit = "hrs";
            else
                static_assert("Unkown time unit.");

            this->start = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            auto stop = std::chrono::high_resolution_clock::now();
            std::cout << "Time elapsed: "
                      << std::chrono::duration_cast<
                             DurationType>(stop - start)
                             .count()
                      << ' ' << this->time_unit << "\n";
        }
    };

    long long rand(long long min, long long max)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<long long> dist(min, max);
        return dist(rng);
    }

    template <typename T>
    constexpr bool is_lvalue(T &&)
    {
        return std::is_lvalue_reference<T>{};
    };

    template <typename T>
    constexpr bool is_rvalue(T &&)
    {
        return std::is_rvalue_reference<T &&>{};
    };

    

} /* utility */

#endif /* ULTILITY_HPP */
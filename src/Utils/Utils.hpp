#ifndef LIN_ALG_UTILS_HPP
#define LIN_ALG_UTILS_HPP

#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <type_traits>

// must be independent of any other namespace

namespace __zz_utils__
{
    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::string time_unit;

    public:
        Timer()
        {
            this->start = std::chrono::high_resolution_clock::now();
            this->time_unit = "milliseconds";
        }
        Timer(std::string &&time_unit)
        {
            this->start = std::chrono::high_resolution_clock::now();
            if (time_unit == "microseconds")
            {
                this->time_unit = "microseconds";
                return;
            }
            this->time_unit = "milliseconds";
        }
        ~Timer()
        {
            auto stop = std::chrono::high_resolution_clock::now();
            if (this->time_unit == "microseconds")
            {
                std::cout << "\nTime elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n";
                return;
            }
            std::cout << "\nTime elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
        }
    };

    long long rand(long long min, long long max)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<long long> dist(min, max);
        return dist(rng);
    }

    constexpr bool is_declared_static_matrix_v(size_t r_sz, size_t c_sz)
    {
        return r_sz != 0 || c_sz != 0;
    };

    constexpr size_t sq_mat_size(size_t r_sz, size_t c_sz)
    {
        return c_sz == 0 ? r_sz * r_sz : r_sz * c_sz;
    }

    template <typename TargetType>
    bool is_1d_c_array_v(const TargetType &target)
    {
        return std::is_array_v<TargetType> && std::rank_v<TargetType> == 1;
    }
}

#endif /* LIN_ALG_UTILS_HPP */
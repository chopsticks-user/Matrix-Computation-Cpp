#include "src/LinearAlgebra.hpp"

#include <iostream>
#include <chrono>
#include <string>
#include <random>

namespace utils
{
    long long rand(long long min, long long max)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<long long> dist(min, max);
        return dist(rng);
    }

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
}

const int n = 10000;

void test1()
{
    utils::Timer t1;
    for (int i = 0; i < n; i++)
    {
        std::vector<float> v(360000);
    }
}

void test2()
{
    utils::Timer t2;
    for (int i = 0; i < n; i++)
    {
        Matrix<float, 600, 600> m;
        m.data_->data_[30000] = 0;
    }
}

int main()
{
    test2();
    return 0;
}
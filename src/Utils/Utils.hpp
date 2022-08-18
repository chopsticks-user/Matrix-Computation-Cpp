#include <iostream>
#include <chrono>
#include <string>
#include <random>

namespace ultis
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
#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>
#include <functional>
#include <string_view>

using namespace linear_algebra;
using namespace zz_no_inc;
using utility::Timer;

class A
{
public:
    int aa;
    int ac;
    int ad;
    A() { aa = 2; };
    A(const A &a) = delete;
    ~A() = default;
};

template <typename T>
constexpr bool test(T &&x)
{
    std::cout << std::addressof(x) << '\n';
    if constexpr (std::is_lvalue_reference_v<T>)
        return true;
    else
        return false;
}

int main()
{

    try
    {
        {
            int sum = 0;
            Matrix<int> m1(1000, 1000, 10);
            utility::Timer t1;
            for (auto it = m1.begin(); it != m1.end(); ++it)
            {
                sum++;
                *it;
            }
            // for (auto i = 0; i < 10000; i++)
            //     for (auto j = 0; j < 10000; j++)
            //     {
            //         sum++;
            //         m1(i, j);
            //     }
            std::cout << sum << '\n';
        }

        {
            int sum = 0;
            std::vector<int> v1(1000000, 10);
            utility::Timer t2;
            for (auto i = 0; i < 1000000; i++)
            {
                sum++;
                v1[i];
            }
            // for (auto it = v1.begin(); it != v1.end(); ++it)
            // {
            //     sum++;
            // }
            std::cout << sum << '\n';
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

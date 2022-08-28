#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>
#include <functional>
#include <string_view>

using namespace linear_algebra;
using utility::Timer;

int main()
{

    try
    {
        int n = 10000;
        int m = 10000;
        {
            Matrix<int> m1(n, m, -1);
            // Matrix<int> m2(m, m, -1);
            // m1(0,1) = 1000;

            Timer t1;
            // std::cout << m1.upper_triangle() << '\n';
            m1.upper_triangle();
        }

        {
            // int sum = 0;
            // std::vector<int> v1(size, -2383);
            // Timer t2;
            // // for (auto it = v1.begin(); it != v1.end(); ++it)
            // // {
            // //     *it;
            // // }
            // for (auto i = 0; i < size; i++)
            // {
            //     v1[i];
            // }
            int a;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

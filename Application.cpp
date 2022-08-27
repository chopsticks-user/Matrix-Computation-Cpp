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

int main()
{

    try
    {
        int n = 10000;
        int size = n * n;
        {
            int sum = 0;
            Matrix<int> m1(n, n, 12319);
            Timer t1;
            const auto *it = m1.begin();
            const auto *it_end = m1.end();
            while (it != it_end)
                *(it++);
            std::cout << *(it-1) << '\n';
        }

        {
            int sum = 0;
            std::vector<int> v1(size, -2383);
            Timer t2;
            // for (auto it = v1.begin(); it != v1.end(); ++it)
            // {
            //     *it;
            // }
            for (auto i = 0; i < size; i++)
            {
                v1[i];
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

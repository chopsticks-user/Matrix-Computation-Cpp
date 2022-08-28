#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>
#include <functional>
#include <string_view>
#include <tuple>

using namespace linear_algebra;
using utility::MatrixIt;
using utility::Timer;

int main()
{

    try
    {
        Matrix<int> m1(10000, 10000, 555);
        Matrix<int> m2(10000, 10000, -66);

        {
            Matrix<int> m3(10000, 10000);
            Timer t1;
            matrix::subtract(m1.iterator(), m2.iterator(), m3.iterator(), false);
        }

        {
            Matrix<int> m3(10000, 10000);
            Timer t1;
            matrix::subtract(m1.iterator(), m2.iterator(), m3.iterator());
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

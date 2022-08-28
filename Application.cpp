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

template <typename ItTp, typename RowSizeTp>
void test(MatrixIt<ItTp, RowSizeTp> it1,
          MatrixIt<ItTp, RowSizeTp> it2)
{
}

int main()
{

    try
    {
        Matrix<int> m1(10000, 10000, 555);
        Matrix<int> m2(10000, 10000, -66);

        {
            Timer t1;
            // std::cout << m2 + m1;
            m1 - m2;
        }

        {
            Timer t1;
            Matrix<int> m3(10000, 10000);
            matrix::add(m1.iterator(), m2.iterator(), m3.iterator());
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

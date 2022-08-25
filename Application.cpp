#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>

using namespace zz_no_inc;
using namespace linear_algebra;

class A
{
public:
    A(){};
    A(const A &a) = delete;
};

int main()
{

    try
    {
        Matrix<int> m1(4, 3, 1);
        Matrix<int> m2 = m1;

        Matrix<int, 4, 3> m3 = std::move(m2.fill_column(-1, 2).fill_row(-1, 2).fill(0));

        m3.fill(3);

        // m2 = m3.copy_to_row();

        std::cout << m2 << '\n';
        std::cout << m3 << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}
#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>

// using namespace zz_no_inc;
using namespace linear_algebra;

int main()
{

    try
    {
        Matrix<int> m1;
        std::cout << m1.matrix_ptr_->data__.size() << '\n';
        std::cout << sizeof(m1) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
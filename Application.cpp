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
        Matrix<int> m1(1, 2);
        std::cout << m1.matrix_ptr_->data__.size() << '\n';
        std::cout << *(m1.matrix_ptr_) << '\n';
        std::cout << std::is_copy_constructible_v<std::shared_ptr<int>> << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
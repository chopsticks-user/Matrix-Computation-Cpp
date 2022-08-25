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
        Matrix<int, 4, 3> m2 = std::move(m1);
        m2.matrix_ptr_->fill_all_element_with_(2);
        std::cout << *m1.matrix_ptr_ << '\n';
        std::cout << *m2.matrix_ptr_ << '\n';
        std::cout << m1.is_dynamic_matrix() << '\n';

        constexpr auto a = m1.is_dynamic_matrix();

    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}
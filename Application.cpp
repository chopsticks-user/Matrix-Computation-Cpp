#include "src/LinearAlgebra.hpp"

#include <list>
#include <array>
#include <typeinfo>

class A
{
    int a = 0;

public:
    A() = default;
    explicit A(int a) : a(a){};
    A(const A &r) = default;
    A(A &&r) = default;
    A &operator=(const A &r)
    {
        this->a = r.a;
        return *this;
    }
    A &operator=(A &&r)
    {
        this->a = std::move(r.a);
        return *this;
    }
    A b()
    {
        this->a++;
        std::cout << this->a << "\n";
        return *this;
    }
    A c()
    {
        this->a += 2;
        std::cout << this->a << "\n";
        return *this;
    }
};

using namespace linear_algebra;

auto cr()
{
    return zz_BaseMatrix<int>();
}

int main()
{
    auto a = cr();
    a.fill_initialize(5, 5, 10);
    auto b = zz_BaseMatrix<int, 5, 5>();
    b.move_initialize(std::move(a));
    auto c = zz_BaseMatrix<int>();
    c.move_initialize(std::move(b));
    c.access_element_at(4, 4) = 100;

    utility::validate_matrix_dimensions<0, 0>();

    constexpr bool bbb = utility::is_dynamic_matrix_vv<2, 3>::value;

    std::cout << bbb << '\n';

    // std::cout << a.n_rows_ << '\n'
    //           << a.n_cols_ << '\n'
    //           << a.data_[0] << '\n'
    //           << typeid(a.data_).name() << '\n';

    return 0;
}
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
};

using namespace linear_algebra;

auto cr()
{
    return zz_BaseMatrix<int>();
}

constexpr auto bb(int a)
{
    return a;
}

int main()
{
    auto a = cr();
    a.default_fill_initialize(5, 5, 10);
    auto b = zz_BaseMatrix<int, 5, 5>();
    b.default_move_initialize(std::move(a));
    auto c = zz_BaseMatrix<int>();
    c.default_move_initialize(std::move(b));

    // auto cb = b.clone_data();
    // b.data_[0] = 100;
    // std::cout<<cb[0];

    std::cout << a.n_rows_ << '\n'
              << a.n_cols_ << '\n'
              << a.data_[0] << '\n'
              << typeid(a.data_).name() << '\n';

    // std::cout << typeid(a.data_).name() << '\n'
    //           << a.data_.size() << '\n'
    //           << a.is_dynamic_matrix() << '\n'
    //           << a.is_static_matrix() << '\n';
    // // a.default_fill_initialize();
    return 0;
}
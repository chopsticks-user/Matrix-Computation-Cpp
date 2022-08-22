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

int main()
{
    zz_BaseMatrix<int, 2> a;
    std::cout << typeid(a.data_).name() << '\n'
              << a.data_.size() << '\n'
              << a.is_dynamic_matrix() << '\n'
              << a.is_static_matrix() << '\n';
    a.default_fill_initialize();
    return 0;
}
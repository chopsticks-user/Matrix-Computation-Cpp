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
    zz_BaseMatrix<int, 5> a;
    std::cout << typeid(a.data_).name() << '\n'
              << a.data_.size() << '\n';
    return 0;
}
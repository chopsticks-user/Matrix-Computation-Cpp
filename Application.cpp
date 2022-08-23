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

// constexpr void aaa(long a, long b)
// {
//     utility::verified_matrix_data_container_size<a, b>();
// }

using namespace linear_algebra;

int main()
{
    auto a = zz_BaseMatrix<int>();
    auto b = zz_BaseMatrix<int, 5>();
    auto c = zz_BaseMatrix<int, 5, 6>();
    c.access_element_at(4, 4) = 100;

    std::cout << a.data_.size() << " " << a.is_dynamic() << " " << a.is_static() << '\n';
    std::cout << b.data_.size() << " " << b.is_dynamic() << " " << b.is_static() << '\n';
    std::cout << c.data_.size() << " " << c.is_dynamic() << " " << c.is_static() << '\n';
    std::cout << utility::check_if_dynamic_matrix(0, 0) << '\n';

    // constexpr auto aaa = utility::check_if_static_square_matrix<0, 0>();

    // std::cout<< utility::check_if_static_square_matrix<0, 0>()<<'\n';
    // std::cout<< utility::verified_matrix_col_size<25, 0>()<<'\n';
    // std::cout<< utility::verified_matrix_data_container_size<25, 3>()<<'\n';

    // std::cout << a.n_rows_ << '\n'
    //           << a.n_cols_ << '\n'
    //           << a.data_[0] << '\n'
    //           << typeid(a.data_).name() << '\n';

    return 0;
}
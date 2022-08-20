#include "src/LinearAlgebra.hpp"

#include <list>
#include <array>

int main()
{
    // test1();
    Matrix<float> m;
    // std::cout << m.is_static_matrix_v() << '\n';

    Matrix<float, 1> m1;
    // std::cout << m1.is_static_matrix_v() << '\n';

    Matrix<int, 4, 3> m2;
    // std::cout << m2.is_static_matrix_v() << '\n';

    Matrix<int, 1000, 1100> m3;

    std::cout << sizeof(m3) << '\n';
    m2.print();
    // void* ptr;

    // std::list<int> l(10);

    // std::array<float, 5> arr;

    // float a[5] = {0, 0, 2, 3, 0};

    // arr.fill(2.1);

    // std::vector<float> v(9, 1);

    // ptr = arr.begin();

    // v.insert(v.begin()+2, arr.begin(), arr.end());

    // for (auto &i : v)
    //     std::cout << i << " ";
    // std::cout << '\n';
    // transform_to_matrix<2,2>(a);

    // Matrix<float, 20, 20> m1(m);

    // m1.data_->data_[0] = 2;

    // std::cout << m.data_->data_.size() << '\n';

    return 0;
}
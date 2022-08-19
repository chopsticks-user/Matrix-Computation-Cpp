#include "src/LinearAlgebra.hpp"

#include <list>
#include <array>

// template <size_t row_size, size_t col_size, typename T>
// auto transform_to_matrix(const T &target)
// {
//     try
//     {
//         if (std::is_array_v<T>)
//         {
//             if (std::rank_v<T> == 1 && std::rank_v<T> == 2)
//                 return target;
//         }
//     }
//     catch (...)
//     {
//         std::cerr << "Errors occurred during transformation." << '\n';
//     }
// }

// const int n = 10000;

// void test1()
// {
//     utils::general::Timer t1;
//     for (int i = 0; i < n; i++)
//     {
//         std::vector<float> v(360000);
//     }
// }

// void test2()
// {
//     utils::general::Timer t2;
//     for (int i = 0; i < n; i++)
//     {
//         Matrix<float, 600, 600> m2;
//     }
// }

int main()
{
    // test1();
    Matrix<float> m;
    std::cout << m.is_static_matrix_v() << '\n';

    // Matrix<float, 2> m1;
    // std::cout << m1.is_static_matrix_v() << '\n';

    // Matrix<int, 2, 3> m2;
    // std::cout << m2.is_static_matrix_v() << '\n';

    // Matrix<int, 2, 3> m3(m2);

    std::list<int> l(10);

    std::array<float, 5> arr;

    float a[5] = {0, 0, 2, 3, 0};

    arr.fill(2.1);

    std::vector<float> v(9, 1);

    v.insert(v.begin(), arr.begin(), arr.end());

    for (auto &i : v)
        std::cout << i << " ";
    std::cout << '\n';
    // transform_to_matrix<2,2>(a);

    // Matrix<float, 20, 20> m1(m);

    // m1.data_->data_[0] = 2;

    // std::cout << m.data_->data_.size() << '\n';

    return 0;
}
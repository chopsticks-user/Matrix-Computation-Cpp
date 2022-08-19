#include "src/LinearAlgebra.hpp"

const int n = 10000;

void test1()
{
    utils::Timer t1;
    for (int i = 0; i < n; i++)
    {
        std::vector<float> v(360000);
    }
}

void test2()
{
    utils::Timer t2;
    for (int i = 0; i < n; i++)
    {
        Matrix<float, 600, 600> m2;
    }
}

int main()
{
    // test1();
    Matrix<float> m;
    std::cout << m.is_static_matrix_v() << '\n';

    Matrix<float, 2> m1;
    std::cout << m1.is_static_matrix_v()<< '\n';

    Matrix<int, 2, 3> m2;
    std::cout << m2.is_static_matrix_v() << '\n';
    // Matrix<float, 20, 20> m1(m);

    // m1.data_->data_[0] = 2;

    // std::cout << m.data_->data_.size() << '\n';

    return 0;
}
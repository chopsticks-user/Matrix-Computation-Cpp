#include "src/LinearAlgebra.hpp"

int main()
{
    std::vector<int> a;
    DynamicMatrix<float> dm(60, 70, 2000);
    StaticMatrix<int, 77, 77> sm(55);
    std::cout << typeid(dm.data_).name() << '\n';
    std::cout << typeid(sm.data_).name() << '\n';
    std::cout << sm.data_.size() << '\n';
    std::cout << dm.data_.size() << '\n';
    std::cout << dm.data_.max_size() << '\n';
    return 0;
}
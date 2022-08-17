#include "src/N3K0.hpp"

int main()
{
    std::vector<int> a;
    DynamicMatrix<float> dm(6, 5, 2000);
    StaticMatrix<int, 55, 56> sm(55);
    std::cout << typeid(dm.data_).name() << '\n';
    std::cout << typeid(sm.data_).name() << '\n';
    std::cout << sm.data_[0] << '\n';
    std::cout << dm.data_[0] << '\n';
    return 0;
}
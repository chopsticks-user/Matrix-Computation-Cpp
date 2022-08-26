#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>
#include <functional>

using namespace linear_algebra;

class A
{
public:
    int aa;
    int ac;
    int ad;
    A() { aa = 0; };
    A(const A &a) = delete;
    ~A() = default;
};

int main()
{

    try
    {
        auto t1 = std::make_unique<utility::Timer>();

        // Matrix<long long> m1(16, 128);
        // Matrix<long long, 128, 128> m2;
        // Matrix<long long, 128, 3> m3;

        // for (auto &i : m1)
        //     i = utility::rand(1, 10);

        // for (auto &i : m2)
        //     i = utility::rand(1, 10);

        // for (auto &i : m3)
        //     i = utility::rand(1, 10);

        // auto m4 = m1 * m2 * m2 * m3;

        // std::cout << m4 << '\n';
        // std::cout << m4.sub(1, 1) << '\n';

        Matrix<int> m5(3, 4, 5);

        std::cout << m5.fill_row(-1, 0) << '\n';
        std::cout << m5.fill_row(0, 9) << '\n';
        std::cout << m5.row_swap(0, -1) << '\n';
        
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

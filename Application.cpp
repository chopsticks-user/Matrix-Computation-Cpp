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

        Matrix<int, 10, 10> m1(1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

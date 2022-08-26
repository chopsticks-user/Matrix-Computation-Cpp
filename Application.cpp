#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>
#include <functional>
#include <string_view>

using namespace linear_algebra;
using namespace zz_no_inc;

class A
{
public:
    int aa;
    int ac;
    int ad;
    A() { aa = 2; };
    A(const A &a) = delete;
    ~A() = default;
};

template <typename T>
constexpr bool test(T &&x)
{
    std::cout << std::addressof(x) << '\n';
    if constexpr (std::is_lvalue_reference_v<T>)
        return true;
    else
        return false;
}

int main()
{
    // 10000 x 10000
    // dynamic: same-type-cctor: <m, 227ms> vs <v, 156ms>
    // dynamic: same-type-mctor: <m, 109ms> vs <v, 103ms>, default
    // dynamic: same-type-cp=:   <m, 227ms> vs <v, 156ms>
    // dynamic: same-type-mv=:   <m, 106ms> vs <v, 101ms>, default

    try
    {
        Matrix<int> m1(10000, 10000, 69);
        Matrix<int, 10000, 10000> m2;
        auto *t1 = new utility::Timer;
        m2 = std::move(m1);
        std::cout << m2(10, 10) << '\n';
        // auto md = m2.data();
        delete t1;

        std::vector<int> v1(100000000, 69);
        std::vector<int> v2;
        auto *t2 = new utility::Timer;
        v2 = std::move(v1);
        delete t2;

        // auto p = std::make_unique<int>();
        // *p = 5;
        // int a = *p;
        // std::cout << *p << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nERROR: " << e.what() << "\n\n";
        return 0;
    }
    return 0;
}

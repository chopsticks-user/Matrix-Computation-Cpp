#include "src/LinearAlgebra.hpp"
#include "src/Exception/Exception.hpp"

#include <list>
#include <array>
#include <typeinfo>

using namespace zz_no_inc;

int main()
{

    try
    {
        DynamicMatrix_<int> a(5, 5, 1);
        DynamicMatrix_<int> b(a);

        a.fill_all_element_with_(56);
        b.fill_all_element_with_(12);

        std::cout << a;
        std::cout << b;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
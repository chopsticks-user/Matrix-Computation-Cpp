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
        DynamicMatrix_<float> a(3, 3);
        DynamicMatrix_<int> b(a);

        int j = 1;
        for (auto & i:b.data__)
        {
            i = j;
            j++;
        }

        std::vector<int> v = {0, 0, 0};
        std::vector<int> v1 = {6, 6, 6, 6, 6};

        b.insert_col_at_(3, v)
            .insert_col_at_(2, v)
            .insert_row_at_(1, v1);

        std::cout << b;
        
        b.erase_row_at_(0);
        b.erase_col_at_(4);

        std::cout << b;
        std::cout << b.data__.size() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
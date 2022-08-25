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

        std::vector<int> v = {1, 1, 1};
        std::vector<int> v1 = {6, 6, 6, 6, 6};
        
        StaticMatrix_<int, 3, 40> c;
        c.copy_data_to_col(2, v);

        b.insert_col_at_(3, v)
            .insert_col_at_(2, v)
            .insert_row_at_(1, v1)
            .erase_row_at_(0)
            .erase_col_at_(4);

    

        std::cout << c;
        std::cout << c.data__.size() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
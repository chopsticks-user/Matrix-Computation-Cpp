#ifndef MATRIX_CONTAINER_HELPER_HPP
#define MATRIX_CONTAINER_HELPER_HPP

#include <iostream>

namespace linear_algebra
{
    namespace container
    {
        

    }
}

constexpr bool is_declared_static_matrix_v(size_t r_sz, size_t c_sz)
{ return r_sz != 0 || c_sz != 0; };

constexpr size_t sq_mat_size(size_t r_sz, size_t c_sz)
{ return c_sz == 0 ? r_sz * r_sz : r_sz * c_sz; }



#endif /* MATRIX_CONTAINER_HELPER_HPP */
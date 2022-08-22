#ifndef LIN_ALG_CONTAINER_STATIC_MATRIX_HPP
#define LIN_ALG_CONTAINER_STATIC_MATRIX_HPP

#include "MatrixBase.hpp"

namespace linear_algebra
{
    template <typename ElementType,
              utility::SizeType templ_row_size = 0,
              utility::SizeType templ_col_size = 0>
    class zz_MatrixStatic
        : public zz_BaseMatrix<ElementType,
                               templ_row_size,
                               templ_col_size>
    {
    };
}

#endif /* LIN_ALG_CONTAINER_STATIC_MATRIX_HPP */
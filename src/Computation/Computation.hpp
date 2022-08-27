#ifndef LINEAR_ALGEBRA_COMPUTATION_HPP
#define LINEAR_ALGEBRA_COMPUTATION_HPP

#include "../Utility/Utility.hpp"
#include <math.h>

namespace linear_algebra
{
    template <typename IteratorType, typename RowSizeType>
    struct MatrixItWrapper
    {
        IteratorType begin;
        IteratorType end;
        RowSizeType row_size;
    };

    namespace matrix_helper
    {
        template <typename Matrix1, typename Matrix2>
        auto add(const Matrix1& m1, const Matrix2& m2)
        {
            // utility::expect()
        }
    } /* matrix_helper */
} /* linear_algebra */

#endif /* LINEAR_ALGEBRA_COMPUTATION_HPP */
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

        MatrixItWrapper(IteratorType begin, IteratorType end, RowSizeType row_size)
            : begin(begin), end(end), row_size(row_size){};
    };

    namespace matrix_helper
    {
        // template <typename IteratorType, typename RowSizeType>
        // void add(IteratorType it1, IteratorType it2,
        //          IteratorType it_res, RowSizeType row_size)
        // {
        //     auto i = 0;
        //     while ((mat_it_wr_res.begin + i) != mat_it_wr_res.end)
        //     {
        //         *(mat_it_wr_res.begin + i) = (*(mat_it_wr1.begin + i)) +
        //                                      (*(mat_it_wr2.begin + i));
        //     }
        // }
    } /* matrix_helper */
} /* linear_algebra */

#endif /* LINEAR_ALGEBRA_COMPUTATION_HPP */
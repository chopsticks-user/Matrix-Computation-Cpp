#ifndef LINEAR_ALGEBRA_COMPUTATION_MATRIX_HPP
#define LINEAR_ALGEBRA_COMPUTATION_MATRIX_HPP

#include "../Utility/Utility.hpp"

#include <math.h>

namespace linear_algebra
{
    namespace matrix_helper
    {

    } /* matrix_helper */

    namespace matrix
    {
        template <typename ItTp, typename RowSizeTp>
        void add(utility::MatrixIt<ItTp, RowSizeTp> it1,
                 utility::MatrixIt<ItTp, RowSizeTp> it2,
                 utility::MatrixIt<ItTp, RowSizeTp> it_res)
        {
            utility::expect(it1.row_size == it2.row_size && it2.row_size == it_res.row_size,
                            std::range_error("Matrix addition: Dimensions mismatch."));
            RowSizeTp len = it_res.end - it_res.begin;
            for(RowSizeTp i = 0; i < len; ++i)
                *(it_res.begin + i) = *(it1.begin + i) + *(it2.begin + i);
        }

        // template <typename ItTp, typename RowSizeTp>
        // void add(utility::MatrixIt<ItTp, RowSizeTp> &&it1,
        //          utility::MatrixIt<ItTp, RowSizeTp> &&it2,
        //          utility::MatrixIt<ItTp, RowSizeTp> &&it_res)
        // {
        //     utility::expect(it1.row_size == it2.row_size == it_res.row_size,
        //                     std::range_error("Matrix addition: Dimensions mismatch."));
        //     RowSizeTp len = it_res.row_size;
        //     RowSizeTp i = 0;
        //     while (i++ < len)
        //         *(it_res.begin + i) = *(it1.begin + i) + *(it2.begin + i);
        // }
    } /* matrix */

} /* linear_algebra */

#endif /* LINEAR_ALGEBRA_COMPUTATION_MATRIX_HPP */
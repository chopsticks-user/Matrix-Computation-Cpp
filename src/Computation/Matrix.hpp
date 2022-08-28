#ifndef LINEAR_ALGEBRA_COMPUTATION_MATRIX_HPP
#define LINEAR_ALGEBRA_COMPUTATION_MATRIX_HPP

#include "../Utility/Utility.hpp"

#include <math.h>

namespace linear_algebra
{
    namespace matrix
    {
        namespace helper
        {

        } /* helper */

        template <typename ItTp, typename RowSizeTp>
        void add(utility::MatrixIt<ItTp, RowSizeTp> it1,
                 utility::MatrixIt<ItTp, RowSizeTp> it2,
                 utility::MatrixIt<ItTp, RowSizeTp> it_res,
                 bool require_pre_cond = true)
        {
            if (require_pre_cond)
                utility::expect(it1.row_size == it2.row_size && it2.row_size == it_res.row_size &&
                                    it1.end - it1.begin == it2.end - it2.begin &&
                                    it1.end - it1.begin == it_res.end - it_res.begin,
                                std::range_error("Matrix addition: Dimensions mismatch."));
            RowSizeTp len = it_res.end - it_res.begin;
            for (RowSizeTp i = 0; i < len; ++i)
                *(it_res.begin + i) = *(it1.begin + i) + *(it2.begin + i);
        }

        template <typename ItTp, typename RowSizeTp>
        void subtract(utility::MatrixIt<ItTp, RowSizeTp> it1,
                      utility::MatrixIt<ItTp, RowSizeTp> it2,
                      utility::MatrixIt<ItTp, RowSizeTp> it_res,
                      bool require_pre_cond = true)
        {
            if (require_pre_cond)
                utility::expect(it1.row_size == it2.row_size && it2.row_size == it_res.row_size &&
                                    it1.end - it1.begin == it2.end - it2.begin &&
                                    it1.end - it1.begin == it_res.end - it_res.begin,
                                std::range_error("Matrix subtraction: Dimensions mismatch."));
            RowSizeTp len = it_res.end - it_res.begin;
            for (RowSizeTp i = 0; i < len; ++i)
                *(it_res.begin + i) = *(it1.begin + i) - *(it2.begin + i);
        }
    } /* matrix */

} /* linear_algebra */

#endif /* LINEAR_ALGEBRA_COMPUTATION_MATRIX_HPP */
#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"

















// template <typename CastElementType,
//           SizeType cast_row_size,
//           SizeType cast_col_size>
// operator MatrixBase_<CastElementType,
//                      cast_row_size,
//                      cast_col_size>() const
// {
//     if constexpr (utility::check_if_static_matrix<templ_row_size, templ_col_size>())
//     {
//         if constexpr (utility::check_if_static_matrix<cast_row_size, cast_col_size>())
//         {
//             static_assert(utility::check_if_equal_dimensions<templ_row_size, templ_col_size, cast_row_size, cast_col_size>(),
//                           "Invalid cast, dimensions mismatch.");
//             return MatrixBase_<CastElementType, cast_row_size, cast_col_size> = this;
//         }
//         return MatrixBase_<CastElementType> = this;
//     }
// }

#endif /* LIN_ALG_CONTAINER_MATRIX_HPP */
#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"

#include <memory>

namespace linear_algebra
{
    template <typename ElementType,
              utility::SizeType templ_row_size = 0,
              utility::SizeType templ_col_size = 0>
    class Matrix
    {
        typedef utility::SizeType SizeType;

        typedef zz_no_inc::StaticMatrix_<ElementType,
                                         templ_row_size,
                                         templ_col_size>
            StaticMatrixType;

        typedef zz_no_inc::DynamicMatrix_<ElementType>
            DynamicMatrixType;

        template <typename ReturnType>
        using DynamicMatrixMethod = typename std::enable_if_t<
            utility::is_declared_dynamic_matrix<templ_row_size,
                                                templ_col_size>{},
            ReturnType>;

        template <typename ReturnType>
        using StaticMatrixMethod = typename std::enable_if_t<
            utility::is_declared_static_matrix<templ_row_size,
                                               templ_col_size>{},
            ReturnType>;

        typedef std::conditional_t<utility::check_if_dynamic_matrix<
                                       templ_row_size,
                                       templ_col_size>(),
                                   DynamicMatrixType,
                                   StaticMatrixType>
            MatrixType;

    public:
        std::unique_ptr<MatrixType> matrix_ptr_;

        Matrix() : matrix_ptr_(std::make_unique<MatrixType>()){};

        ~Matrix() noexcept
        {
            std::cout << "An instance of Matrix has been destroyed.\n";
        }

        /// check if ElementType is copy constructible.
        explicit Matrix(const ElementType &fill_value)
            : matrix_ptr_(std::make_unique<MatrixType>(fill_value)){};

        explicit Matrix(SizeType n_rows,
                        SizeType n_cols,
                        const ElementType &fill_value = ElementType())
            : matrix_ptr_(std::make_unique<MatrixType>(n_rows, n_cols, fill_value)){};

    private:
    };
}

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
#ifndef LIN_ALG_CONTAINER_STATIC_MATRIX_HPP
#define LIN_ALG_CONTAINER_STATIC_MATRIX_HPP

#include "MatrixBase.hpp"

namespace zz_no_inc
{
    template <typename ElementType,
              utility::SizeType templ_row_size = 0,
              utility::SizeType templ_col_size = 0>
    class StaticMatrix_
        : public MatrixBase_<ElementType,
                             templ_row_size,
                             templ_col_size>
    {
        typedef MatrixBase_<ElementType, templ_row_size, templ_col_size> Base_;
        typedef utility::SizeType SizeType;

    public:
        StaticMatrix_()
        {
            this->set_dimensions_();
        }

        /// Might throw (std::bad_alloc) if std::fill_n failed to allocate memory.
        explicit StaticMatrix_(ElementType fill_value)
        {
            this->fill_initialize_(fill_value);
        }

        StaticMatrix_(const StaticMatrix_ &rhs_matrix)
        {
            this->copy_initialize_(rhs_matrix);
        };

        template<typename RhsMatrixType>
        StaticMatrix_(const RhsMatrixType &rhs_matrix)
        {
            this->copy_initialize_(rhs_matrix);
        };

        template<typename RhsMatrixType>
        StaticMatrix_(RhsMatrixType &&rhs_matrix)
        {
            this->move_initialize_(std::move(rhs_matrix));
        };

        StaticMatrix_(StaticMatrix_ &&rhs_matrix)
        {
            this->move_initialize_(std::move(rhs_matrix));
        }
    };
}

#endif /* LIN_ALG_CONTAINER_STATIC_MATRIX_HPP */
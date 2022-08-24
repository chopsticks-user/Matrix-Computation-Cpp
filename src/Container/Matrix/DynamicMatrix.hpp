#ifndef LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP
#define LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP

#include "MatrixBase.hpp"

namespace zz_no_inc
{
    template <typename ElementType>
    class DynamicMatrix_
        : public MatrixBase_<ElementType>
    {
        typedef MatrixBase_<ElementType> Base_;
        typedef utility::SizeType SizeType;

    public:
        DynamicMatrix_()
        {
            this->set_dimensions_();
        }

        /// Might throw (std::bad_alloc) if std::fill_n failed to allocate memory.
        explicit DynamicMatrix_(SizeType row_size,
                                SizeType col_size = 0,
                                ElementType fill_value = 0)
        {
            this->fill_initialize_(row_size, col_size, fill_value);
        }

        DynamicMatrix_(const DynamicMatrix_ &rhs_matrix)
        {
            this->copy_initialize_(rhs_matrix);
        };

        template <typename RhsMatrixType>
        DynamicMatrix_(const RhsMatrixType &rhs_matrix)
        {
            this->copy_initialize_(rhs_matrix);
        };

        template <typename RhsMatrixType>
        DynamicMatrix_(RhsMatrixType &&rhs_matrix)
        {
            this->move_initialize_(std::move(rhs_matrix));
        };

        DynamicMatrix_(DynamicMatrix_ &&rhs_matrix)
        {
            this->move_initialize_(std::move(rhs_matrix));
        }
    };
}

#endif /* LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP */
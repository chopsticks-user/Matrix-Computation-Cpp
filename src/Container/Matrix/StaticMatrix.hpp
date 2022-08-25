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

        ~StaticMatrix_() noexcept
        {
            std::cout << "An instance of StaticMatrix has been destroyed." << '\n';
        }

        /// Might throw (std::bad_alloc) if std::fill_n failed to allocate memory.
        explicit StaticMatrix_(const ElementType& fill_value)
        {
            this->fill_initialize_(fill_value);
        }

        StaticMatrix_(const StaticMatrix_ &rhs_matrix)
        {
            this->copy_initialize_(rhs_matrix);
        };

        template <typename RhsMatrixType>
        StaticMatrix_(const RhsMatrixType &rhs_matrix)
        {
            this->copy_initialize_(rhs_matrix);
        };

        template <typename RhsMatrixType>
        StaticMatrix_(RhsMatrixType &&rhs_matrix)
        {
            this->move_initialize_(std::move(rhs_matrix));
        };

        StaticMatrix_(StaticMatrix_ &&rhs_matrix)
        {
            this->move_initialize_(std::move(rhs_matrix));
        }

        template <typename SeqContainer1D>
        StaticMatrix_ &copy_data_to_row(SizeType row_index,
                                        const SeqContainer1D &rhs_container)
        {
            SizeType rhs_size = utility::get_1d_seq_container_size(rhs_container);
            if (rhs_size != this->n_cols__)
                throw std::range_error("Row sizes mismatch.");
            if (row_index >= this->n_rows__ || row_index < 0)
                throw std::range_error("Row index out of bounds.");

            std::copy(std::begin(rhs_container),
                      std::end(rhs_container),
                      this->data__.begin() + this->n_cols__ * row_index);
            return *this;
        }

        template <typename SeqContainer1D>
        StaticMatrix_ &copy_data_to_col(SizeType col_index,
                                        const SeqContainer1D &rhs_container)
        {
            SizeType rhs_size = utility::get_1d_seq_container_size(rhs_container);
            if (rhs_size != this->n_rows__)
                throw std::range_error("Column sizes mismatch.");
            if (col_index >= this->n_cols__ || col_index < 0)
                throw std::range_error("Column index out of bounds.");

            for (SizeType i = 0; i < rhs_size; i++)
                this->data__[this->n_cols__ * i + col_index] = rhs_container[i];
            return *this;
        }
    };
}

#endif /* LIN_ALG_CONTAINER_STATIC_MATRIX_HPP */
#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"

#include <memory>

namespace linear_algebra
{
    /// Accept negative indices
    template <typename ElementType,
              long templ_row_size = 0,
              long templ_col_size = 0>
    class Matrix
    {
        typedef long SizeType;

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
        Matrix() : matrix_ptr_(std::make_unique<MatrixType>()){};

        ~Matrix() noexcept
        {
            std::cout << "At memory address: " << std::addressof(*this)
                      << ", an instance of Matrix, whose size of " << sizeof(*this)
                      << " bytes, has been destroyed.\n";
        }

        explicit Matrix(const ElementType &fill_value)
            : matrix_ptr_(std::make_unique<MatrixType>(fill_value)){};

        explicit Matrix(SizeType n_rows,
                        SizeType n_cols,
                        const ElementType &fill_value = ElementType())
            : matrix_ptr_(std::make_unique<MatrixType>(n_rows, n_cols, fill_value)){};

        Matrix(Matrix &rhs_matrix)
            : matrix_ptr_(std::move(rhs_matrix.clone_data())){};

        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix(Matrix<RhsElementType, rhs_row_size, rhs_col_size> &rhs_matrix)
            : matrix_ptr_(std::make_unique<MatrixType>(
                  std::move(*(rhs_matrix.clone_data())))){};

        Matrix(Matrix &&rhs_matrix) = default;

        /// 1 copy
        /// use move it_begin, it_end
        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix(Matrix<RhsElementType, rhs_row_size, rhs_col_size> &&rhs_matrix)
            : matrix_ptr_(std::make_unique<MatrixType>(
                  std::move(*(rhs_matrix.clone_data())))){};

        Matrix &operator=(Matrix &rhs_matrix)
        {
            this->matrix_ptr_ = (std::move(rhs_matrix.clone_data()));
            return *this;
        }

        /// 2 copy
        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix &operator=(Matrix<RhsElementType, rhs_row_size, rhs_col_size> &rhs_matrix)
        {
            this->matrix_ptr_ = std::make_unique<MatrixType>(
                std::move(*(rhs_matrix.clone_data())));
            return *this;
        }

        Matrix &operator=(Matrix &&rhs_matrix) = default;

        /// 2 copy
        /// use move it_begin, it_end
        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix &operator=(Matrix<RhsElementType, rhs_row_size, rhs_col_size> &&rhs_matrix)
        {
            this->matrix_ptr_ = std::make_unique<MatrixType>(
                std::move(*(rhs_matrix.clone_data())));
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
        {
            os << *(matrix.matrix_ptr_);
            return os;
        }

        ElementType &operator()(SizeType row_index, SizeType col_index)
        {
            return (*(this->matrix_ptr_))(
                this->validate_negative_row_index_(row_index),
                this->validate_negative_col_index_(col_index));
        }

        const ElementType &operator()(SizeType row_index, SizeType col_index) const
        {
            return (*(this->matrix_ptr_))(row_index, col_index);
        }

        constexpr bool is_dynamic_matrix()
        {
            return utility::is_declared_dynamic_matrix<templ_row_size,
                                                       templ_col_size>{};
        }

        constexpr bool is_static_matrix()
        {
            return utility::is_declared_static_matrix<templ_row_size,
                                                      templ_col_size>{};
        }

        SizeType row_size() const
        {
            return this->matrix_ptr_->get_row_size_();
        }

        SizeType column_size() const
        {
            return this->matrix_ptr_->get_col_size_();
        }

        auto clone_data() const
        {
            auto copy_ptr = std::make_unique<MatrixType>();
            copy_ptr->data__ = std::move(this->matrix_ptr_->clone_data_());
            if constexpr (utility::is_declared_dynamic_matrix<templ_row_size,
                                                              templ_col_size>{})
                copy_ptr->set_dimensions_(this->row_size(), this->column_size());
            return std::move(copy_ptr);
        }

        auto clone() const
        {
            Matrix<ElementType, templ_row_size, templ_col_size> copy_matrix;
            copy_matrix.matrix_ptr_ = this->clone_data();
            return copy_matrix;
        }

        auto begin() const noexcept { return this->matrix_ptr_->data__.begin(); };

        auto end() const noexcept { return this->matrix_ptr_->data__.end(); };

        auto rbegin() const noexcept { return this->matrix_ptr_->data__.rbegin(); };

        auto rend() const noexcept { return this->matrix_ptr_->data__.rend(); };

        auto cbegin() const noexcept { return this->matrix_ptr_->data__.cbegin(); };

        auto cend() const noexcept { return this->matrix_ptr_->data__.cend(); };

        auto crbegin() const noexcept { return this->matrix_ptr_->data__.crbegin(); };

        auto crend() const noexcept { return this->matrix_ptr_->data__.crend(); };

        Matrix &fill(const ElementType &fill_value = ElementType())
        {
            this->matrix_ptr_->fill_all_element_with_(fill_value);
            return *this;
        }

        Matrix &fill_row(SizeType row_index, const ElementType &fill_value)
        {
            row_index = this->validate_negative_row_index_(row_index);
            this->matrix_ptr_->fill_value_to_row_(row_index, fill_value);
            return *this;
        }

        template <typename SeqContainer1D>
        Matrix &fill_row(SizeType row_index, const SeqContainer1D &rhs_seq_container)
        {
            row_index = this->validate_negative_row_index_(row_index);
            this->matrix_ptr_->copy_data_to_row_(row_index, rhs_seq_container);
            return *this;
        }

        Matrix &fill_column(SizeType col_index, const ElementType &fill_value)
        {
            col_index = this->validate_negative_col_index_(col_index);
            this->matrix_ptr_->fill_value_to_col_(col_index, fill_value);
            return *this;
        }

        template <typename SeqContainer1D>
        Matrix &fill_column(SizeType col_index, const SeqContainer1D &rhs_seq_container)
        {
            col_index = this->validate_negative_col_index_(col_index);
            this->matrix_ptr_->copy_data_to_col_(col_index, rhs_seq_container);
            return *this;
        }

        template <typename SeqContainer1D, typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        append_row(SizeType row_index, const SeqContainer1D &rhs_seq_container)
        {
            row_index = this->validate_negative_append_row_index_(row_index);
            this->matrix_ptr_->insert_row_at_(row_index, rhs_seq_container);
            return *this;
        }

        template <typename SeqContainer1D, typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        append_column(SizeType col_index, const SeqContainer1D &rhs_seq_container)
        {
            col_index = this->validate_negative_append_col_index_(col_index);
            this->matrix_ptr_->insert_col_at_(col_index, rhs_seq_container);
            return *this;
        }

        template <typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        remove_row(SizeType row_index)
        {
            row_index = this->validate_negative_row_index_(row_index);
            this->matrix_ptr_->erase_row_at_(row_index);
            return *this;
        }

        template <typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        remove_column(SizeType col_index)
        {
            col_index = this->validate_negative_col_index_(col_index);
            this->matrix_ptr_->erase_col_at_(col_index);
            return *this;
        }

        template <typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        resize(SizeType new_row_size, SizeType new_col_size)
        {
            this->matrix_ptr_->resize_and_fill_default_(new_row_size, new_col_size);
            return *this;
        }

        template <typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        clear()
        {
            this->matrix_ptr_->clear_data_();
            return *this;
        }
        ///------------------------------------Math-related methods-------------------------------------------------

        Matrix &operator+(const Matrix &rhs_matrix)
        {
            utility::expect(
                this->is_summable(rhs_matrix.row_size(), rhs_matrix.column_size()),
                std::runtime_error("Dimensions mismatch when performing matrix addition."));

            return *this;
        }

        Matrix &operator-(const Matrix &rhs_matrix)
        {
            utility::expect(
                this->is_summable(rhs_matrix.row_size(), rhs_matrix.column_size()),
                std::runtime_error("Dimensions mismatch when performing matrix subtraction."));

            return *this;
        }

        Matrix &operator*(const Matrix &rhs_matrix)
        {
            utility::expect(
                this->is_multipliable(rhs_matrix.row_size(), rhs_matrix.column_size()),
                std::runtime_error("Dimensions mismatch when performing matrix multiplication."));

            return *this;
        }

        Matrix &operator/(const Matrix &rhs_matrix)
        {
            utility::expect(
                this->is_multipliable(rhs_matrix.row_size(), rhs_matrix.column_size()),
                std::runtime_error("Dimensions mismatch when performing matrix division."));

            return *this;
        }

    private:
        std::unique_ptr<MatrixType> matrix_ptr_;

        SizeType validate_negative_row_index_(SizeType row_index) const noexcept
        {
            return row_index < 0 ? this->row_size() + row_index : row_index;
        }

        SizeType validate_negative_col_index_(SizeType col_index) const noexcept
        {
            return col_index < 0 ? this->column_size() + col_index : col_index;
        }

        SizeType validate_negative_append_row_index_(SizeType row_index) const noexcept
        {
            return row_index < 0 ? this->row_size() + row_index + 1 : row_index;
        }

        SizeType validate_negative_append_col_index_(SizeType col_index) const noexcept
        {
            return col_index < 0 ? this->column_size() + col_index + 1 : col_index;
        }

        bool is_multipliable(SizeType rhs_row_size, SizeType rhs_column_size)
        {
            return utility::check_if_multipliable(
                this->row_size(), this->column_size(),
                rhs_row_size, rhs_column_size);
        }

        bool is_summable(SizeType rhs_row_size, SizeType rhs_column_size)
        {
            return utility::check_if_equal_dimensions(
                this->row_size(), this->column_size(),
                rhs_row_size, rhs_column_size);
        }
    };
}

// /// use move it_begin, it_end
// template <typename RhsElementType,
//           SizeType rhs_row_size,
//           SizeType rhs_col_size>
// Matrix(Matrix<RhsElementType, rhs_row_size, rhs_col_size> &&rhs_matrix)
//     : matrix_ptr_(std::make_unique<MatrixType>(
//           std::move(*(rhs_matrix.clone_data()))))
// {
//     if constexpr (utility::is_declared_static_matrix<templ_row_size, templ_col_size>{})
//     {
//         if constexpr (utility::is_declared_static_matrix<rhs_row_size, rhs_col_size>{})
//             static_assert("Matrix dimensions mismatch.");
//         else if (templ_row_size != rhs_matrix.row_size() ||
//                  templ_col_size != rhs_matrix.column_size())
//             throw std::range_error("Matrix dimensions mismatch.");
//         else
//         {
//             this->matrix_ptr_ = std::make_unique<MatrixType>();
//             std::move(rhs_matrix.begin(), rhs_matrix.end(), this->begin());
//         }
//     }
// }

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
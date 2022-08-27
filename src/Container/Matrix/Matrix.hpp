#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "../../Config.hpp"

#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"

#include <memory>

namespace linear_algebra
{
    /// Accept negative indices, static matrices are currently not available
    template <typename ElementType = float,
              long templ_row_size = 0,
              long templ_col_size = 0>
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
        const auto &data() const
        {
            return *(this->matrix_ptr_);
        }

        auto &data()
        {
            return *(this->matrix_ptr_);
        }

        Matrix() : matrix_ptr_(std::make_unique<MatrixType>()){};

#if DEBUG_LIN_ALG
        ~Matrix() noexcept
        {
            std::cout << "At memory address: <" << std::addressof(*this)
                      << ">, an instance of <Matrix>, whose size of " << sizeof(*this)
                      << " bytes and contains a pointer at <" << this->matrix_ptr_.get()
                      << ">, has been destroyed.\n";
        }
#else
        ~Matrix() = default;
#endif

        explicit Matrix(const ElementType &fill_value)
            : matrix_ptr_(std::make_unique<MatrixType>(fill_value)){};

        explicit Matrix(SizeType n_rows,
                        SizeType n_cols,
                        const ElementType &fill_value = ElementType())
            : matrix_ptr_(std::make_unique<MatrixType>(n_rows, n_cols, fill_value)){};

        Matrix(Matrix &rhs_matrix)
            : matrix_ptr_(std::make_unique<MatrixType>(rhs_matrix.data())){};

        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix(Matrix<RhsElementType, rhs_row_size, rhs_col_size>
                   &rhs_matrix)
            : matrix_ptr_(std::make_unique<MatrixType>(rhs_matrix.data())){};

        Matrix(Matrix &&rhs_matrix) = default;

        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix(Matrix<RhsElementType, rhs_row_size, rhs_col_size>
                   &&rhs_matrix)
            : matrix_ptr_(std::make_unique<MatrixType>(
                  std::move(rhs_matrix.data()))){};

        Matrix &operator=(Matrix &rhs_matrix)
        {
            this->matrix_ptr_ = std::make_unique<MatrixType>(
                rhs_matrix.data());
            return *this;
        }

        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix &operator=(Matrix<RhsElementType, rhs_row_size, rhs_col_size>
                              &rhs_matrix)
        {
            this->matrix_ptr_ = std::make_unique<MatrixType>(
                rhs_matrix.data());
            return *this;
        }

        Matrix &operator=(Matrix &&rhs_matrix) = default;

        template <typename RhsElementType,
                  SizeType rhs_row_size,
                  SizeType rhs_col_size>
        Matrix &operator=(Matrix<RhsElementType, rhs_row_size, rhs_col_size>
                              &&rhs_matrix)
        {
            this->matrix_ptr_ = std::make_unique<MatrixType>(
                std::move(rhs_matrix.data()));
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
        {
            os << *(matrix.matrix_ptr_);
            return os;
        }

        ElementType &operator()(SizeType row_index, SizeType col_index)
        {
#if ALLOW_NEGATIVE_INDEX
            return (*(this->matrix_ptr_))(
                this->valid_row_index_(row_index),
                this->valid_col_index(col_index));
#else
            return (*(this->matrix_ptr_))(row_index, col_index);
#endif /* ALLOW_NEGATIVE_INDEX */
        }

        const ElementType &operator()(SizeType row_index, SizeType col_index) const
        {
            return (*(this->matrix_ptr_))(row_index, col_index);
        }

        constexpr bool is_dynamic() noexcept
        {
            return utility::is_declared_dynamic_matrix<templ_row_size,
                                                       templ_col_size>{};
        }

        constexpr bool is_static() noexcept
        {
            return utility::is_declared_static_matrix<templ_row_size,
                                                      templ_col_size>{};
        }

        template <typename ReturnType = SizeType>
        constexpr StaticMatrixMethod<ReturnType>
        row_size() const noexcept
        {
            return templ_row_size;
        }

        template <typename ReturnType = SizeType>
        DynamicMatrixMethod<ReturnType>
        row_size() const noexcept
        {
            return this->matrix_ptr_->get_row_size_();
        }

        template <typename ReturnType = SizeType>
        constexpr StaticMatrixMethod<ReturnType>
        column_size() const noexcept
        {
            return templ_col_size;
        }

        template <typename ReturnType = SizeType>
        DynamicMatrixMethod<ReturnType>
        column_size() const noexcept
        {
            return this->matrix_ptr_->get_col_size_();
        }

        template <typename ReturnType = bool>
        constexpr StaticMatrixMethod<ReturnType>
        is_square() const noexcept
        {
            return templ_row_size == templ_col_size;
        }

        template <typename ReturnType = bool>
        DynamicMatrixMethod<ReturnType>
        is_square() const noexcept
        {
            return this->row_size() == this->column_size();
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

        auto clone()
        {
            return Matrix<ElementType, templ_row_size, templ_col_size>(*this);
        }

        auto begin() const noexcept { return &*(this->matrix_ptr_->data__.begin()); };

        auto end() const noexcept { return &*(this->matrix_ptr_->data__.end()); };

        auto rbegin() const noexcept { return &*(this->matrix_ptr_->data__.rbegin()); };

        auto rend() const noexcept { return &*(this->matrix_ptr_->data__.rend()); };

        auto cbegin() const noexcept { return &*(this->matrix_ptr_->data__.cbegin()); };

        auto cend() const noexcept { return &*(this->matrix_ptr_->data__.cend()); };

        auto crbegin() const noexcept { return &*(this->matrix_ptr_->data__.crbegin()); };

        auto crend() const noexcept { return &*(this->matrix_ptr_->data__.crend()); };

        Matrix &fill(const ElementType &fill_value = ElementType())
        {
            this->matrix_ptr_->fill_all_element_with_(fill_value);
            return *this;
        }

        Matrix &fill_row(SizeType row_index, const ElementType &fill_value)
        {
            row_index = this->valid_row_index_(row_index);
            this->matrix_ptr_->fill_value_to_row_(row_index, fill_value);
            return *this;
        }

        template <typename SeqContainer1D>
        Matrix &fill_row(SizeType row_index, const SeqContainer1D &rhs_seq_container)
        {
            row_index = this->valid_row_index_(row_index);
            this->matrix_ptr_->copy_data_to_row_(row_index, rhs_seq_container);
            return *this;
        }

        Matrix &fill_column(SizeType col_index, const ElementType &fill_value)
        {
            col_index = this->valid_col_index(col_index);
            this->matrix_ptr_->fill_value_to_col_(col_index, fill_value);
            return *this;
        }

        template <typename SeqContainer1D>
        Matrix &fill_column(SizeType col_index, const SeqContainer1D &rhs_seq_container)
        {
            col_index = this->valid_col_index(col_index);
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
            row_index = this->valid_row_index_(row_index);
            this->matrix_ptr_->erase_row_at_(row_index);
            return *this;
        }

        template <typename ReturnType = Matrix &>
        DynamicMatrixMethod<ReturnType>
        remove_column(SizeType col_index)
        {
            col_index = this->valid_col_index(col_index);
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

#if ENABLE_MATRIX_MATH_FUNCTIONS
        /// ElementType must have a defined operator+
        template <typename RhsMatrixType>
        Matrix operator+(const RhsMatrixType &rhs_matrix)
        {
            const SizeType rhs_row_size = rhs_matrix.row_size();
            const SizeType rhs_col_size = rhs_matrix.column_size();

            utility::expect(
                this->is_summable(rhs_row_size, rhs_col_size),
                std::runtime_error(
                    "Dimensions mismatch when performing matrix addition."));

            Matrix<ElementType> result(rhs_row_size, rhs_col_size);
            auto it1 = this->begin();
            auto it2 = rhs_matrix.begin();
            auto it_end1 = this->end();
            auto it_end2 = rhs_matrix.end();
            auto res_it = result.begin();
            auto res_it_end = result.end();

            SizeType i = 0;
            while ((res_it + i) != res_it_end)
            {
                *(res_it + i) = *(it1 + i) + *(it2 + i);
                i++;
            }

            return result;
        }

        /// ElementType must have a defined operator-
        template <typename RhsMatrixType>
        Matrix operator-(const RhsMatrixType &rhs_matrix)
        {
            const SizeType rhs_row_size = rhs_matrix.row_size();
            const SizeType rhs_col_size = rhs_matrix.column_size();

            utility::expect(
                this->is_summable(rhs_row_size, rhs_col_size),
                std::runtime_error(
                    "Dimensions mismatch when performing matrix subtraction."));

            Matrix<ElementType> result(rhs_row_size, rhs_col_size);
            auto it1 = this->begin();
            auto it2 = rhs_matrix.begin();
            auto it_end1 = this->end();
            auto it_end2 = rhs_matrix.end();
            auto res_it = result.begin();
            auto res_it_end = result.end();

            SizeType i = 0;
            while ((res_it + i) != res_it_end)
            {
                *(res_it + i) = *(it1 + i) - *(it2 + i);
                i++;
            }

            return result;
        }

        /// ElementType must have a defined operator*
        template <typename RhsMatrixType>
        Matrix operator*(const RhsMatrixType &rhs_matrix)
        {
            const SizeType row_size = this->row_size();
            const SizeType col_size = this->column_size();
            const SizeType rhs_row_size = rhs_matrix.row_size();
            const SizeType rhs_col_size = rhs_matrix.column_size();

            utility::expect(
                this->is_multipliable(rhs_row_size),
                std::runtime_error(
                    "Dimensions mismatch when performing matrix multiplication."));

            Matrix<ElementType> result(row_size, rhs_col_size);

            auto it1 = this->begin();
            auto it2 = rhs_matrix.begin();
            auto it_end1 = this->end();
            auto it_end2 = rhs_matrix.end();
            auto res_it = result.begin();
            auto res_it_end = result.end();

            for (SizeType i = 0; i < row_size; i++)
                for (SizeType j = 0; j < rhs_col_size; j++)
                    for (SizeType k = 0; k < rhs_row_size; k++)
                        *(res_it + i * rhs_col_size + j) +=
                            (*(it1 + i * rhs_row_size + k)) *
                            (*(it2 + k * rhs_col_size + j));

            return result;
        }

        /// ElementType must have a defined operator*
        Matrix operator*(const ElementType &scalar)
        {
            // if (scalar == 1)
            //     return (*this).clone();

            static_assert(std::is_arithmetic_v<ElementType>,
                          "ElementType must be arithmetic type.");

            const SizeType row_size = this->row_size();
            const SizeType col_size = this->column_size();

            Matrix<ElementType> result(row_size, col_size);

            if (scalar == 0)
                return result;

            auto it = this->begin();
            auto it_end = this->end();
            auto res_it = result.begin();
            auto res_it_end = result.end();

            SizeType i = 0;
            while ((res_it + i) != res_it_end)
            {
                *(res_it + i) = (*(it + i)) * (scalar);
                i++;
            }

            return result;
        }

        bool is_singular()
        {
            if (this->is_square() == false)
                return false;
            return true;
        }

        ElementType det()
        {
            static_assert(std::is_arithmetic_v<ElementType>,
                          "Scalar must be of any arithmetic type.");

            utility::expect(this->is_square_matrix() == true,
                            std::runtime_error(
                                "Taking power of a non-square matrix is not allowed."));

            return ElementType();
        }

        Matrix identity()
        {
            /// exception: std::complex
            static_assert(std::is_arithmetic_v<ElementType>,
                          "ElementType must be of any arithmetic type.");

            utility::expect(this->is_square_matrix() == true,
                            std::runtime_error(
                                "Cannot find an identity matrix of a non-square matrix."));

            SizeType row_size = this->row_size();
            Matrix<ElementType> identity_matrix(row_size, row_size);
            while (row_size--)
                identity_matrix(row_size, row_size) = 1;
            return identity_matrix;
        }

        Matrix inverse()
        {
            return *this;
        }

        Matrix sub(SizeType rm_row_index, SizeType rm_col_index)
        {
            Matrix<ElementType> sub_matrix(std::move(this->clone()));
            sub_matrix.remove_row(rm_row_index);
            sub_matrix.remove_column(rm_col_index);
            return sub_matrix;
        }

        /// For testing purpose only. Actual algorithm does not repeatedly perform multiplication.
        template <typename ScalarType>
        Matrix pow(ScalarType scalar)
        {
            static_assert(std::is_arithmetic_v<ScalarType>,
                          "Scalar must be of any arithmetic type.");

            utility::expect(this->is_square_matrix() == true,
                            std::runtime_error(
                                "Taking power of a non-square matrix is not allowed."));

            if (scalar == 0)
                return this->identity();

            if (scalar == 1)
                return *this;

            if (scalar == -1)
                return this->inverse();

            const SizeType row_size = this->row_size();
            const SizeType col_size = this->column_size();
            Matrix<ElementType> result(*this);

            for (SizeType i = 0; i < scalar - 1; i++)
                result = std::move(result * result);
            return result;
        }

        /// Double-transposing on one matrix is not available.
        Matrix<ElementType> transpose()
        {
            SizeType t_row_size = this->column_size();
            SizeType t_col_size = this->row_size();

            Matrix<ElementType> result(t_row_size, t_col_size);
            for (SizeType i = 0; i < t_row_size; i++)
                for (SizeType j = 0; j < t_row_size; j++)
                    result(i, j) = (*this)(j, i);
            return result;
        }

        template <typename ScalarType>
        Matrix &row_addition(SizeType row_index, ScalarType value)
        {
            static_assert(std::is_arithmetic_v<ScalarType>,
                          "Scalar must be of any arithmetic type.");

            row_index = this->valid_row_index_(row_index);

            SizeType row_size = this->row_size();
            SizeType col_size = this->column_size();

            for (SizeType i = 0; i < col_size; i++)
                *(this->begin() + row_index * col_size + i) += value;

            return *this;
        }

        template <typename ScalarType>
        Matrix &row_multiplication(SizeType row_index, ScalarType value)
        {
            static_assert(std::is_arithmetic_v<ScalarType>,
                          "Scalar must be of any arithmetic type.");

            row_index = this->valid_row_index_(row_index);

            SizeType row_size = this->row_size();
            SizeType col_size = this->column_size();

            for (SizeType i = 0; i < col_size; i++)
                *(this->begin() + row_index * col_size + i) *= value;

            return *this;
        }

        Matrix &row_swap(SizeType row_index1, SizeType row_index2)
        {

            row_index1 = this->valid_row_index_(row_index1);
            row_index2 = this->valid_row_index_(row_index2);

            SizeType row_size = this->row_size();
            SizeType col_size = this->column_size();

            for (SizeType i = 0; i < col_size; i++)
                std::swap(*(this->begin() + row_index1 * col_size + i),
                          *(this->begin() + row_index2 * col_size + i));

            return *this;
        }
#endif /* MATRIX_MATH_FUNCTIONS */

    private:
        std::unique_ptr<MatrixType> matrix_ptr_;

        /// Need to check if the returned row_index is still less than 0.
        SizeType valid_row_index_(SizeType row_index) const
        {
#if ALLOW_NEGATIVE_INDEX
            if (row_index < 0)
                row_index += this->row_size();
#endif /* ALLOW_NEGATIVE_INDEX */
            utility::expect(row_index >= 0 && row_index < this->row_size(),
                            std::range_error("Row index out of range."));
            return row_index;
        }

        SizeType valid_col_index(SizeType col_index) const
        {
#if ALLOW_NEGATIVE_INDEX
            if (col_index < 0)
                col_index += this->column_size();
#endif /* ALLOW_NEGATIVE_INDEX */
            utility::expect(col_index >= 0 && col_index < this->column_size(),
                            std::range_error("Column index out of range."));
            return col_index;
        }

        SizeType validate_negative_append_row_index_(SizeType row_index) const
        {
            return row_index < 0 ? this->row_size() + row_index + 1 : row_index;
        }

        SizeType validate_negative_append_col_index_(SizeType col_index) const
        {
            return col_index < 0 ? this->column_size() + col_index + 1 : col_index;
        }

        bool is_multipliable(SizeType rhs_row_size) const noexcept
        {
            return this->column_size() == rhs_row_size;
        }

        bool is_summable(SizeType rhs_row_size, SizeType rhs_column_size) const noexcept
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
#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"

// #include <type_traits>
// #include <memory>

// template <typename ElementType, size_t declared_row_size = 0, size_t declared_col_size = 0>
// struct is_static_matrix_:std::is_same<>;

// template <typename T>
// struct is_static_matrix_<>

template <typename ElementType,
          size_t declared_row_size = 0,
          size_t declared_col_size = 0>
class Matrix
{
    typedef std::conditional_t<
        __zz_utils__::is_declared_static_matrix_v(declared_row_size, declared_col_size),
        StaticMatrix<ElementType, declared_row_size, declared_col_size>,
        DynamicMatrix<ElementType>>
        MatrixType;

public:
    std::unique_ptr<MatrixType> matrix_ptr_;

public:
    constexpr bool is_static_matrix_v()
    {
        return std::is_same_v<MatrixType,
                              StaticMatrix<ElementType, declared_row_size, declared_col_size>>;
    }

    constexpr bool is_dynamic_matrix_v()
    {
        return std::is_same_v<MatrixType,
                              DynamicMatrix<ElementType>>;
    }

    Matrix() : matrix_ptr_(std::make_unique<MatrixType>()){};

    // for static matrices only
    explicit Matrix(ElementType fill_value)
        : matrix_ptr_(std::make_unique<MatrixType>(fill_value)){};

    // for dynamic matrices only
    explicit Matrix(size_t row_size, size_t col_size, ElementType fill_value = 0)
        : matrix_ptr_(std::make_unique<MatrixType>(row_size, col_size, fill_value)){};

    Matrix(Matrix &r_matrix)
        : matrix_ptr_(std::make_unique<MatrixType>(*(r_matrix.matrix_ptr_))){};

    Matrix(Matrix &&r_matrix) = default;

    Matrix &operator=(Matrix &r_matrix)
    {
        this->matrix_ptr_ = std::make_unique<MatrixType>(*(r_matrix.matrix_ptr_));
        return *this;
    }

    Matrix &operator=(Matrix &&r_matrix) = default;

    template <typename RMatrixType>
    Matrix(RMatrixType &r_matrix)
        : matrix_ptr_(std::make_unique<MatrixType>(*(r_matrix.matrix_ptr_))){};

    template <typename RMatrixType>
    Matrix(RMatrixType &&r_matrix) : matrix_ptr_(std::move(r_matrix.matrix_ptr_)){};

    template <typename RMatrixType>
    Matrix &operator=(RMatrixType &r_matrix)
    {
        this->matrix_ptr_ = std::make_unique<MatrixType>(*(r_matrix.matrix_ptr_));
        return *this;
    }

    template <typename RMatrixType>
    Matrix& operator=(RMatrixType &&r_matrix)
    {
        matrix_ptr_ = std::move(r_matrix.matrix_ptr_);
        return *this;
    }

    size_t row_size() const
    {
        return this->matrix_ptr_->row_size();
    }

    size_t column_size() const
    {
        return this->matrix_ptr_->column_size();
    }

    auto &copy_data() const
    {
        return this->matrix_ptr_->copy_data();
    }

    constexpr ElementType &at(size_t row_index, size_t col_index)
    {
        return this->matrix_ptr_->access_element_at(row_index, col_index);
    }

    void print() { this->matrix_ptr_->display_data(); }
};

#endif /* LIN_ALG_CONTAINER_MATRIX_HPP */
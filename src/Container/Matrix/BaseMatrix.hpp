#ifndef BASEMATRIX_HPP
#define BASEMATRIX_HPP

// #include "../../Utils/Utils.hpp"
#include "MatrixHelper.hpp"

#include <vector>
#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <algorithm>

// polymorphic copy construction
// class AbstractMatrix
// {
// public:
//     virtual ~AbstractMatrix() = default;
//     // virtual std::unique_ptr<AbstractMatrix> clone() const = 0;
// };

template <typename ElementType,
          size_t declared_row_size = 0,
          size_t declared_col_size = 0>
class BaseMatrix
{
protected:
    typedef std::conditional_t<
        is_declared_static_matrix_v(declared_row_size, declared_col_size),
        std::array<ElementType, sq_mat_size(declared_row_size, declared_col_size)>,
        std::vector<ElementType>>
        DataType;
    DataType data_;

    size_t n_rows_;
    size_t n_cols_;

    //--------------------------Initialization Section Start------------------------------
    // declare this function as a template function so that
    // std::enable_if::type = T
    // T = void is for the compiler to deduce T
    template <typename T = void>
    typename std::enable_if_t<
        is_declared_static_matrix_v(declared_row_size, declared_col_size), T>
    default_fill_initialize(ElementType fill_value = 0)
    {
        data_.fill(fill_value);
        this->n_rows_ = declared_row_size;
        this->n_cols_ = declared_col_size;
    }

    template <typename T = void>
    typename std::enable_if_t<
        !is_declared_static_matrix_v(declared_row_size, declared_col_size), T>
    default_fill_initialize(std::size_t row_size = 0,
                            std::size_t col_size = 0,
                            ElementType fill_value = 0)
    {
        data_.resize(row_size * col_size, fill_value);
        this->n_rows_ = declared_row_size;
        this->n_cols_ = declared_col_size;
    }

    template <class RMatrixType>
    void copy_initialize(const RMatrixType &r_matrix)
    {
        this->n_rows_ = r_matrix->n_rows_;
        this->n_cols_ = r_matrix->n_cols_;
        this->data_.resize(r_matrix->data_.size());
        std::copy(r_matrix->data_.begin(), r_matrix->data_.end(), data_.begin());
    }

    template <class RMatrixType>
    void move_initialize(RMatrixType &&r_matrix)
    {
        this->n_rows_ = r_matrix->n_rows_;
        this->n_cols_ = r_matrix->n_cols_;
        this->data_.resize(r_matrix->data_.size());
        std::move(r_matrix->data_.begin(), r_matrix->data_.end(), data_.begin());
    }

    //--------------------------Initialization Section End-------------------------------------
    //--------------------------Type Traits Section Start--------------------------------------

    template <typename TargetType>
    bool is_1d_c_array_v(const TargetType &target)
    {
        return std::is_array_v<TargetType> && std::rank_v<TargetType> == 1;
    }

    //--------------------------Type Traits Section End----------------------------------------
    //--------------------------Functions Section Start----------------------------------------
    // (not implemented yet) Append: mode = 0 <=> normal, mode = 1 <=> lazy, mode = 2 <=> force
    
    // Assign-values functions for both static matrices and dynamic matrices

    
    // Append functions for dynamic matrices
    template <typename ReturnType = void, typename TargetType>
    typename std::enable_if_t<
        !is_declared_static_matrix_v(declared_row_size, declared_col_size),
        ReturnType>
    append_1d_c_array_to_rows(const TargetType &c_array, size_t row_index, int append_mode = 0)
    {
        try
        {
            size_t len = sizeof(c_array) / sizeof(c_array[0]);

            if (len == 0)
                return;
            if (len != this->n_cols_)
                throw;

            this->data_.insert(this->data_.begin(), row_index * this->n_cols_, 0);
            for (size_t i = 0; i < len; i++)
                this->data_[row_index * this->n_cols_ + i] = c_array[i];
        }
        catch (...)
        {
            std::cerr << "An error has occurred at <append_1d_c_array_to_rows>.\n";
        }
    }

    template <typename ReturnType = void, typename TargetType>
    typename std::enable_if_t<
        !is_declared_static_matrix_v(declared_row_size, declared_col_size),
        ReturnType>
    append_1d_c_array_to_cols(const TargetType &c_array, size_t col_index)
    {
        try
        {
            size_t len = sizeof(c_array) / sizeof(c_array[0]);

            if (len == 0)
                return;
            if (len != this->n_rows_)
                throw;

            this->data_.resize(this->data_.size() + len);
            ElementType temp;
            for (size_t i = col_index, j = 0; i < this->data_.size(), j < len; i++)
            {
                if (i % col_index == 0)
                {
                    ElementType temp = this->data_[i];
                    this->data_[i] = c_array[j];
                    j++;
                }
                else 
                    std::swap(this->data_[i], temp)
            }
        }
        catch (...)
        {
            std::cerr << "An error has occurred at <append_1d_c_array_to_cols>.\n";
        }
    }

    template <typename T>
    void insert_1d_container(const T &target, size_t row_size, size_t col_size)
    {
        return;
    }

    //--------------------------Functions Section End------------------------------------------

public:
    // virtual ~BaseMatrix() = default;
    // virtual std::unique_ptr<BaseMatrix> clone() const = 0;
};

// use enable_if to enable specialized functionalities for square matrices

#endif /* BASEMATRIX_HPP */
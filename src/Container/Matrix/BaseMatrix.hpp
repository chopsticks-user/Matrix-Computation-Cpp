#ifndef BASEMATRIX_HPP
#define BASEMATRIX_HPP

#include "../../Utils/Utils.hpp"

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
//     virtual std::unique_ptr<AbstractMatrix> clone() const = 0;
// };

template <typename ElementType,
          size_t declared_row_size = 0,
          size_t declared_col_size = 0>
class BaseMatrix
{
protected:
    typedef std::conditional_t<
        __zz_utils__::is_declared_static_matrix_v(declared_row_size, declared_col_size),
        std::array<ElementType, __zz_utils__::sq_mat_size(declared_row_size, declared_col_size)>,
        std::vector<ElementType>>
        DataType;
    DataType data_;

    size_t n_rows_;
    size_t n_cols_;
//--------------------------Initialization Section Start------------------------------
    
    // declare this function as a template function so that std::enable_if::type = T, 
    // T = void is for the compiler to deduce T
    template <typename T = void>
    typename std::enable_if_t<
        __zz_utils__::is_declared_static_matrix_v(declared_row_size, declared_col_size), T>
    default_fill_initialize(ElementType fill_value = 0)
    {
        data_.fill(fill_value);
        this->n_rows_ = declared_row_size;
        this->n_cols_ = declared_col_size == 0
                            ? declared_row_size
                            : declared_col_size;
    }

    template <typename T = void>
    typename std::enable_if_t<
        !__zz_utils__::is_declared_static_matrix_v(declared_row_size, declared_col_size), T>
    default_fill_initialize(size_t row_size = 0,
                            size_t col_size = 0,
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
//--------------------------Functions Section Start----------------------------------------

    void fill_value_to_row(ElementType fill_value, size_t row_index)
    {
        // std::fill();
    }

    void fill_value_to_col();

    void replace_row_with();

    void replace_col_with();

    void add_new_row();

    void add_new_col();

    void remove_row();

    void remove_col();

    void reset_data();

    void change_dims();
//--------------------------Functions Section End------------------------------------------

public:
    ElementType &access_element_at(size_t row_index, size_t col_index)
    {
        return this->data_[row_index * this->n_cols_ + col_index];
    }

    void display_data() noexcept
    {
        std::cout << "[";
        for (size_t i = 0; i < this->n_rows_; i++)
        {
            std::cout << "[";
            if (this->data_.size() / this->n_rows_ >= 1)
                std::cout << this->data_[i * this->n_cols_];
            for (size_t j = 1; j < this->n_cols_; j++)
                std::cout << ", " << this->access_element_at(i, j);
            std::cout << "]";
            if (i < this->n_rows_ - 1)
                std::cout << "\n ";
        }
        std::cout << "]\n";
    }
};

// use enable_if to enable specialized functionalities for square matrices
// (not implemented yet) Append: mode = 0 <=> normal, mode = 1 <=> lazy, mode = 2 <=> force
#endif /* BASEMATRIX_HPP */

// size_t len = sizeof(c_array) / sizeof(c_array[0]);

// if (len == 0)
//     return;
// if (len != this->n_rows_)
//     throw;

// this->data_.resize(this->data_.size() + len);
// ElementType temp;
// for (size_t i = col_index, j = 0; i < this->data_.size(), j < len; i++)
// {
//     if (i % col_index == 0)
//     {
//         ElementType temp = this->data_[i];
//         this->data_[i] = c_array[j];
//         j++;
//     }
//     else
//         std::swap(this->data_[i], temp);
// }
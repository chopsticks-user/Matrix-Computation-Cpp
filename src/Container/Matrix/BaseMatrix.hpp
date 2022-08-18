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

template <typename ElementType, size_t row_size = 0, size_t col_size = 0>
class BaseMatrix
{
protected:
    // declare this function as a template function so that
    // std::enable_if::type = T
    // T = void is for the compiler to deduce T
    template <typename T = void>
    typename std::enable_if_t<is_declared_static_matrix_v(row_size, col_size), T>
    default_fill_initialize(ElementType fill_value = 0)
    { data_.fill(fill_value); }

    template <typename T = void>
    typename std::enable_if_t<!is_declared_static_matrix_v(row_size, col_size), T>
    default_fill_initialize(std::size_t inp_row_size = 0, std::size_t inp_col_size = 0, ElementType fill_value = 0)
    { data_.resize(inp_row_size * inp_col_size, fill_value); }

    template <class RMatrixType>
    void copy_initialize(const RMatrixType& r_matrix)
    { std::copy(r_matrix->data_.begin(), r_matrix->data_.end(), data_.begin()); }

    template <class RMatrixType>
    void move_initialize(RMatrixType&& r_matrix)
    { std::move(r_matrix->data_.begin(), r_matrix->data_.end(), data_.begin()); }
    
public:
    typedef std::conditional_t<is_declared_static_matrix_v(row_size, col_size),
                               std::array<ElementType, sq_mat_size(row_size, col_size)>,
                               std::vector<ElementType>>
        DataType;
    DataType data_;

    // virtual ~BaseMatrix() = default;
    // virtual std::unique_ptr<BaseMatrix> clone() const = 0;
};

// use enable_if to enable specialized functionalities for square matrices

#endif /* BASEMATRIX_HPP */
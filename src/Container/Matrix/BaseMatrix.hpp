#ifndef N3K0_CONTAINER_MATRIX_BASEMATRIX_HPP
#define N3K0_CONTAINER_MATRIX_BASEMATRIX_HPP

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


template <typename ElementType, std::size_t row_size = 0, std::size_t col_size = 0>
struct BaseMatrix
{
    constexpr bool is_static_matrix_v() { return row_size != 0 || col_size != 0; };

    constexpr auto fix_size(size_t r_size, size_t c_size)
    { return c_size ? r_size * r_size : r_size * c_size; }

    typedef std::conditional_t<row_size != 0 || col_size != 0,
                               std::array<ElementType, col_size != 0 ? row_size * col_size : row_size * row_size>,
                               std::vector<ElementType>>
        DataType;
    DataType data_;

    // declare this function as a template function so that
    // std::enable_if::type = T
    // T = void is for the compiler to deduce T
    template <typename T = void>
    typename std::enable_if_t<row_size != 0 || col_size != 0, T>
    default_fill_initialize(ElementType fill_value = 0)
    { data_.fill(fill_value); }

    template <typename T = void>
    typename std::enable_if_t<row_size == 0 && col_size == 0, T>
    default_fill_initialize(std::size_t inp_row_size = 0, std::size_t inp_col_size = 0, ElementType fill_value = 0)
    { data_.resize(inp_row_size * inp_col_size, fill_value); }

    template <class RMatrixType>
    void copy_initialize(const RMatrixType& r_matrix)
    { std::copy(r_matrix.data_.begin(), r_matrix.data_.end(), data_.begin()); }

    template <class RMatrixType>
    void move_initialize(RMatrixType&& r_matrix)
    { std::move(r_matrix.data_.begin(), r_matrix.data_.end(), data_.begin()); }
};

// use enable_if to enable specialized functionalities for square matrices

#endif /* N3KO_CONTAINER_MATRIX_BASEMATRIX_HPP */
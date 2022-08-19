#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "../../Utils/Utils.hpp"
#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"
#include "BaseMatrix.hpp"
#include "MatrixHelper.hpp"
#include <type_traits>

#include <memory>

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
        is_declared_static_matrix_v(declared_row_size, declared_col_size),
        StaticMatrix<ElementType, declared_row_size, declared_col_size>,
        DynamicMatrix<ElementType>>
        MatrixType;

private:
    std::shared_ptr<MatrixType> data_;

public:
    static const int a = 0;
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

    Matrix() : data_(std::make_shared<MatrixType>()){};

    // template<std::enable_if_t<is_declared_static_matrix_v(declared_row_size, declared_col_size), bool> = true>
    // Matrix(ElementType fill_value = 0)
    // { std::cout<<"e"; }

    // for static matrices only
    Matrix(ElementType fill_value)
        : data_(std::make_shared<MatrixType>(fill_value)){};

    // for dynamic matrices only
    Matrix(size_t row_size, size_t col_size, ElementType fill_value = 0)
        : data_(std::make_shared<MatrixType>(row_size, col_size, fill_value)){};

    template <typename RMatrixType>
    Matrix(const RMatrixType &r_matrix)
        : data_(std::make_shared<MatrixType>(r_matrix.data_)){};

    template <typename RMatrixType>
    Matrix(RMatrixType &&r_matrix) : data_(std::move(r_matrix.data_)){};
};

#endif /* LIN_ALG_CONTAINER_MATRIX_HPP */
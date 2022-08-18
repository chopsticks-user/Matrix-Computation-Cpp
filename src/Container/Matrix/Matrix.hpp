#ifndef LIN_ALG_CONTAINER_MATRIX_HPP
#define LIN_ALG_CONTAINER_MATRIX_HPP

#include "../../Utils/Utils.hpp"
#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"
#include "BaseMatrix.hpp"
#include "MatrixHelper.hpp"
#include <type_traits>

#include <memory>

template <typename ElementType, size_t row_size = 0, size_t col_size = 0>
class Matrix
{
    typedef std::conditional_t<is_declared_static_matrix_v(row_size, col_size),
                               StaticMatrix<ElementType, row_size, col_size>,
                               DynamicMatrix<ElementType>>
        MatrixType;

private:
    std::shared_ptr<MatrixType> data_;

public:
    constexpr bool is_static_matrix_v()
    {
        return std::is_same_v<MatrixType,
                              StaticMatrix<ElementType, row_size, col_size>>;
    }

    Matrix() : data_(std::make_shared<MatrixType>()){};

    template <typename RMatrixType>
    Matrix(const RMatrixType &r_matrix)
        : data_(std::make_shared<MatrixType>(r_matrix.data_))
    {
        std::cout << "copy \n"
                  << std::addressof(r_matrix.data_) << '\n';
    }

    template <typename RMatrixType>
    Matrix(RMatrixType &&r_matrix) : data_(std::move(r_matrix.data_))
    {
    }
};

#endif /* LIN_ALG_CONTAINER_MATRIX_HPP */
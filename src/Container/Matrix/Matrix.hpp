#ifndef LINEAR_ALGEBRA_CONTAINER_MATRIX_HPP
#define LINEAR_ALGEBRA_MATRIX_MATRIX_HPP

#include "DynamicMatrix.hpp"
#include "StaticMatrix.hpp"
#include "BaseMatrix.hpp"
#include <memory>

template <typename ElementType, size_t row_size = 0, size_t col_size = 0>
class Matrix
{
private:
    static constexpr bool is_declared_static_matrix_v(size_t r_sz, size_t c_sz)
    {
        return r_sz != 0 || c_sz != 0;
    };

    static constexpr size_t sq_mat_size(size_t r_sz, size_t c_sz)
    {
        return c_sz == 0 ? r_sz * r_sz : r_sz * c_sz;
    }

public:
    typedef std::conditional_t<is_declared_static_matrix_v(row_size, col_size),
                               StaticMatrix<ElementType, row_size, col_size>,
                               DynamicMatrix<ElementType>>
        MatrixType;
    std::unique_ptr<MatrixType> data_;
    // Matrix() = default;
};

#endif /* LINEAR_ALGEBRA_CONTAINER_MATRIX_H */
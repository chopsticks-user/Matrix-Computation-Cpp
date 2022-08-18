#ifndef LINEAR_ALGEBRA_CONTAINER_MATRIX_DYNAMICMATRIX_HPP
#define LINEAR_ALGEBRA_CONTAINER_MATRIX_DYNAMICMATRIX_HPP

#include "BaseMatrix.hpp"

template <typename ElementType>
class DynamicMatrix : public BaseMatrix<ElementType>
{
    typedef BaseMatrix<ElementType> Base;

private:
    // using Base::default_fill_initialize();

public:
    DynamicMatrix() = default;

    DynamicMatrix(std::size_t sq_sz)
    { this->default_fill_initialize(sq_sz, sq_sz); }

    DynamicMatrix(std::size_t r_size, std::size_t c_size, ElementType value = 0)
    { this->default_fill_initialize(r_sz, c_sz, value); }
};

#endif /* LINEAR_ALGEBRA_CONTAINER_MATRIX_DYNAMICMATRIX_HPP */
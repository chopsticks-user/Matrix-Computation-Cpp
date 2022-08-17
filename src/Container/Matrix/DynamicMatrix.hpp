#ifndef N3K0_CONTAINER_MATRIX_DYNAMICMATRIX_HPP
#define N3K0_CONTAINER_MATRIX_DYNAMICMATRIX_HPP

#include "BaseMatrix.hpp"

template <typename ElementType>
class DynamicMatrix : public BaseMatrix<ElementType>
{
    typedef BaseMatrix<ElementType> Base;

private:
    // using Base::default_fill_initialize();

public:
    DynamicMatrix() = default;

    DynamicMatrix(std::size_t sq_size)
    { this->default_fill_initialize(sq_size, sq_size); }

    DynamicMatrix(std::size_t r_size, std::size_t c_size, ElementType value = 0)
    { this->default_fill_initialize(r_size, c_size, value); }
};

#endif /* N3KO_CONTAINER_MATRIX_DYNAMICMATRIX_HPP */
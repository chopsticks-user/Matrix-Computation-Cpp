#ifndef N3K0_CONTAINER_MATRIX_STATICMATRIX_HPP
#define N3K0_CONTAINER_MATRIX_STATICMATRIX_HPP

#include "BaseMatrix.hpp"

template <typename ElementType, std::size_t row_size = 0, std::size_t col_size = 0>
class StaticMatrix : public BaseMatrix<ElementType, row_size, col_size>
{
    typedef BaseMatrix<ElementType, row_size, col_size> Base;

public:
    StaticMatrix()
    { this->default_fill_initialize(); }

    StaticMatrix(ElementType value)
    { this->default_fill_initialize(value); }
};

#endif /* N3KO_CONTAINER_MATRIX_STATICMATRIX_HPP */
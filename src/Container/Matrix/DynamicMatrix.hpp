#ifndef LINEAR_ALGEBRA_CONTAINER_MATRIX_DYNAMICMATRIX_HPP
#define LINEAR_ALGEBRA_CONTAINER_MATRIX_DYNAMICMATRIX_HPP

#include "BaseMatrix.hpp"

template <typename ElementType>
class DynamicMatrix : public BaseMatrix<ElementType>
{
    typedef BaseMatrix<ElementType> Base;

private:
public:
    DynamicMatrix() = default;

    DynamicMatrix(std::size_t sq_sz)
    {
        this->default_fill_initialize(sq_sz, sq_sz);
    }

    DynamicMatrix(std::size_t r_sz, std::size_t c_sz, ElementType value = 0)
    {
        this->default_fill_initialize(r_sz, c_sz, value);
    }

    template <class RMatrixType>
    DynamicMatrix(const RMatrixType &r_matrix)
    {
        std::cout << std::addressof(r_matrix) << '\n';
        std::cout << "copy\n";
        this->data_.resize(r_matrix->data_.size());
        this->copy_initialize(r_matrix);
    }

    // template <class RMatrixType>
    // DynamicMatrix(RMatrixType&& r_matrix)
    // {
    //     std::cout<<"move\n";
    //     this->data_.resize(r_matrix->data_.size());
    //     this->move_initialize(r_matrix);
    // }
};

#endif /* LINEAR_ALGEBRA_CONTAINER_MATRIX_DYNAMICMATRIX_HPP */
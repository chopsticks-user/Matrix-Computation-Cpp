#ifndef LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP
#define LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP

#include "BaseMatrix.hpp"

template <typename ElementType>
class DynamicMatrix : public BaseMatrix<ElementType>
{
    typedef BaseMatrix<ElementType> Base;

private:


public:
    DynamicMatrix() = default;

    ~DynamicMatrix() = default;

    // virtual std::unique_ptr<Base> clone() const override
    // { return std::make_unique<DynamicMatrix>(*this); }

    // Matrix<int>(5) --> M<5x5>
    DynamicMatrix(std::size_t sq_sz)
    { this->default_fill_initialize(sq_sz, sq_sz); }

    // Matrix<int>(5, 6, 7) --> M<5x6>, ∀ M[i, j] = 7
    // Matrix<int>(5, 6) --> M<5x6>, ∀ M[i, j] = 0
    DynamicMatrix(std::size_t r_sz, std::size_t c_sz, ElementType init_value = 0)
    { this->default_fill_initialize(r_sz, c_sz, init_value); }

    // copy constructor + copy assignment, implicitly
    template <class RMatrixType>
    DynamicMatrix(const RMatrixType &r_matrix)
    {
        std::cout << std::addressof(r_matrix) << '\n';
        std::cout << "copy\n";
        this->data_.resize(r_matrix->data_.size());
        this->copy_initialize(r_matrix);
    }

    // move constructor + move assignment, implicitly
    template <class RMatrixType>
    DynamicMatrix(RMatrixType&& r_matrix)
    {
        std::cout<<"move\n";
        this->data_.resize(r_matrix->data_.size());
        this->move_initialize(r_matrix);
    }
};

#endif /* LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP */
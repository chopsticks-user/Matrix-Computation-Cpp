#ifndef LIN_ALG_CONTAINER_STATIC_MATRIX_HPP
#define LIN_ALG_CONTAINER_STATIC_MATRIX_HPP

#include "BaseMatrix.hpp"

template <typename ElementType,
          size_t declared_row_size = 0,
          size_t declared_col_size = 0>
class StaticMatrix : public BaseMatrix<ElementType,
                                       declared_row_size,
                                       declared_col_size>
{
    typedef BaseMatrix<ElementType, declared_row_size, declared_col_size> Base;

public:
    // virtual std::unique_ptr<Base> clone() const override
    // { return std::make_unique<StaticMatrix>(*this); }

    ~StaticMatrix() = default;

    // Matrix<int, 5, 6> --> M<5x6>, ∀ M[i, j] = 0
    StaticMatrix()
    {
        this->default_fill_initialize();
    }

    // Matrix<int, 5, 6>(7) --> M<5x6>, ∀ M[i, j] = 7
    explicit StaticMatrix(ElementType value)
    {
        this->default_fill_initialize(value);
    }

    // copy constructor + copy assignment, implicitly
    template <class RMatrixType>
    StaticMatrix(const RMatrixType &r_matrix)
    {
        this->copy_initialize(r_matrix);
    } // exceptions

    template <class RMatrixType>
    StaticMatrix(RMatrixType &&r_matrix)
    {
        this->move_initialize(r_matrix);
    } // exceptions
//---------------------------------------------------------------------------------------

    void fill_row(size_t row_index, ElementType fill_value)
    {
        // assign_row_value(row_index, ElementType fill_value);
    }

    void fill_col(size_t col_index, ElementType fill_value)
    {
        // assign_col_value(col_index, ElementType fill_value);
    }

    void assign_row(size_t row_index, ElementType fill_value)
    {
        // assign_row_value(row_index, const RContainerType& r_container);
    }

    void assign_col(size_t col_index, ElementType fill_value)
    {
        // assign_col_value(col_index, const RContainerType& r_container);
    }

    void clear()
    {
        // clear();
    }
};

#endif /* LIN_ALG_CONTAINER_STATIC_MATRIX_HPP */
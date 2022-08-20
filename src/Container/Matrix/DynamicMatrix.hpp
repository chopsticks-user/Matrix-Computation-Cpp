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
    // DynamicMatrix(size_t sq_sz)
    // { this->default_fill_initialize(sq_sz, sq_sz); }

    // Matrix<int>(5, 6, 7) --> M<5x6>, ∀ M[i, j] = 7
    // Matrix<int>(5, 6) --> M<5x6>, ∀ M[i, j] = 0
    DynamicMatrix(size_t row_size, size_t col_size, ElementType fill_value = 0)
    {
        this->default_fill_initialize(row_size, col_size, fill_value);
    }

    // copy constructor + copy assignment, implicitly
    template <class RMatrixType>
    DynamicMatrix(const RMatrixType &r_matrix)
    {
        std::cout << std::addressof(r_matrix) << '\n';
        std::cout << "copy\n";
        // this->data_.resize(r_matrix->data_.size());
        this->copy_initialize(r_matrix);
    }

    // move constructor + move assignment, implicitly
    template <class RMatrixType>
    DynamicMatrix(RMatrixType &&r_matrix)
    {
        std::cout << "move\n";
        this->data_.resize(r_matrix->data_.size());
        this->move_initialize(r_matrix);
    }

    // ElementType& at(size_t row_index, size_t col_index)
    // {
    //     // return access_data_at(row_index, col_index);
    //     return this->data_[row_index*this->n_cols_ + col_index];
    // }
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

    void append_row(size_t row_index)
    {
        // assign_row_value(row_index, const RContainerType& r_container);
    }

    void append_col(size_t col_index)
    {
        // assign_col_value(col_index, const RContainerType& r_container);
    }

    void remove_row(size_t row_index)
    {
        // remove_row(row_index);
    }

    void remove_col(size_t row_index)
    {
        // remove_col(col_index);
    }

    void clear()
    {
        // clear();
    }

    void resize(size_t new_row_size, size_t new_col_size)
    {
        this->n_rows_ = new_row_size;
        this->n_cols_ = new_col_size;
        this->data_.resize(new_row_size * new_col_size);
    }

};

#endif /* LIN_ALG_CONTAINER_DYNAMIC_MATRIX_HPP */
#ifndef LIN_ALG_CONTAINER_BASEMATRIX_HPP
#define LIN_ALG_CONTAINER_BASEMATRIX_HPP

#include "../../../libs/Algorithm.hpp"
#include "../../../libs/Utility.hpp"

#include <vector>
#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace linear_algebra
{
    /**
     * @brief Matrix Base.
     *
     * @tparam ElementType
     * @tparam templ_row_size
     * @tparam templ_col_size
     */
    template <typename ElementType,
              utility::SizeType templ_row_size = 0,
              utility::SizeType templ_col_size = 0>
    struct zz_BaseMatrix
    {
        typedef utility::SizeType SizeType;

        typedef std::vector<ElementType> DynamicContainerType;

        typedef std::array<ElementType,
                           templ_row_size * (templ_col_size == 0 ? templ_row_size : templ_col_size)>
            StaticContainerType;

        template <typename ReturnType>
        using DynamicMatrixMethod = typename std::enable_if_t<
            templ_row_size == 0, ReturnType>;

        template <typename ReturnType>
        using StaticMatrixMethod = typename std::enable_if_t<
            templ_row_size != 0, ReturnType>;

        typedef std::conditional_t<templ_row_size == 0,
                                   DynamicContainerType,
                                   StaticContainerType>
            DataContainerType;

        /**
         * If both the size of column and row are either unspecified or equal to zero, data is stored
         * in a standard array. Otherwise, data is stored in a standard vector.
         */
        DataContainerType data_;
        SizeType n_rows_;
        SizeType n_cols_;

        constexpr bool is_dynamic_matrix() { return templ_row_size == 0; }
        constexpr bool is_static_matrix() { return !is_dynamic_matrix(); }

        template <typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        set_dimensions()
        {
            n_rows_ = templ_row_size;
            n_cols_ = templ_col_size == 0 ? templ_row_size : templ_col_size;
        }

        template <typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        set_dimensions(SizeType row_size, SizeType col_size)
        {
            n_rows_ = row_size;
            n_cols_ = col_size == 0 ? row_size : col_size;
        }

        template <typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        fill_initialize(ElementType fill_value = 0)
        {
            set_dimensions();
            data_.fill(fill_value);
        }

        template <typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        fill_initialize(SizeType row_size,
                        SizeType col_size,
                        ElementType fill_value = 0)
        {
            set_dimensions(row_size, col_size);
            data_.resize(row_size * col_size, fill_value);
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        copy_initialize(const zz_BaseMatrix<RhsElementType,
                                            rhs_row_size,
                                            rhs_col_size>
                            &rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                static_assert(rhs_row_size == templ_row_size && rhs_col_size == templ_col_size,
                              "Copy to a static matrix: Dimensions mismatch.");
            set_dimensions();
            try
            {
                if (rhs_matrix.n_rows_ != templ_row_size || rhs_matrix.n_cols_ != templ_col_size)
                    throw std::runtime_error("Copy to a static matrix: Dimensions mismatch.");
                std::copy(rhs_matrix.data_.begin(), rhs_matrix.data_.end(), data_.begin());
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        copy_initialize(const zz_BaseMatrix<RhsElementType,
                                            rhs_row_size,
                                            rhs_col_size>
                            &rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                fill_initialize(rhs_row_size, rhs_col_size);
            else
                fill_initialize(rhs_matrix.n_rows_, rhs_matrix.n_cols_);
            std::copy(rhs_matrix.data_.begin(), rhs_matrix.data_.end(), data_.begin());
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        move_initialize(zz_BaseMatrix<RhsElementType,
                                      rhs_row_size,
                                      rhs_col_size>
                            &&rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                static_assert(rhs_row_size == templ_row_size && rhs_col_size == templ_col_size,
                              "Move to a static matrix: Dimensions mismatch.");
            set_dimensions();
            try
            {
                if (rhs_matrix.n_rows_ != templ_row_size || rhs_matrix.n_cols_ != templ_col_size)
                    throw std::runtime_error("Move to a static matrix: Dimensions mismatch.");
                std::move(rhs_matrix.data_.begin(), rhs_matrix.data_.end(), data_.begin());
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        move_initialize(zz_BaseMatrix<RhsElementType,
                                      rhs_row_size,
                                      rhs_col_size>
                            &&rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                fill_initialize(rhs_row_size, rhs_col_size);
            else
                fill_initialize(rhs_matrix.n_rows_, rhs_matrix.n_cols_);
            std::move(rhs_matrix.data_.begin(), rhs_matrix.data_.end(), data_.begin());
        }

        DataContainerType clone_data()
        {
            DataContainerType cloned_data;
            std::copy(data_.begin(), data_.end(), cloned_data.begin());
            return cloned_data;
        }

        ElementType &access_element_at(SizeType row_index, SizeType col_index)
        {
            try
            {
                return data_.at(row_index * n_cols_ + col_index);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';                
                throw(e);
            }
        }
    };
} /* linear_algebra */

#endif /* LIN_ALG_CONTAINER_BASEMATRIX_HPP */
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
                           templ_row_size *(templ_col_size == 0 ? templ_row_size : templ_col_size)>
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

        /**
         * @brief Set static matrices's row sizes and column sizes.
         * 
         * @tparam ReturnType 
         * @return StaticMatrixMethod<ReturnType> 
         */
        template <typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        set_dimensions()
        {
            n_rows_ = templ_row_size;
            n_cols_ = templ_col_size == 0 ? templ_row_size : templ_col_size;
        }

        /**
         * @brief Set dynamic matrices's row sizes and column sizes.
         * 
         * @tparam ReturnType 
         * @param row_size 
         * @param col_size 
         * @return DynamicMatrixMethod<ReturnType> 
         */
        template <typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        set_dimensions(SizeType row_size, SizeType col_size)
        {
            n_rows_ = row_size;
            n_cols_ = col_size == 0 ? row_size : col_size;
        }

        /**
         * @brief Initialize static matrices's data containers.
         * 
         * @tparam ReturnType 
         * @param fill_value 
         * @return StaticMatrixMethod<ReturnType> 
         */
        template <typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        default_fill_initialize(ElementType fill_value = 0)
        {
            set_dimensions();
            data_.fill(fill_value);
        }

        /**
         * @brief Initialize dynamic matrices's data containers.
         * 
         * @tparam ReturnType 
         * @param row_size 
         * @param col_size 
         * @param fill_value 
         * @return DynamicMatrixMethod<ReturnType> 
         */
        template <typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        default_fill_initialize(SizeType row_size,
                                SizeType col_size,
                                ElementType fill_value = 0)
        {
            set_dimensions(row_size, col_size);
            data_.resize(row_size * col_size, fill_value);
        }
    };
} /* linear_algebra */

#endif /* LIN_ALG_CONTAINER_BASEMATRIX_HPP */
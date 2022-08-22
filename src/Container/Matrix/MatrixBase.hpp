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
     * @brief Matrix Base
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

        typedef std::array<DynamicContainerType,
                           templ_row_size *(templ_col_size == 0 ? templ_row_size : templ_col_size)>
            StaticContainerType;

        template <typename ReturnType>
        using DynamicMatrixMethod = typename std::enable_if_t<
            templ_row_size == 0 && templ_col_size == 0, ReturnType>;

        template <typename ReturnType>
        using StaticMatrixMethod = typename std::enable_if_t<
            templ_row_size != 0, ReturnType>;

        typedef std::conditional_t<templ_row_size == 0 && templ_col_size == 0,
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

        constexpr bool is_dynamic_matrix() { return templ_row_size == 0 && templ_col_size == 0; }
        constexpr bool is_static_matrix() { return !is_dynamic_matrix(); }

        void initialize_dimensions()
        {
        }

        void set_dimensions(SizeType row_size, SizeType col_size)
        {
        }

        StaticMatrixMethod<void>
        default_fill_initialize()
        {
            return;
        }
    };
} /* linear_algebra */

#endif /* LIN_ALG_CONTAINER_BASEMATRIX_HPP */
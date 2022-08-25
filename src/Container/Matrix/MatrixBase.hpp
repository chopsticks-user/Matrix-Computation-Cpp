#ifndef LIN_ALG_CONTAINER_BASEMATRIX_HPP
#define LIN_ALG_CONTAINER_BASEMATRIX_HPP

#include "../../Algorithm/Algorithm.hpp"
#include "../../Utility/Utility.hpp"

#include <vector>
#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace zz_no_inc
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
    struct MatrixBase_
    {
        typedef utility::SizeType SizeType;

        typedef std::vector<ElementType> DynamicContainerType;

        typedef std::array<ElementType,
                           utility::verified_matrix_data_container_size<
                               templ_row_size,
                               templ_col_size>()>
            StaticContainerType;

        template <typename ReturnType>
        using DynamicMatrixMethod = typename std::enable_if_t<
            utility::is_declared_dynamic_matrix<templ_row_size,
                                                templ_col_size>{},
            ReturnType>;

        template <typename ReturnType>
        using StaticMatrixMethod = typename std::enable_if_t<
            utility::is_declared_static_matrix<templ_row_size,
                                               templ_col_size>{},
            ReturnType>;

        typedef std::conditional_t<templ_row_size == 0,
                                   DynamicContainerType,
                                   StaticContainerType>
            DataContainerType;

        /**
         * If both the size of column and row are either unspecified or equal to zero, data is stored
         * in a standard array. Otherwise, data is stored in a standard vector.
         */
        DataContainerType data__;
        SizeType n_rows__;
        SizeType n_cols__;

        constexpr bool is_dynamic_()
        {
            return utility::is_declared_dynamic_matrix<templ_row_size,
                                                       templ_col_size>{};
        }

        constexpr bool is_static_()
        {
            return utility::is_declared_static_matrix<templ_row_size,
                                                      templ_col_size>{};
        }

        const SizeType &get_row_size_() const noexcept { return n_rows__; }

        const SizeType &get_col_size_() const noexcept { return n_cols__; }

        template <typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        set_dimensions_()
        {
            n_rows__ = templ_row_size;
            n_cols__ = utility::verified_matrix_col_size<templ_row_size, templ_col_size>();
        }

        template <typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        set_dimensions_(SizeType row_size, SizeType col_size)
        {
            n_rows__ = row_size;
            n_cols__ = utility::verified_matrix_col_size(row_size, col_size);
        }

        template <typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        fill_initialize_(ElementType fill_value = 0)
        {
            set_dimensions_();
            data__.fill(fill_value);
        }

        template <typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        fill_initialize_(SizeType row_size,
                         SizeType col_size,
                         ElementType fill_value = 0)
        {
            set_dimensions_(row_size, col_size);
            data__.resize(row_size * col_size, fill_value);
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        copy_initialize_(const MatrixBase_<RhsElementType,
                                           rhs_row_size,
                                           rhs_col_size>
                             &rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                static_assert(utility::check_if_equal_dimensions<
                                  templ_row_size, templ_col_size,
                                  rhs_row_size, rhs_col_size>(),
                              "Copy to a static matrix: Dimensions mismatch.");
            set_dimensions_();
            try
            {
                if (rhs_matrix.n_rows__ != templ_row_size ||
                    rhs_matrix.n_cols__ != utility::verified_matrix_col_size(templ_row_size, templ_col_size))
                    throw std::runtime_error("Copy to a static matrix: Dimensions mismatch.");
                std::copy(rhs_matrix.data__.begin(), rhs_matrix.data__.end(), data__.begin());
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        copy_initialize_(const MatrixBase_<RhsElementType,
                                           rhs_row_size,
                                           rhs_col_size>
                             &rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                fill_initialize_(rhs_row_size, rhs_col_size);
            else
                fill_initialize_(rhs_matrix.n_rows__, rhs_matrix.n_cols__);
            std::copy(rhs_matrix.data__.begin(), rhs_matrix.data__.end(), data__.begin());
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        StaticMatrixMethod<ReturnType>
        move_initialize_(MatrixBase_<RhsElementType,
                                     rhs_row_size,
                                     rhs_col_size>
                             &&rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                static_assert(utility::check_if_equal_dimensions<
                                  templ_row_size, templ_col_size,
                                  rhs_row_size, rhs_col_size>(),
                              "Copy to a static matrix: Dimensions mismatch.");
            set_dimensions_();
            try
            {
                if (rhs_matrix.n_rows__ != templ_row_size ||
                    rhs_matrix.n_cols__ != utility::verified_matrix_col_size(templ_row_size, templ_col_size))
                    throw std::runtime_error("Copy to a static matrix: Dimensions mismatch.");
                std::move(rhs_matrix.data__.begin(), rhs_matrix.data__.end(), data__.begin());
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        template <typename RhsElementType, SizeType rhs_row_size, SizeType rhs_col_size,
                  typename ReturnType = void>
        DynamicMatrixMethod<ReturnType>
        move_initialize_(MatrixBase_<RhsElementType,
                                     rhs_row_size,
                                     rhs_col_size>
                             &&rhs_matrix)
        {
            if constexpr (rhs_row_size != 0)
                fill_initialize_(rhs_row_size, rhs_col_size);
            else
                fill_initialize_(rhs_matrix.n_rows__, rhs_matrix.n_cols__);
            std::move(rhs_matrix.data__.begin(), rhs_matrix.data__.end(), data__.begin());
        }

        /// Safety check is handled by either std::array or std::vector.
        ElementType &operator()(SizeType row_index, SizeType col_index)
        {
            return data__.at(row_index * n_cols__ + col_index);
        }

        /// Safety check is handled by either std::array or std::vector.
        const ElementType &operator()(SizeType row_index, SizeType col_index) const
        {
            return data__.at(row_index * n_cols__ + col_index);
        }

        /// No-throw if ElementType can be printed by std::cout
        friend std::ostream &operator<<(std::ostream &os, const MatrixBase_ &rhs_matrix)
        {
            os << "\n[";
            for (size_t i = 0; i < rhs_matrix.n_rows__; i++)
            {
                os << "[";
                if (rhs_matrix.data__.size() / rhs_matrix.n_rows__ >= 1)
                    os << rhs_matrix.data__[i * rhs_matrix.n_cols__];
                for (size_t j = 1; j < rhs_matrix.n_cols__; j++)
                    os << ", " << rhs_matrix.data__[i * rhs_matrix.n_cols__ + j];
                os << "]";
                if (i < rhs_matrix.n_rows__ - 1)
                    os << "\n ";
            }
            os << "]\n";
            return os;
        }

        DataContainerType clone_data_() const
        {
            DataContainerType cloned_data;
            std::copy(data__.begin(), data__.end(), cloned_data.begin());
            return cloned_data;
        }

        MatrixBase_ &fill_all_element_with_(ElementType fill_value)
        {
            std::fill(data__.begin(), data__.end(), fill_value);
            return *this;
        }

        MatrixBase_ &fill_value_to_row_(SizeType row_index, ElementType fill_value)
        {
            if (row_index >= n_rows__)
                throw std::out_of_range("Row index is out of range.");
            std::fill(data__.begin() + n_cols__ * row_index,
                      data__.begin() + n_cols__ * (row_index + 1),
                      fill_value);
            return *this;
        }

        MatrixBase_ &fill_value_to_col_(SizeType col_index, ElementType fill_value)
        {
            if (col_index >= n_cols__)
                throw std::out_of_range("Column index is out of range.");
            if (n_cols__ == 1)
                fill_all_element_with_(fill_value);
            for (auto i = col_index; i < n_rows__ * n_cols__; i += n_cols__)
                data__.at(i) = fill_value;
            return *this;
        }
    };
} /* linear_algebra */

#endif /* LIN_ALG_CONTAINER_BASEMATRIX_HPP */
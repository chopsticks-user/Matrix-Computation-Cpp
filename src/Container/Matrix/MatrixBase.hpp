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
    template <typename ElementType,
              utility::SizeType templ_row_size = 0,
              utility::SizeType templ_col_size = 0>
    struct zz_BaseMatrix
    {
        typedef std::conditional_t<templ_row_size == 0 && templ_col_size == 0,
                                   std::array<ElementType, templ_row_size * templ_col_size>,
                                   std::vector<ElementType>>
            DataContainerType;

        DataContainerType data_;
    };
} /* linear_algebra */

#endif /* LIN_ALG_CONTAINER_BASEMATRIX_HPP */
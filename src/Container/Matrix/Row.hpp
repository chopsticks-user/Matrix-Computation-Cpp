#ifndef LIN_ALG_CONTAINER_ROW_HPP
#define LIN_ALG_CONTAINER_ROW_HPP

#include <array>

namespace zz_no_inc
{
    template <typename ElementType>
    struct Row
    {

        Row() = default;

        template<typename Iterator>
        Row(Iterator it_begin, Iterator it_end){};
    };
}

#endif /* LIN_ALG_CONTAINER_ROW_HPP */
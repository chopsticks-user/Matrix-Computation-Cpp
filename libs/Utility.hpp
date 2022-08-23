
#include <type_traits>

namespace utility
{
    typedef long SizeType;

    template <typename T>
    constexpr bool is_lvalue(T &&)
    {
        return std::is_lvalue_reference<T>{};
    };

    template <typename T>
    constexpr bool is_rvalue(T &&)
    {
        return std::is_rvalue_reference<T &&>{};
    };

    template <SizeType row_size, SizeType col_size>
    constexpr void validate_matrix_dimensions()
    {
        static_assert(row_size >= 0,
                      "Row size must be non-negative.");
        static_assert(col_size >= 0,
                      "Column size must be non-negative.");
        static_assert(row_size != 0 || col_size == 0,
                      "Dynamic matrices cannot have a fixed column size.");
    }

    template <SizeType row_size, SizeType col_size>
    using is_dynamic_matrix_vv =
        std::integral_constant<bool, row_size == 0 && col_size == 0>;
}
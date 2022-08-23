
#include <type_traits>
#include <iostream>

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
    constexpr bool check_if_dynamic_matrix()
    {
        validate_matrix_dimensions<row_size, col_size>();
        return row_size == 0;
    }

    bool check_if_dynamic_matrix(SizeType row_size, SizeType col_size)
    {
        return row_size == 0 && col_size == 0;
    }

    template <SizeType row_size, SizeType col_size>
    constexpr bool check_if_static_matrix()
    {
        validate_matrix_dimensions<row_size, col_size>();
        return row_size > 0;
    }

    bool check_if_static_matrix(SizeType row_size, SizeType col_size)
    {
        return row_size > 0;
    }

    template <SizeType row_size, SizeType col_size>
    constexpr bool check_if_static_square_matrix()
    {
        validate_matrix_dimensions<row_size, col_size>();
        return row_size > 0 && (col_size == 0 || row_size == col_size);
    }

    bool check_if_static_square_matrix(SizeType row_size, SizeType col_size)
    {
        return row_size > 0 && (col_size == 0 || row_size == col_size);
    }

    template <SizeType row_size, SizeType col_size>
    constexpr SizeType verified_matrix_col_size()
    {
        if constexpr (check_if_static_square_matrix<row_size, col_size>() == true)
            return row_size;
        return col_size;
    }

    SizeType verified_matrix_col_size(SizeType row_size, SizeType col_size)
    {
        if (check_if_static_square_matrix(row_size, col_size) == true)
            return row_size;
        return col_size;
    }

    template <SizeType row_size, SizeType col_size>
    constexpr SizeType verified_matrix_data_container_size()
    {
        return row_size * verified_matrix_col_size<row_size, col_size>();
    }

    SizeType verified_matrix_data_container_size(
        SizeType row_size,
        SizeType col_size)
    {
        return row_size * verified_matrix_col_size(row_size, col_size);
    }

    template <SizeType row_size, SizeType col_size>
    struct is_declared_dynamic_matrix
        : public std::integral_constant<
              bool, check_if_dynamic_matrix<row_size, col_size>()>
    {
    };

    template <SizeType row_size, SizeType col_size>
    using is_declared_dynamic_matrix_v =
        typename is_declared_dynamic_matrix<row_size, col_size>::value;

    template <SizeType row_size, SizeType col_size>
    struct is_declared_static_matrix
        : public std::integral_constant<
              bool, check_if_static_matrix<row_size, col_size>()>
    {
    };

    template <SizeType row_size, SizeType col_size>
    using is_declared_static_matrix_v =
        typename is_declared_static_matrix<row_size, col_size>::value;

    template <typename ContainerItType>
    void print_1d_container(ContainerItType it_begin, ContainerItType it_end)
    {
        std::cout << '[' << *it_begin;
        for (; it_begin != it_end; it_begin++)
            std::cout << ", " << *it_begin;
        std::cout << "]\n";
    }

    // in Matrix.hpp
    template <typename T>
    struct is_dynamic_matrix : public std::false_type
    {
    };

    // in Matrix.hpp
    template <template <typename ElementType,
                        SizeType row_size,
                        SizeType col_size>
              class T,
              typename ElementType>
    struct is_dynamic_matrix<T<ElementType, 0, 0>>
        : public std::true_type
    {
    };

}
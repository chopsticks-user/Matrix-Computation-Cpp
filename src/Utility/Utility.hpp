#ifndef ULTILITY_HPP
#define ULTILITY_HPP

#include "Expect.hpp"

#include <type_traits>
#include <iostream>
#include <chrono>
#include <random>

namespace utility
{
    typedef long SizeType;
    typedef size_t PositiveSizeType;

    using mic = std::chrono::microseconds;
    using mil = std::chrono::milliseconds;
    using sec = std::chrono::seconds;
    using min = std::chrono::minutes;
    using hr = std::chrono::hours;

    template <typename DurationType = mic>
    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::string time_unit;

    public:
        Timer()
        {
            if (std::is_same_v<DurationType, mic>)
                this->time_unit = "μs";
            else if (std::is_same_v<DurationType, mil>)
                this->time_unit = "ms";

            else if (std::is_same_v<DurationType, sec>)
                this->time_unit = "s";

            else if (std::is_same_v<DurationType, min>)
                this->time_unit = "mins";

            else if (std::is_same_v<DurationType, hr>)
                this->time_unit = "hrs";
            else
                static_assert("Unkown time unit.");

            this->start = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            auto stop = std::chrono::high_resolution_clock::now();
            std::cout << "Time elapsed: "
                      << std::chrono::duration_cast<
                             DurationType>(stop - start)
                             .count()
                      << ' ' << this->time_unit << "\n";
        }
    };

    long long rand(long long min, long long max)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<long long> dist(min, max);
        return dist(rng);
    }

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

    template <typename T>
    constexpr void require_nothrow_destructible_type()
    {
        static_assert(std::is_nothrow_destructible_v<T>,
                      "Type must have a non-throwing destructor.");
    }

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

    template <SizeType row_size1, SizeType col_size1,
              SizeType row_size2, SizeType col_size2>
    constexpr bool check_if_equal_dimensions()
    {
        if constexpr (row_size1 == row_size2)
            if constexpr (verified_matrix_col_size<row_size1, col_size1>() ==
                          verified_matrix_col_size<row_size2, col_size2>())
                return true;
        return false;
    }

    bool check_if_equal_dimensions(SizeType row_size1, SizeType col_size1,
                                   SizeType row_size2, SizeType col_size2)
    {
        return row_size1 == row_size2 && col_size1 == col_size2;
    }

    bool check_if_multipliable(SizeType row_size1, SizeType col_size1,
                               SizeType row_size2, SizeType col_size2)
    {
        return row_size1 == col_size2 && col_size1 == row_size2;
    }

    template <SizeType row_size, SizeType col_size>
    struct is_declared_dynamic_matrix
        : public std::integral_constant<
              bool, check_if_dynamic_matrix<row_size, col_size>()>
    {
    };

    // template <SizeType row_size, SizeType col_size>
    // using is_declared_dynamic_matrix_v =
    //     typename is_declared_dynamic_matrix<row_size, col_size>::value;

    template <SizeType row_size, SizeType col_size>
    struct is_declared_static_matrix
        : public std::integral_constant<
              bool, check_if_static_matrix<row_size, col_size>()>
    {
    };

    // template <SizeType row_size, SizeType col_size>
    // using is_declared_static_matrix_v =
    //     typename is_declared_static_matrix<row_size, col_size>::value;

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

    template <typename SeqContainer1D>
    SizeType get_1d_seq_container_size(const SeqContainer1D &container)
    {
        if constexpr (std::is_array_v<SeqContainer1D>)
            return sizeof(container) / sizeof(container[0]); // might throw
        else
            return container.size(); // might throw
    }

    template <typename ElementType>
    constexpr void check_element_requirements()
    {
        static_assert(std::is_default_constructible_v<ElementType>,
                      "Element type must be default constructible.");
        static_assert(std::is_copy_constructible_v<ElementType>,
                      "Element type must be copy constructible.");
        static_assert(std::is_move_constructible_v<ElementType>,
                      "Element type must be move constructible.");
        static_assert(std::is_nothrow_destructible_v<ElementType>,
                      "Element type must be non-throwing destructible.");
    }

} /* utility */

#endif /* ULTILITY_HPP */
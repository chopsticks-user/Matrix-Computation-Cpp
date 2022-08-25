
#include <type_traits>
#include <iostream>
#include <chrono>
#include <random>

namespace utility
{
    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::string time_unit;

    public:
        Timer()
        {
            this->start = std::chrono::high_resolution_clock::now();
            this->time_unit = "milliseconds";
        }
        Timer(std::string &&time_unit)
        {
            this->start = std::chrono::high_resolution_clock::now();
            if (time_unit == "microseconds")
            {
                this->time_unit = "microseconds";
                return;
            }
            this->time_unit = "milliseconds";
        }
        ~Timer()
        {
            auto stop = std::chrono::high_resolution_clock::now();
            if (this->time_unit == "microseconds")
            {
                std::cout << "\nTime elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n";
                return;
            }
            std::cout << "\nTime elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
        }
    };

    long long rand(long long min, long long max)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<long long> dist(min, max);
        return dist(rng);
    }

    typedef size_t SizeType;

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

    template <typename SeqContainer1D>
    SizeType get_1d_seq_container_size(const SeqContainer1D &container)
    {
        if constexpr (std::is_array_v<SeqContainer1D>)
            return sizeof(container) / sizeof(container[0]); // might throw
        else
            return container.size(); // might throw
    }

}
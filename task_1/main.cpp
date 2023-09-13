#include <array>
#include <iostream>

template <int N>
constexpr std::array<std::array<int, N - 1>, N - 1> Submatrix(const std::array<std::array<int, N>, N> &matrix, const int row, const int colomn)
{
    std::array<std::array<int, N - 1>, N - 1> sb{};
    for (int i = 0; i < N - 1; ++i)
        for (int j = 0; j < N - 1; ++j)
            (&std::get<0>(((&std::get<0>(sb))[i])))[j] = matrix[i + (i >= row ? 1 : 0)][j + (j >= colomn ? 1 : 0)];
    return sb;
}

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N> &matrix)
{
    int det = 0;
    for (int i = 0; i < N; ++i)
    {
        auto sb = Submatrix<N>(matrix, 0, i);
        det += matrix[0][i] * Det<N - 1>(sb) * ((i % 2 == 0) ? 1 : -1);
    }
    return det;
}

template <>
constexpr int Det<1>(const std::array<std::array<int, 1>, 1> &matrix)
{
    return matrix[0][0];
}
template <>
constexpr int Det<2>(const std::array<std::array<int, 2>, 2> &matrix)
{
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

int main()
{
    constexpr std::array<std::array<int, 3>, 3> matrix1 = {{{0, 1, 2},
                                                           {1, 2, 3},
                                                           {2, 3, 7}}};
    constexpr int result1 = Det<3>(matrix1);
    std::cout << result1 << std::endl;

    constexpr std::array<std::array<int, 4>, 4> matrix2 = {{{2, 1, 1, 1},
                                                           {-3, 2, 1, 1},
                                                           {3, 3, 2, 1},
                                                           {1, 2, 3, 4}}};
    constexpr int result2 = Det<4>(matrix2);
    std::cout << result2 << std::endl;

    constexpr std::array<std::array<int, 5>, 5> matrix3 = {{{2, 1, 1, 1, 4},
                                                           {-3, 2, 1, 1, 3},
                                                           {3, 3, 2, 1, 2},
                                                           {1, 2, 3, 4, 1},
                                                           {1, 2, 3, 4, 0}}};
    constexpr int result3 = Det<5>(matrix3);
    std::cout << result3 << std::endl;
    return 0;
}

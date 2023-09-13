#include <array>
#include <iostream>

constexpr int Det(const std::array<std::array<int, 1>, 1> &matrix)
{
    return matrix[0][0];
}

constexpr int Det(const std::array<std::array<int, 2>, 2> &matrix)
{
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N> &matrix)
{
    int det = 0;
    for (int i = 0; i < N; ++i)
    {
        std::array<std::array<int, N - 1>, N - 1> submatrix{};
        for (int j = 1; j < N; ++j)
        {
            int k = 0;
            for (int l = 0; l < N; ++l)
            {
                if (l == i)
                    continue;
                (&std::get<0>(((&std::get<0>(submatrix))[j - 1])))[k++] = matrix[j][l];
            }
        }
        det += matrix[0][i] * Det(submatrix) * ((i % 2 == 0) ? 1 : -1);
    }
    return det;
}

int main()
{
    constexpr std::array<std::array<int, 3>, 3> matrix = {{{2, 0, 0},
                                                           {0, 2, 0},
                                                           {0, 0, 2}}};
    constexpr int result = Det<3>(matrix);
    std::cout << result << std::endl;
    return 0;
}
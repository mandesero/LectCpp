#include <vector>

int main()
{
    std::vector<bool> v;

    /*
        std::_Bit_iterator::reference &el
        является rvalue, а начальное значение ссылки на неконстантное значение должно быть lvalue
        => ошибка компиляции

        [cppreference]: Exposes class std::vector<bool>::reference as a method of accessing individual bits.
        In particular, objects of this class are returned by operator[] by value.

    */
    for (auto &el : v);

    /*
        std::_Bit_iterator::reference &&el
        универсальная ссылка, ошибок не возникает
    */
    for (auto &&el : v);
}
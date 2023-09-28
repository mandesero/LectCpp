#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <set>

#include <cassert>

struct TPrettyPrinter
{
    std::ostringstream os;

    const std::string Str() const
    {
        return os.str();
    }

    template <typename ValueType>
    TPrettyPrinter &Format(ValueType v)
    {
        os << v;
        return *this;
    }

    template <typename ValueType>
    TPrettyPrinter &Format(const std::vector<ValueType> &v)
    {
        bool flag = true;
        for (const auto &x : v)
        {
            if (flag)
                os << "[";
            else
                os << ", ";

            os << TPrettyPrinter().Format(x).Str();
            flag = false;
        }
        os << "]";
        return *this;
    }

    template <typename... Args>
    TPrettyPrinter &Format(const std::tuple<Args...> &t)
    {
        std::apply([this](auto... elements)
                   {
            bool flag = true;
            auto printElement = [&flag, this](const auto& x) {
                if (flag)
                    os << "(";
                else
                    this->os << ", ";

                os << TPrettyPrinter().Format(x).Str();
                flag = false;
            };
            (printElement(elements), ...); },
                   t);

        os << ")";
        return *this;
    }

    template <typename SetType>
    TPrettyPrinter &Format(const std::set<SetType> &s)
    {
        bool flag = true;
        for (const auto &x : s)
        {
            if (flag)
                os << "{";
            else
                os << ", ";

            os << TPrettyPrinter().Format(x).Str();
            flag = false;
        }
        os << "}";
        return *this;
    }

    template <typename PairType_1, typename PairType_2>
    TPrettyPrinter &Format(const std::pair<PairType_1, PairType_2> &p)
    {
        os << "(" << TPrettyPrinter().Format(p.first).Str() << ", " << TPrettyPrinter().Format(p.second).Str() << ")";
        return *this;
    }
};

template <typename T>
const std::string Format(const T &t)
{
    return TPrettyPrinter().Format(t).Str();
}

int main()
{
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int>> v = {{1, 4}, {5, 6}};
    std::string s1 = TPrettyPrinter().Format("vector: ").Format(v).Str();
    std::string s2 = TPrettyPrinter().Format(t).Format(" ! ").Format(0).Str();

    assert("vector: [(1, 4), (5, 6)]" == s1);
    assert("(xyz, 1, 2) ! 0" == s2);
}

#include <iostream>
#include <memory>

template <typename T, typename OtherT = T>
struct CustomAllocator
{
    using value_type = T;

    CustomAllocator() = default;

    template <class U>
    CustomAllocator(const CustomAllocator<U> &) noexcept {};

    T *allocate(std::size_t n)
    {
        return static_cast<T *>(OtherT::operator new(sizeof(T) * n));
    }

    void deallocate(T *p, std::size_t n)
    {
        return OtherT::operator delete(p, sizeof(T) * n);
    }
};

class A
{
public:
    // ...
    static void *operator new(size_t size)
    {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size)
    {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

int main()
{
    auto sp = std::allocate_shared<A>(CustomAllocator<A>());
    return 0;
}

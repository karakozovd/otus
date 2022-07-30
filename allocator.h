#include <memory>
#include <iostream>

template <typename T, size_t B_SZ>
class Buffer
{
public:
    using size_type = typeof B_SZ;
    using value_type = T;
    using pointer = T*;

    explicit Buffer() { m_data = (pointer)malloc(sizeof(value_type) * B_SZ); }
    virtual ~Buffer() { delete []m_data; }

    value_type& operator[](size_type i)
    {
        if (i >= B_SZ || i < 0)
            throw std::out_of_range("buffer out of range");

        return *(m_data + i);
    }

    value_type operator[](size_type i) const
    {
        if (i >= B_SZ || i < 0)
            throw std::out_of_range("buffer out of range");

        return *(m_data + i);
    }

private:
    pointer m_data;
};

template <typename T, size_t SZ>
class BasicAllocator
{
public:
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = typeof SZ;

    using self_type = BasicAllocator<T, SZ>;

    template <typename U>
    struct rebind
    {
        using other = BasicAllocator<U, SZ>;
    };

    BasicAllocator(const self_type &other) = delete;
    BasicAllocator(self_type &&other) = delete;
    BasicAllocator operator =(self_type) = delete;

    explicit BasicAllocator() : m_buffer(Buffer<value_type, SZ>()), m_offset(size_type()) { }

    ~BasicAllocator() = default;

    pointer allocate(int n)
    {
        if (size_type(n) > SZ)
            throw std::bad_alloc();

        size_type oldOffset = m_offset;
        ++m_offset;

        return &m_buffer[oldOffset];
    }

    void deallocate(pointer, size_type) { }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        ::new(p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p)
    {
        p->~U();
    }

    size_type max_size() const { return SZ; }

private:
    Buffer<value_type, SZ> m_buffer;
    size_type m_offset;
};

#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class BasicVector
{
public:
    BasicVector() : m_size(0), m_allocator() { }
    ~BasicVector() = default;

    void push_back(const T& item)
    {
        T* ptr =  basic_alloc_traits::allocate(m_allocator, 1);
        basic_alloc_traits::construct(m_allocator, ptr, item);

        if (m_size == 0)
            m_data = ptr;

        ++m_size;
    }

    void pop_back()
    {
        basic_alloc_traits::destroy(m_allocator, m_data + m_size);
        basic_alloc_traits::deallocate(m_allocator, m_data + m_size, 1);

        --m_size;
    }

    size_t size() const noexcept { return m_size; }

    T& operator[](size_t pos) { return *(m_data + pos); }
    const T& operator[](size_t pos) const { return *(m_data + pos); }

public:
    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() noexcept { return m_data; }
    iterator end() noexcept { return m_data + m_size; }

    const_iterator begin() const noexcept { return m_data; }
    const_iterator end() const noexcept { return m_data + m_size; }

    const_iterator cbegin() const noexcept { return m_data; }
    const_iterator cend() const noexcept { return m_data + m_size; }

private:
    size_t m_size;

    T* m_data { nullptr };

    using basic_alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<T>;
    using basic_alloc_traits = typename std::allocator_traits<Allocator>::template rebind_traits<T>;

    basic_alloc m_allocator;
};

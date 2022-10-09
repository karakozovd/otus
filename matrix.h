#include <map>
#include <numeric>

template <typename T, T default_value>
class Field
{
public:
    explicit Field() : m_value {default_value} { }
    explicit Field(T value) : m_value {value} { }

    Field &operator=(T rval)
    {
        m_value = rval;
        return *this;
    }

    operator T() const { return m_value; }

private:
    T m_value;
};

template <typename T, T default_value>
class Pair
{
public:
    explicit Pair() = default;
    virtual ~Pair() = default;

    size_t size() const
    {
        auto sz = std::accumulate(m_pairsMap.begin(), m_pairsMap.end(), 0, [](const size_t &prev, const std::pair<int, Field<T, default_value>> &val){
            // increment counter only if element != default value
            return (val.second == default_value) ? prev : prev + 1;
        });

        return sz;
    }

    Field<T, default_value> &operator[](int idx) { return m_pairsMap[idx]; }

private:
    std::map<int, Field<T, default_value>> m_pairsMap;
};

template <typename T, T default_value>
class Matrix
{
public:
    explicit Matrix() = default;
    virtual ~Matrix() = default;

    size_t size() const
    {
        auto sz = std::accumulate(m_matrix.begin(), m_matrix.end(), 0, [](const size_t &prev, const std::pair<int, Pair<T, default_value>> &val){
            return prev + val.second.size();
        });

        return sz;
    }

    Pair<T, default_value> &operator[](int idx) { return m_matrix[idx]; }

private:
    std::map<int, Pair<T, default_value>> m_matrix;
};

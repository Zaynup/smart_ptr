#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(T *ptr) : m_ptr(ptr){};

    unique_ptr(cosnt unique_ptr &rhs) = delete;
    unique_ptr &operator=(const unique_ptr &rhs) = delete;

    T *get() const noexcept
    {
        return m_ptr;
    }

    T *release()
    {
        return std::exchange(m_ptr, nullptr);
    }

    void reset(T *ptr) noexcept
    {
        delete std::exchange(m_ptr, ptr);
    }

    void swap(unique_ptr &rhs)
    {
    }

private:
    T *m_ptr;
};
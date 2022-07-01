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

    void reset()
    {
    }

    void swap()
    {
    }

private:
    T *m_ptr;
};
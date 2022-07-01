#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(std::nullptr_t) : unique_ptr() {}
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs);
    ~unique_ptr();

    unique_ptr operator=(const unique_ptr &rhs) = delete;
    unique_ptr &operator=(std::nullptr_t);
    unique_ptr &operator=(unique_ptr &&rhs);

    operator*()
    {
        return *m_ptr;
    }

    T *get()
    {
        return m_ptr;
    }

    T *release()
    {
        return std::exchange(m_ptr, nullptr);
    }

    void reset(T *ptr)
    {
        delete std::exchange(m_ptr, ptr);
    }

private:
    T *m_ptr{nullptr};
};
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
    unique_ptr &operator=(std::nullptr_t)
    {
        reset();
        return *this;
    }
    unique_ptr &operator=(unique_ptr &&rhs)
    {
        reset(rhs.release());
        return *this;
    }

    explicit operator bool()
    {
        return static_cast<bool>(m_ptr);
    }

    unique_ptr &operator*()
    {
        return *m_ptr;
    }

    unique_ptr *operator->()
    {
        return m_ptr;
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

    void swap(unique_ptr &rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
    }

private:
    T *m_ptr{nullptr};
};

template <typename T, typename... Args>
auto make_unique(Args &&...args)
{
    return unique_ptr<T>{new T(std::forward<Args>(args)...)};
}
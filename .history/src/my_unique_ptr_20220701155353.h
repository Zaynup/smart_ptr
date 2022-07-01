#include <utility>

template <typename T>
class unique_ptr
{
public:
    constexpr unique_ptr() noexcept = default;
    constexpr unique_ptr(std::nullptr_t) noexcept : unique_ptr() {}
    unique_ptr(T *ptr) noexcept : m_ptr(ptr) {}

    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs) noexcept : m_ptr(rhs.release()) {}

    ~unique_ptr() noexcept
    {
        delete m_ptr;
    }

    unique_ptr operator=(const unique_ptr &rhs) = delete;
    unique_ptr &operator=(std::nullptr_t)
    {
        reset();
        return *this;
    }
    unique_ptr &operator=(unique_ptr &&rhs) noexcept
    {
        reset(rhs.release());
        return *this;
    }

    explicit operator bool()
    {
        return static_cast<bool>(m_ptr);
    }

    unique_ptr &operator*() const
    {
        return *m_ptr;
    }

    unique_ptr *operator->() noexcept
    {
        return m_ptr;
    }

    T *get() const noexcept
    {
        return m_ptr;
    }

    T *release() noexcept
    {
        return std::exchange(m_ptr, nullptr);
    }

    void reset(T *ptr) noexcept
    {
        delete std::exchange(m_ptr, ptr);
    }

    void swap(unique_ptr &rhs) noexcept
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
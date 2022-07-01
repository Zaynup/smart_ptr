#include <utility>

template <typename T>
class unique_ptr
{
public:
    constexpr unique_ptr() noexcept = default;
    constexpr unique_ptr(std::nullptr_t) noexcept : unique_ptr() {}

    explicit unique_ptr(T *ptr) noexcept : m_ptr(ptr){};

    unique_ptr(const unique_ptr &rhs) = delete;

    unique_ptr(unique_ptr &&rhs) noexcept : m_ptr(rhs.release()) {}

    unique_ptr &operator=(const unique_ptr &rhs) = delete;
    unique_ptr &operator=(const unique_ptr &&rhs)
    {
        reset(rhs.release());
        return *this;
    }
    unique_ptr &operator=(std::nullptr_t)
    {
        reset();
        return *this;
    }

    ~unique_ptr() noexcept
    {
        delete m_ptr;
    }

    T &operator*()
    {
        return *m_ptr;
    }

    T *operator->()
    {
        return m_ptr;
    }

    explicit operator bool() const noexcept
    {
        return static_cast<bool>(m_ptr);
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
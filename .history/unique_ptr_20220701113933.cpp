#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() noexcept = default;
    unique_ptr(T *ptr) noexcept : m_ptr(ptr);
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs) noexcept : m_ptr(rhs.release()) {}

    ~unique_ptr() noexcept
    {
        delete m_ptr;
    }

    unique_ptr &operator=(const unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &&rhs) noexcept
    {
        reset(rhs.release());
        return *this;
    }

    T &operator*()
    {
        return *m_ptr;
    }

    T *operator->()
    {
        return m_ptr;
    }

    operator bool()
    {
        return static_cast<bool>(m_ptr);
    }

    T *get() noexcept
    {
        return m_ptr;
    }

    T *release() noexcept
    {
        return std::exchange(m_ptr, nullptr)
    }

    void reset(T *ptr) noexcept
    {
        // 若m_ptr本身为空指针，delete空指针无问题
        delete std::exchange(m_ptr, ptr);
    }

    void swap(unique_ptr &rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
    }

private:
    T *m_ptr{nullptr};
};
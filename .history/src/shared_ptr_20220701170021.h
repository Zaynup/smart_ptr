#include <utility>

class ref_count
{
public:
    int use_count() const noexcept { return m_count; }
    void inc_ref() noexcept { ++m_count; }
    int dec_ref() noexcept { return --m_count; }

private:
    int m_count = {1};
};

template <typename T>
class shared_ptr
{
public:
    constexpr shared_ptr() noexcept = default;

    constexpr shared_ptr(std::nullptr_t) : shared_ptr() {}

    explicit shared_ptr(T *ptr)
        : m_ptr(ptr)
    {
        if (ptr)
        {
            m_count = new ref_count();
        }
    }

    shared_ptr(const shared_ptr &rhs) noexcept
        : m_ptr(rhs.m_ptr),
          m_count(rhs.m_count)
    {
        if (m_count)
        {
            m_count->inc_ref();
        }
    }

    shared_ptr(shared_ptr &&rhs) noexcept
        : m_ptr(rhs.m_ptr),
          m_count(rhs.m_count)
    {
        rhs.m_ptr = nullptr;
        rhs.m_count = nullptr;
    }

    ~shared_ptr() noexcept
    {
        if (m_count && m_count->dec_ref())
        {
            delete m_ptr;
            delete m_count;
        }
    }

    // 异常安全
    shared_ptr &operator=(const shared_ptr &rhs)
    {
        shared_ptr{rhs}.swap(*this);
        return *this;
    }

    shared_ptr &operator=(shared_ptr &&rhs)
    {
        shared_ptr{std::move(rhs)}.swap(*this)
    }

    explicit operator bool() const noexcept
    {
        return static_cast<bool>(m_ptr);
    }

    T &operator*() const noexcept
    {
        return *m_ptr;
    }

    T *operator->() const noexcept
    {
        return m_ptr;
    }

    bool unique() const noexcept
    {
        return m_count->use_count() == 1;
    }

    T *get() const noexcept
    {
        return m_ptr;
    }

    int use_count() const noexcept
    {
        return m_count ? m_count->use_count() : 0;
    }

    void reset() noexcept
    {
        shared_ptr{}.swap{*this};
    }

    void reset(std::nullptr_t) noexcept
    {
        reset();
    }

    void reset(T *ptr)
    {
        shared_ptr{ptr}.swap(*this);
    }

    void swap(shared_ptr &rhs) noexcept
    {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_count, rhs.m_count);
    }

private:
    T *m_ptr = {nullptr};
    ref_count *m_count = {nullptr};
};

make_shared()
{
}
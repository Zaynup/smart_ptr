#include <utility>

class ref_count
{
public:
    int use_count() { return m_count; }
    void inc_ref() { ++m_count; }
    int dec_ref() { return --m_count; }

private:
    int m_count = {1};
};

template <typename T>
class shared_ptr
{
public:
    shared_ptr() = default;

    explicit shared_ptr(T *ptr)
        : m_ptr(ptr)
    {
        if (ptr)
        {
            m_count = new ref_count();
        }
    }

    shared_ptr(const shared_ptr &rhs)
        : m_ptr(rhs.m_ptr),
          m_count(rhs.m_count)
    {
        if (m_count)
        {
            m_count->inc_ref();
        }
    }

    shared_ptr(shared_ptr &&rhs)
        : m_ptr(rhs.m_ptr),
          m_count(rhs.m_count)
    {
        rhs.m_ptr = nullptr;
        rhs.m_count = nullptr;
    }

    ~shared_ptr()
    {
        if (m_count && m_count->dec_ref())
        {
            delete m_ptr;
            delete m_count;
        }
    }

    shared_ptr &operator=(const shared_ptr &rhs)
    {
        shared_ptr{rhs}.swap(*this);
        return *this;
    }
    shared_ptr &operator=(shared_ptr &&rhs)
    {
    }

    operator bool()
    {
        return static_cast<bool>(m_ptr);
    }

    T &operator*()
    {
        return *m_ptr;
    }

    T *operator->()
    {
        return m_ptr;
    }

    bool unique()
    {
        return 1 == *use_count;
    }

    T *get()
    {
        return m_ptr;
    }

    int use_count()
    {
        return *m_count;
    }

    T *release()
    {
    }

    void reset(T *ptr);

    void swap(shared_ptr &rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_count, rhs.m_count);
    }

private:
    T *m_ptr = {nullptr};
    ref_count *m_count = {nullptr};
};
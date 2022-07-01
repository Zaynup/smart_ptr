#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(T *ptr) : m_ptr(ptr);
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs);

    ~unique_ptr();

    T &operator*();
    T *operator->();
    unique_ptr &operator=(const unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &&) = delete;

    T *get()
    {
        return m_ptr;
    }

    T *release()
    {
        return std::exchange(m_ptr, nullptr)
    }

    void reset(T *ptr)
    {
        delete std::exchange(m_ptr, ptr);
    }

    void swap(unique_ptr &rhs)
    {
    }

private:
    T *m_ptr{nullptr};
};
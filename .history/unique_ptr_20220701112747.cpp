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
        // 若m_ptr本身为空指针，delete空指针无影响
        delete std::exchange(m_ptr, ptr);
    }

    void swap(unique_ptr &rhs)
    {
        std::swap(m_ptr, rhs);
    }

private:
    T *m_ptr{nullptr};
};
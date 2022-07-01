#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(T *ptr) : m_ptr(ptr){};

    unique_ptr(cosnt unique_ptr &rhs) = delete;
    unique_ptr &operator=(const unique_ptr &rhs) = delete;

    T *get()
    {
        return m_ptr;
    }

    void release()
    {
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
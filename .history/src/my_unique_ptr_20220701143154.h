#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(T *ptr) : m_ptr(ptr){};

    unique_ptr(cosnt unique_ptr &rhs) = delete;
    unique_ptr &operator=(const unique_ptr &rhs) = delete;

    void get()
    {
        return m_ptr;
    }

    void release() {}

private:
    T *m_ptr;
};
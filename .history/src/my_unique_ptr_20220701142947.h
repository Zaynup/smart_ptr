#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(T *ptr);

    unique_ptr(cosnt unique_ptr &rhs) = delete;

private:
    T *m_ptr;
};
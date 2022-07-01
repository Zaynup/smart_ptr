#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(const unique_ptr &rhs) = delete;
    ~unique_ptr();

private:
    T *m_ptr{nullptr};
};
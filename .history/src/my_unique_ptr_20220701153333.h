#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr();

private:
    T *m_ptr{nullptr};
};
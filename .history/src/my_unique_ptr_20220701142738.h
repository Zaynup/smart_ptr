#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;

private:
    T *m_ptr;
};
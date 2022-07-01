#include <utility>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(std::nullptr_t) : unique_ptr() {}
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs);
    ~unique_ptr();

    operator=(const unique_ptr &rhs) = delete;

private:
    T *m_ptr{nullptr};
};
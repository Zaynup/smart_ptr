#include <utility>

template <typename T>
class unique_ptr
{
public:
    constexpr unique_ptr() noexcept = default;

    // 不能隐身转换，拷贝构造声明为explicit
    explicit unique_ptr(T *ptr) noexcept : m_ptr(ptr);

    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs) noexcept : m_ptr(rhs.release()) {}

    ~unique_ptr() noexcept
    {
        delete m_ptr;
    }

    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr &operator=(unique_ptr &&rhs) noexcept
    {
        reset(rhs.release());
        return *this;
    }

    T &operator*() const
    {
        return *m_ptr;
    }

    T *operator->() const noexcept
    {
        return m_ptr;
    }

    // operator bool() const noexcept 不能隐式转换
    explicit operator bool() const noexcept
    {
        return static_cast<bool>(m_ptr);
    }

    T *get() const noexcept
    {
        return m_ptr;
    }

    T *release() noexcept
    {
        return std::exchange(m_ptr, nullptr)
    }

    void reset(T *ptr) noexcept
    {
        // 若m_ptr本身为空指针，delete空指针无问题
        delete std::exchange(m_ptr, ptr);
    }

    void swap(unique_ptr &rhs) noexcept
    {
        std::swap(m_ptr, rhs.m_ptr);
    }

private:
    T *m_ptr{nullptr};
};

void func(unique_ptr<int>) {}

int main()
{
    // 不能隐身转换，bool声明为explicit
    // bool b = unique_ptr<int>{};

    // 不能隐身转换，拷贝构造声明为explicit
    // func(new int{1024});
}
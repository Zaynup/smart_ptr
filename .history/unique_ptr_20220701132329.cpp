#include <utility>

template <typename T, typename U>
using enable_if_convertible_t = std::enable_if_t<std::is_convertible_v<T *, U *>, int>;

template <typename T>
class unique_ptr
{
public:
    constexpr unique_ptr() noexcept = default;
    constexpr unique_ptr(nullptr_t) noexcept : unique_ptr() {}

    // 不能隐身转换，拷贝构造声明为explicit
    // explicit unique_ptr(T *ptr) noexcept : m_ptr(ptr);

    template <typename U, enable_if_convertible_t<U, T> = 0>
    explicit unique_ptr<U * ptr> noexpect : m_ptr(ptr) {}

    unique_ptr(const unique_ptr &rhs) = delete;

    // unique_ptr(unique_ptr &&rhs) noexcept : m_ptr(rhs.release()) {}

    template <typename U, enable_if_convertible_t<U, T> = 0>
    unique_ptr(unique_ptr<U> &&rhs) noexcept : m_ptr(rhs.release()) {}

    ~unique_ptr() noexcept
    {
        delete m_ptr;
    }

    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr &operator=(nullptr_t)
    {
        reset();
        return *this;
    }

    template <typename U, enable_if_convertible_t<U, T> = 0>
    unique_ptr &operator=(unique_ptr<U> &&rhs) noexcept
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

    // 不能隐身转换，bool声明为explicit
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

template <typename T, typename... Args>
auto make_unique(Args &&...args)
{
    return unique_ptr<T>{new T(std::forward(args)...)};
    // return unique_ptr<T>{new T{std::forward(args)...}};
}

void func(unique_ptr<int>) {}

#include <vector>
int main()
{
    // 不能隐身转换，bool声明为explicit
    // bool b = unique_ptr<int>{};

    // 不能隐身转换，拷贝构造声明为explicit
    // func(new int{1024});

    const unique_ptr<int> p1;       // 智能指针不能修改
    const unique_ptr<const int> p2; // 对象不能修改

    make_unique<std::vector<int>>(3, 3);
}
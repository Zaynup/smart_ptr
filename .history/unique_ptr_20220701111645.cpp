template <typename T>
class unique_ptr
{
public:
    unique_ptr();
    unique_ptr(T *ptr);
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs);

    ~unique_ptr();

    T &operator*();

private:
    T *m_ptr;
};
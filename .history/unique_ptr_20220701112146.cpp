template <typename T>
class unique_ptr
{
public:
    unique_ptr() = default;
    unique_ptr(T *ptr);
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr(unique_ptr &&rhs);

    ~unique_ptr();

    T &operator*();
    T *operator->();
    unique_ptr &operator=(const unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &&) = delete;

    T *get();
    T *release();
    void reset(T *ptr);
    void swap(unique_ptr &rhs);

private:
    T *m_ptr{nullptr};
};
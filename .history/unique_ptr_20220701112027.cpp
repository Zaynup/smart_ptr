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
    T *operator->();
    unique_ptr &operator=(const unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &&) = delete;

    T *get();
    T *release();
    void reset();

private:
    T *m_ptr;
};
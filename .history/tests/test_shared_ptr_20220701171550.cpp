#include "../src/shared_ptr.h"
#include <iostream>
#include <vector>

void func(shared_ptr<int> p)
{
}

class A
{
public:
    A()
    {
        std::cout << "A::A()" << std::endl;
    }

    ~A()
    {
        std::cout << "A::~A()" << std::endl;
    }

    void Print(void) { std::cout << "I am an A objcet." << std::endl; }
    void PrintData(void) { std::cout << "I am an A objcet. My data is " << m_data << std::endl; }
    void SetData(int data)
    {
        this->m_data = data;
    }

private:
    int m_data = 100;
};

void test_nullptr(void)
{
    //指向空指针的场景
    shared_ptr<A> p;
    auto p1 = p;
    std::cout << "use count:" << p.use_count();
    auto p2(p);
    std::cout << "use count:" << p.use_count();
}

void test_A(void)
{
    //指向动态对象的场景
    shared_ptr<A> p(new A);
    auto p1 = p;
    std::cout << "use count:" << p.use_count();

    auto p2(p);
    std::cout << "use count:" << p.use_count();
}

shared_ptr<A> test_create(void)
{
    shared_ptr<A> p(new A);
    return p;
}

std::vector<shared_ptr<A>> test_STL(void)
{
    std::vector<shared_ptr<A>> listA;
    for (int i = 0; i < 2; ++i)
    {
        listA.push_back(shared_ptr<A>(new A));
    }
    return std::move(listA);
}

int main()
{
    // shared_ptr<int> p = new int(1024);
    shared_ptr<int> p(new int(1024));
    if (p)
    {
    }

    const shared_ptr<int> p2{new int{1024}};
    *p2;

    shared_ptr<const int> p3{new int{1024}};

    // explicit shared_ptr(T * ptr) 不能隐式转换
    // func(new int{1024});

    test_nullptr();
    // test_A();
    // auto p = test_create();
    // p->PrintData();
    // auto listA = test_STL();
    // auto p1 = p;
    // p->Print();
    // p1->Print();
    // (*p).Print();

    return 0;
}

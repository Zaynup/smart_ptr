#include "../src/shared_ptr.h"
#include <iostream>
#include <vector>

void func(shared_ptr<int> p)
{
}

class A
{
public:
    A();
    ~A();
    void Print(void) { std::cout << "I am an A objcet." << std::endl; }
    void PrintData(void) { std::cout << "I am an A objcet. My data is " << m_data << std::endl; }
    void SetData(int data);

private:
    int m_data = 100;
};
A::A()
{
    std::cout << "A::A()" << std::endl;
}
A::~A()
{
    std::cout << "A::~A()" << std::endl;
}
void A::SetData(int data)
{
    this->m_data = data;
}

void test_nullptr(void)
{
    //指向空指针的场景
    my_shared_ptr<A> p;
    auto p1 = p;
    auto p2(p);
}

void test_A(void)
{
    //指向动态对象的场景
    my_shared_ptr<A> p(new A);
    auto p1 = p;
    auto p2(p);
}

my_shared_ptr<A> test_create(void)
{
    my_shared_ptr<A> p(new A);
    return p;
}

std::vector<my_shared_ptr<A>> test_STL(void)
{
    std::vector<my_shared_ptr<A>> listA;
    for (int i = 0; i < 2; ++i)
    {
        listA.push_back(my_shared_ptr<A>(new A));
    }
    return std::move(listA);
}

int main(int argv, char *argc[])
{
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
    test_A();
    auto p = test_create();
    p->PrintData();
    auto listA = test_STL();
    auto p1 = p;
    p->Print();
    p1->Print();
    (*p).Print();

    return 0;
}

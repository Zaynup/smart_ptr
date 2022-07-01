#include "../src/unique_ptr.h"
#include <iostream>
/**
 * 简单的类，将被智能指针使用
 * */
class Test
{
public:
    Test()
    {
        std::cout << "Test class construct" << std::endl;
    }
    ~Test()
    {
        std::cout << "Test class destruct" << std::endl;
    }

    void printSomething()
    {
        std::cout << "Test printSomething " << std::endl;
    }

    void printResource()
    {
        std::cout << "Test printResource " << a << std::endl;
    }

    int getResource()
    {
        return a;
    }

private:
    int a = 10;
};

/**
 * 使用unique_ptr的类
 * */
class PUser
{
public:
    PUser()
    {
        //初始化pTest
        pTest.reset(new Test());
        std::cout << "PUser construct " << std::endl;
    }
    ~PUser()
    {
        std::cout << "PUser destruct" << std::endl;
    }

    //可以在类的各种函数，使用pTest，
    void userTest()
    {
        std::cout << "userTest " << pTest->getResource() << std::endl;
    }

private:
    //典型用法，在一个类中，作为一个类成员变量
    unique_ptr<Test> pTest;
};

/**
 * 主程序入口
 *
 *  */
int main(int argc, char *argv[])
{
    unique_ptr<Test> tPtr1(new Test());
    //以下这两句话，//编译就不通过，因为已经定义， unique_ptr& operator = (const unique_ptr&) noexcept = delete;
    // unique_ptr<Test> tPtr2 = tPtr1;
    // unique_ptr<Test> tPtr3(tPtr1);

    //以下两句话就允许，因为pPtr1做了控制权转移
    unique_ptr<Test> tPtr3(std::move(tPtr1));
    unique_ptr<Test> tPtr4 = std::move(tPtr3);

    // tPtr1->printResource();//这一句就崩溃，因为tPtr1非空，只不过资源完全不能用了
    tPtr1->printSomething(); //这一句不崩溃，tPtr1虽然资源不能用，但是代码段可以调用，只要代码段没有使用到资源

    PUser *pUser = new PUser();
    pUser->userTest();

    return 0;
}

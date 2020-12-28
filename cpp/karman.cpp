#include <iostream>

using namespace std;

struct Unit{
    int data;
};

struct Unit *T = nullptr;
int *testPtr;

void testFun(int *ptr)
{
    cout << "ptr的地址：" << &ptr << endl;
    *ptr=*ptr+1;
    cout << "ptr的值：" << *ptr << endl;
}

void testFun2()
{
    T = new struct Unit;
    T->data = 1;
}

void testFun3(int *ptr)
{
    ptr = new int[1];
    testPtr = ptr;
    *ptr = 2;
    cout << "ptr指向的地址：" << ptr << endl;
}

int main()
{
    // int *mainPtr = nullptr;
    // int a = 1;
    // mainPtr = &a;
    // cout << "Mptr的地址：" << &mainPtr << endl;
    // cout << "a的地址：" << &a << endl;
    // testFun(mainPtr);
    // testFun(&a);

    int *mainPtr = nullptr;
    int a = 1;
    mainPtr = &a;
    cout << "Mptr的地址：" << &mainPtr << endl;
    cout << "a的地址：" << &a << endl;
    testFun3(mainPtr);
    cout << "a的值为：" << a << endl;
    cout << "mainPtr的地址：" << mainPtr << endl;
    testFun3(&a);
    cout << "a的值为：" << a << endl;
    cout << "a的地址：" << &a << endl;

    cout << "testPtr指向的值" << *testPtr << endl;
    // testFun2();
    // cout << T->data << endl;

    system("pause");
    return 0;
}

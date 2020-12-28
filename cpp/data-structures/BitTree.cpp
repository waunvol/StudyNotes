#include <iostream>

using namespace std;
//target=>  创建一个二叉树

struct unit
{
    string data;
    struct unit *right, *left;  //指向左右子树
};

//用递归进行创建
//用递归进行遍历
/*NOTE
    对于没有明确规则地建立二叉树，此方法貌似属于目前尚算简单易懂的建立二叉树的方法。
    就是利用递归的特性，不断层叠下去直到子树输入结束标记。
        1.在主函数中创建一个指向二叉树单元结构体的指针

        2.在CPP中，似乎使用new向堆申请空间时，只能通过指针赋值的方式申请=> typename *ptr = new typename[n];
            所以，在递归调用子函数的时候，我们只能通过指针的形式进行传参

                a)若形参为一级指针时，只能通过 ptr = new typename[n]的方式将指针指向单元地址。但是这实际上
                是将当前函数的 ptr（传入的形参）的这个临时变量的值，改变为 typename[n]的地址，而ptr本该指向
                的值，并无发生变化；

                b)而我们的目标，则是将主函数中的名为top的指针，从无目标，指向子函数中新申请的单元地址。也就是说，
                我们需要在子函数中改变top指针的值。显而易见，在c++中，在子函数中改变实参的方法有两种=>
                    1)形参为指针；
                    2)传引用；
                因此，为了在子函数中，改变top指针的值，就需要将形参变为 top指针的指针。

                c)在主函数中调用 input函数 构造二叉树时，只有第一次调用递归的时候，会对top指针进行重新赋值，后续重复
                调用时，都是用左子树右子树的顶点指针作为传值，所以在递归结束时，top指针正好指向创建的这个二叉树的
                顶点。

*/

void input(struct unit **ptr)
{
    string temp;
    cin >> temp;
    if(temp=="#")
        *ptr = nullptr; //输入特定标识符时，将指向左/右子树的指针变成一个空指针
    else
    //递归创建子树
    {
        *ptr = new struct unit;
        (*ptr)->data = temp;
        
        input(&(*ptr)->left);   //递归创建左子树
        input(&(*ptr)->right);  //递归创建右子树
        }
}

void RunOverTree(struct unit *ptr, int level)
{
    //将数据所在的层数和数据本身的内容打印出来
    if(ptr!=nullptr)
    {
        /*打印操作*/
        string temp_;
        temp_ = ptr->data;
        cout << "data:" << temp_ << endl;
        cout << "level:" << level << endl;
        level++;
        RunOverTree(ptr->left, level);
        RunOverTree(ptr->right,level);
    }

}

int main()
{
    struct unit *top = nullptr;
    input(&top);
    RunOverTree(top, 1);

    system("pause");
    return 0;
}



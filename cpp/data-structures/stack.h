#ifndef STACK_H
#define STACK_H

template<class T>
struct StackUnit
{
    T data;
    StackUnit *next;
};

template<class T>
class stack
{
private:
    StackUnit<T> *head;

public:
    stack(T init_data);
    ~stack();
    void add(T add_data);
    bool del();


};

template<class T>
stack<T>::stack(T init_data)
{
    head = new StackUnit<T>;
    head->data = init_data;
    head->next = nullptr;
}

template<class T>
stack<T>::~stack()
{
    StackUnit<T> *ptr;
    while(1)
    {
        ptr = head;
        if(head->next == nullptr)break;
        head = ptr->next;
        delete ptr;
    } 
}

template<class T>
void stack<T>::add(T add_data)
{
    StackUnit<T> *ptr = new StackUnit<T>;
    ptr->next = head;
    head = ptr;
}

template<class T>
bool stack<T>::del()    //去头
{
    if(head==nullptr)
        return false;
        
    StackUnit<T> *ptr;
    ptr = head;
    head = ptr->next;
    delete ptr;

    return true;
}



#endif
#ifndef MYQUEUE_H_
#define MYQUEUE_H_

template <class T>
struct QueueUnit
{
    T data;
    struct QueueUnit<T> *next=nullptr;
};


template<class T>
class queue
{
private:
    /* data */
public:
    QueueUnit<T> *head;
    QueueUnit<T> *now;
    QueueUnit<T> *iterator;

    queue(T data);
    ~queue();
    void add(T data);
    bool del();
    // T a;
};

template<class T>
queue<T>::queue(T data)
{
    head = new QueueUnit<T>;
    head->data = data;
    now = head;
}

template<class T>
queue<T>::~queue()
{
    QueueUnit<T> *ptr;
    while(1)
    {
        ptr = head;
        if(head->next == nullptr)break;
        head = ptr->next;
        delete ptr;
    } 
}

template<class T>
void queue<T>::add(T data)
{
    now->next = new QueueUnit<T>;
    now = now->next;
    now->data = data;
    now->next = nullptr;
}

template<class T>
bool queue<T>::del()    //去头
{
    if(head == nullptr)
        return false;

    QueueUnit<T> *ptr;
    ptr = head;
    head = ptr->next;
    delete ptr;

    return true;
}

#endif
#include <iostream>
#include "myqueue.h"
// #include <my

using namespace std;
#define targetX 7;
#define targetY 4;

struct map
{
    int weight=1;     //权重
    int x, y;       //mark the coordinate
    int flag=0;       //读写标记
};
map *test_map[8][8];



struct waypoint
{
    waypoint *parent;
    int x, y;
    waypoint *child;
    waypoint *littleBro;
    // waypoint *elderBro;
};

void map_init()
{
    int i, j;
    for (i = 0; i < 8;i++)
    {
        for (j = 0; j < 8; j++)
        {
            test_map[i][j] = new map;
            test_map[i][j]->x = i;
            test_map[i][j]->y = j;
        }
        
    }    
}

waypoint* waypoint_init(map* StartingPoint)
{
    waypoint *ptr = new waypoint;
    ptr->parent = ptr;
    ptr->x = StartingPoint->x;
    ptr->y = StartingPoint->y;
    // ptr->elderBro = nullptr;
    ptr->littleBro = nullptr;
    return ptr;
}

void pushback(queue<map *>* _queue, waypoint* point)
{
    map *ptr_q = _queue->iterator->data;    //ptr for queue
    waypoint *_parent = point;              //mark their parent


    //1.不超界
    //2.未访问
    if(ptr_q->x+1<8 && test_map[ptr_q->x + 1][ptr_q->y]->flag==0)
    {
        _queue->add(test_map[ptr_q->x + 1][ptr_q->y]);
        test_map[ptr_q->x + 1][ptr_q->y]->flag = 1;

        //setup waypoint
        point->child = new waypoint;
        point->child->x = ptr_q->x + 1;
        point->child->y = ptr_q->y;      //mark x and y

        point->child->child = nullptr;
        point->child->littleBro = nullptr;
        point->child->parent = point;
        point = point->child;
    }
    if(ptr_q->y-1>=0 && test_map[ptr_q->x][ptr_q->y - 1]->flag==0)
    {
        _queue->add(test_map[ptr_q->x][ptr_q->y - 1]);
        test_map[ptr_q->x][ptr_q->y - 1]->flag = 1;

        //setup waypoint
        if(point == _parent)
        {
            point->child = new waypoint;
            point->child->x = ptr_q->x;
            point->child->y = ptr_q->y - 1; //mark x and y

            point->child->child = nullptr;
            point->child->littleBro = nullptr;
            point->child->parent = point;
            point = point->child;
        }
        else
        {
            point->littleBro = new waypoint;
            point->littleBro->x = ptr_q->x;
            point->littleBro->y = ptr_q->y - 1;
            point->littleBro->child = nullptr;
            point->littleBro->littleBro = nullptr;
            point->littleBro->parent = _parent;
            point = point->littleBro;
        }
    }
    if(ptr_q->x-1>=0 && test_map[ptr_q->x - 1][ptr_q->y]->flag==0)
    {
        _queue->add(test_map[ptr_q->x - 1][ptr_q->y]);
        test_map[ptr_q->x - 1][ptr_q->y]->flag = 1;

        if(point == _parent)
        {
            point->child = new waypoint;
            point->child->x = ptr_q->x - 1;
            point->child->y = ptr_q->y;      //mark x and y

            point->child->child = nullptr;
            point->child->littleBro = nullptr;
            point->child->parent = point;
            point = point->child;

        }
        else
        {
            point->littleBro = new waypoint;
            point->littleBro->x = ptr_q->x - 1;
            point->littleBro->y = ptr_q->y;

            point->littleBro->child = nullptr;
            point->littleBro->littleBro = nullptr;
            point->littleBro->parent = _parent;
            point = point->littleBro;
        }
    }

    if(ptr_q->y+1<8 && test_map[ptr_q->x][ptr_q->y + 1]->flag==0)
    {
        _queue->add(test_map[ptr_q->x][ptr_q->y + 1]);
        test_map[ptr_q->x][ptr_q->y + 1]->flag = 1;

        if(point == _parent)
        {
            point->child = new waypoint;
            point->child->x = ptr_q->x;
            point->child->y = ptr_q->y + 1;      //mark x and y

            point->child->child = nullptr;
            point->child->littleBro = nullptr;
            point->child->parent = point;
            point = point->child;

        }
        else
        {
            point->littleBro = new waypoint;
            point->littleBro->x = ptr_q->x;
            point->littleBro->y = ptr_q->y + 1;

            point->littleBro->child = nullptr;
            point->littleBro->littleBro = nullptr;
            point->littleBro->parent = _parent;
            point = point->littleBro;
        }
    }

}

/*
void pushback(queue<map *>* _queue, waypoint** point)
{
    map *ptr_q = _queue->iterator->data;    //ptr for queue
    waypoint *_parent = *point;                        //mark their parent

    //1.不超界
    //2.未访问
    if(ptr_q->x+1<8 && ptr_q->flag==0)
    {
        _queue->add(test_map[ptr_q->x + 1][ptr_q->y]);

        //setup waypoint
        (*point)->child = new waypoint;
        (*point)->child->x = ptr_q->x + 1;
        (*point)->child->y = ptr_q->y;      //mark x and y

        (*point)->child->child = nullptr;
        (*point)->child->brother = nullptr;
        (*point)->child->parent = (*point);
        (*point) = (*point)->child;
    }
    if(ptr_q->y-1>=0 && ptr_q->flag==0)
    {
        _queue->add(test_map[ptr_q->x][ptr_q->y - 1]);

        //setup way(*point)
        if((*point) == _parent)
        {
            (*point)->child = new waypoint;
            (*point)->child->x = ptr_q->x;
            (*point)->child->y = ptr_q->y - 1; //mark x and y

            (*point)->child->child = nullptr;
            (*point)->child->brother = nullptr;
            (*point)->child->parent = (*point);
            (*point) = (*point)->child;
        }
        else
        {
            (*point)->brother = new waypoint;
            (*point)->brother->x = ptr_q->x;
            (*point)->brother->y = ptr_q->y - 1;
            (*point)->brother->child = nullptr;
            (*point)->brother->parent = _parent;
            (*point) = (*point)->brother;
        }
    }
    if(ptr_q->x-1>=0 && ptr_q->flag==0)
    {
        _queue->add(test_map[ptr_q->x - 1][ptr_q->y]);
        if((*point) == _parent)
        {
            (*point)->child = new waypoint;
            (*point)->child->x = ptr_q->x - 1;
            (*point)->child->y = ptr_q->y;      //mark x and y

            (*point)->child->child = nullptr;
            (*point)->child->brother = nullptr;
            (*point)->child->parent = (*point);
            (*point) = (*point)->child;
        }
        else
        {
            (*point)->brother = new waypoint;
            (*point)->brother->x = ptr_q->x - 1;
            (*point)->brother->y = ptr_q->y;

            (*point)->brother->child = nullptr;
            (*point)->brother->parent = _parent;
            (*point) = (*point)->brother;
        }
    }

    if(ptr_q->y+1<8 && ptr_q->flag==0)
    {
        _queue->add(test_map[ptr_q->x][ptr_q->y + 1]);
        if((*point) == _parent)
        {
            (*point)->child = new waypoint;
            (*point)->child->x = ptr_q->x;
            (*point)->child->y = ptr_q->y + 1;      //mark x and y

            (*point)->child->child = nullptr;
            (*point)->child->brother = nullptr;
            (*point)->child->parent = (*point);
            (*point) = (*point)->child;
        }
        else
        {
            (*point)->brother = new waypoint;
            (*point)->brother->x = ptr_q->x;
            (*point)->brother->y = ptr_q->y + 1;

            (*point)->brother->child = nullptr;
            (*point)->brother->parent = _parent;
            (*point) = (*point)->brother;
        }
    }
    (*point) = _parent;

}*/

void travel()
{
    queue<map *> BFS_queue(test_map[0][0]); //将起始点加入队列
    BFS_queue.iterator = BFS_queue.head;
    waypoint *way = waypoint_init(test_map[0][0]);

    while(1)
    {
        pushback(&BFS_queue, way);

        BFS_queue.iterator->data->flag = 1;

        if(way->littleBro==nullptr)
        {
            if(way->parent!=way)
            {
                if(way->parent->littleBro!=nullptr)
                    way = way->parent->littleBro->child;
                else    
                    way = way->parent->child->child;    //指向长子的子树              
            }
            else
                way = way->child;
                }
        else
            way = way->littleBro;

        if (BFS_queue.iterator->next == nullptr) //队列扫完则跳出循环
            break;
        if(BFS_queue.iterator->data->x==7 && BFS_queue.iterator->data->y ==4 )
            break;

        BFS_queue.iterator = BFS_queue.iterator->next;
        BFS_queue.del();

    }

    do{
        test_map[way->x][way->y]->weight = 1;
        way = way->parent;
    } while (way!=nullptr);
}



int main()
{
    map_init();
    travel();
    for (int i = 0; i < 8; i++)
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << test_map[i][j]->flag << " ";
    }
    cout << endl;
    cout << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << test_map[i][j]->weight << " ";
    }



        system("pause");
    return 0;
}

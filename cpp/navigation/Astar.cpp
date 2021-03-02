#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;
//set the searching area
/***       A*搜索算法        ***/
//实则加了终点距离权重的迪杰斯特拉算法

#define x_t 4
#define y_t 7       //target x and target y

struct waypoint
{
    int x, y;
    waypoint *front = nullptr;
};

struct graph
{
    int weight=1;     //权重
    int distance = 65535;
    int visit = 0;                //访问标记
    waypoint *way = nullptr;      //路径点

    struct neighbor //定义相邻点结构体
    {
        graph **data;
        neighbor *next=nullptr;
    };
    neighbor *itsNeighbor =nullptr;        //相邻点
};
graph *test_map[8][8];
vector<graph **> ShortPathTable;     //存储目前的最短路径点


void graph_init()
{
    int i, j;
    for (i = 0; i < 8;i++)
    {
        for (j = 0; j < 8; j++)
        {
            test_map[i][j] = new graph;
            test_map[i][j]->way = new waypoint;
            test_map[i][j]->way->x = i;
            test_map[i][j]->way->y = j;

            graph::neighbor **nebPTR;
            nebPTR = &(test_map[i][j]->itsNeighbor);
            //指针指向相邻
            if(i+1<8)
            {
                *nebPTR = new graph::neighbor;
                (*nebPTR)->data = &test_map[i + 1][j];
                nebPTR = &(*nebPTR)->next;
            }
            if(j+1<8)
            {
                *nebPTR = new graph::neighbor;
                (*nebPTR)->data = &test_map[i][j+1];
                nebPTR = &(*nebPTR)->next;
            }
            if(i-1>=0)
            {
                *nebPTR = new graph::neighbor;
                (*nebPTR)->data = &test_map[i - 1][j];
                nebPTR = &(*nebPTR)->next;
            }
            if(j-1>=0)
            {
                *nebPTR = new graph::neighbor;
                (*nebPTR)->data = &test_map[i][j-1];
                nebPTR = &(*nebPTR)->next;
            }
        }
    }  

    
}

int MHTdistance(int x, int y)   //计算曼哈顿距离
{
    x = x_t - x;
    if(x<0)
        x = -x;
    y = y_t - y;
    if(y<0)
        y = -y;
    return x + y;
}

void search(int target_x, int target_y)
{

        graph *now = test_map[0][0];
        now->distance = 0;

        graph *tmp; //用于简化代码
        
        vector<graph **>::iterator i;
        vector<graph **>::iterator shortest;

        do  //搜索邻居最短点
        {
            int min = 65535;

            tmp = *(now->itsNeighbor->data);
            graph::neighbor *nebPTR;
            nebPTR = now->itsNeighbor;
            while(1)
            {
                
                if(tmp->visit==0)
                {
                    min = tmp->weight + MHTdistance(tmp->way->x, tmp->way->y);      //记录最短距离
                    // shortest = tmp;3
                    if(tmp->distance > now->distance + tmp->weight + MHTdistance(tmp->way->x, tmp->way->y))    
                    {
                        tmp->distance = now->distance + tmp->weight + MHTdistance(tmp->way->x, tmp->way->y);    //更新点中的最短距离
                        tmp->way->front = now->way;                     //更新路径
                    }
                    ShortPathTable.push_back(nebPTR->data);     //加入搜索队列
                }
                nebPTR = nebPTR->next;
                if(nebPTR == nullptr)               //跳出条件
                    break;
                tmp = *(nebPTR->data);
            }
            min = 65535;

            for (i = ShortPathTable.begin(); i != ShortPathTable.end();i++)     //挑出距离终点最近点
            {
                // cout << (*(*i))->distance << endl;
                if((*(*i))->distance < min)
                {
                    min = (*(*i))->distance;
                    shortest = i;
                }
            }
            (*(*shortest))->visit = 1;
            now = (*(*shortest));
            ShortPathTable.erase(shortest);     //将已完成搜索点移除队列

        } while (!( now->way->x==target_x && now->way->y==target_y));
        
}




int main()
{
    graph_init();           //初始化地图

    search(x_t, y_t);       //搜索最短路径

    waypoint *tmp = test_map[x_t][y_t]->way;
    while(tmp!=nullptr )        //标记最短路径
    {
        test_map[tmp->x][tmp->y]->weight = 8;
        tmp = tmp->front;
    }

    for (int i = 0; i < 8; i++)     //打印最短路径
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << test_map[i][j]->weight << " ";
    }

    cout << endl;               //虚空分割线
    cout << endl;

    for (int i = 0; i < 8; i++)     //打印搜索范围
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << test_map[i][j]->visit << " ";
    }

    system("pause");
    return 0;
}
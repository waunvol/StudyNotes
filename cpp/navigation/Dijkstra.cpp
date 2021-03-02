#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;
//set the searching area
//实现原理：   原理是基于一个前提：对于一个顶点 A 最短的邻接边 B，从 A 到 B 不可能找到比 AB 更短的路径，因为 AB 已经是最短的了，从其它路径走的话必然经过比 AB 更长的路径。
//            这也是 Dijkstra 不能处理负数的原因。
//            迪杰斯特拉算法主要特点是从起始点开始，采用贪心算法的策略，每次遍历到始点距离最近且未访问过的顶点的邻接节点，直到扩展到终点为止
//            即搜索所有离起点最近的点，直至遍历到终点为止
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
            // test_map[i][j]->itsNeighbor = new graph::neighbor;
            nebPTR = &(test_map[i][j]->itsNeighbor);
            //指针指向相邻
            if(i+1<8)
            {
                *nebPTR = new graph::neighbor;
                (*nebPTR)->data = &test_map[i + 1][j];
                nebPTR = &(*nebPTR)->next;
                // test_map[i][j]->itsNeighbor->data = &test_map[i + 1][j];
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
                // test_map[i][j]->itsNeighbor->data = &test_map[i - 1][j];
            }
            if(j-1>=0)
            {
                *nebPTR = new graph::neighbor;
                (*nebPTR)->data = &test_map[i][j-1];
                nebPTR = &(*nebPTR)->next;
                // test_map[i][j]->itsNeighbor->data = &test_map[i][j-1];
            }
        }
    }  

    
}

void search(int target_x, int target_y)
{

        graph *now = test_map[0][0];
        now->distance = 0;

        // do
        // {
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
                
                if(tmp->visit==0)   //若点未搜索过
                {
                    min = tmp->weight;      //记录当前最小
                    // shortest = tmp;3
                    if(tmp->distance > now->distance + tmp->weight)    
                    {
                        tmp->distance = now->distance + tmp->weight;    //更新点中的最短距离
                        tmp->way->front = now->way;                     //更新路径
                    }
                    ShortPathTable.push_back(nebPTR->data);         //加入下一轮迭代
                }
                nebPTR = nebPTR->next;
                if(nebPTR == nullptr)       //跳出条件
                    break;
                tmp = *(nebPTR->data);
            }
            min = 65535;

            for (i = ShortPathTable.begin(); i != ShortPathTable.end();i++)     //从搜索队列中找出当前最近点
            {
                // cout << (*(*i))->distance << endl;
                if((*(*i))->distance < min)
                {
                    min = (*(*i))->distance;
                    shortest = i;
                }
            }
            (*(*shortest))->visit = 1;      //标记搜索标志
            now = (*(*shortest));
            ShortPathTable.erase(shortest);     //从搜索队列中删除

        } while (!( now->way->x==target_x && now->way->y==target_y));

}



int main()
{
    graph_init();
    search(x_t, y_t);   //搜索最短路径
    waypoint *tmp = test_map[x_t][y_t]->way;

    while(tmp!=nullptr )    //路径标记
    {
        test_map[tmp->x][tmp->y]->weight = 8;
        tmp = tmp->front;
    }

    for (int i = 0; i < 8; i++)     //打印路径
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << test_map[i][j]->weight << " ";
    }

    cout << endl;       //虚空分割线
    cout << endl;

    for (int i = 0; i < 8; i++)     //打印搜索足迹
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << test_map[i][j]->visit << " ";
    }

    system("pause");
    return 0;
}
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<queue>
#include<stack>
int visited[100] = {0};
typedef char VertexType;
typedef int EdgeType;
typedef struct EdgeNode{
    int adjvex; //存放邻接点下标
    EdgeNode * next;
}EdgeNode;
typedef struct VertexNode{
    VertexType data; //存放顶点数据
    EdgeNode * firstEdge;//存放边表头
}VertexNode;
typedef struct{
    VertexNode * adjList;
    int vertexNum;
    int edgeNum;
}GraphAdjList;
//定位index
int locateVex(GraphAdjList * g,char x){
    for(int i = 0; i <g->vertexNum;i++){
        if(g->adjList[i].data==x)
        return i;
    }
    return 0;
}
void createGraph(GraphAdjList * g){
    printf("请输入顶点数和边数：");
    scanf("%d%d",&g->vertexNum,&g->edgeNum);
    getchar();
    g->adjList = (VertexNode*)malloc(g->vertexNum *sizeof(VertexNode));
    for(int i =  0; i < g->vertexNum;i++){
        printf("请输入顶点元素 Vertex[%d]：",i+1);
        scanf("%c",&g->adjList[i].data);
        getchar();
        g->adjList[i].firstEdge = NULL;
    }
    //Create 边表
    char x,y;
    EdgeNode * e;
    for(int i = 0; i < g->edgeNum; i++){
        printf("请输入顶点与顶点之间的关系【逗号隔开】(Vi,Vj):");
        scanf("%c,%c",&x,&y);
        getchar();
        e = (EdgeNode*)malloc(sizeof(EdgeNode));
        e->adjvex = locateVex(g,y);
        //头插
        e->next = g->adjList[locateVex(g,x)].firstEdge;
        g->adjList[locateVex(g,x)].firstEdge = e;
        //以下代码 有向图 不需要 ， 无向图要。
        e = (EdgeNode*)malloc(sizeof(EdgeNode));
        e->adjvex = locateVex(g,x);
    
        e->next = g->adjList[locateVex(g,y)].firstEdge;
        g->adjList[locateVex(g,y)].firstEdge = e;
        
        printf("AdjList表示:\n");
        for (int i = 0; i < g->vertexNum; i++){
            e = g->adjList[i].firstEdge;
            while (e){
                printf("(%c,%c)", g->adjList[i].data, g->adjList[e->adjvex].data);
                e = e->next;
            }
            printf("\n");
        }
    }
    return;
}
void BFS(GraphAdjList * g){
    std::queue<int> q;
    for(int i = 0;i < g->vertexNum; i++){
        if(!visited[i]){
            visited[i] = 1;
            printf("%c  ",g->adjList[i].data);
            q.push(i);
            while(!q.empty()){
                q.pop();
                EdgeNode * e = g->adjList[i].firstEdge;
                while (e)
                {
                    if(!visited[e->adjvex]){
                        visited[e->adjvex] = 1;
                        printf("%c  ",g->adjList[e->adjvex]);
                        q.push(e->adjvex);
                    }
                    e = e->next;
                }
            }
        }
    }
    return;
}
void DFS(GraphAdjList *G, int i){
    EdgeNode *p;
    visited[i] = 1;
    printf("%c  ", G->adjList[i].data);
    p = G->adjList[i].firstEdge;
    while(p){
        if(!visited[p->adjvex]){
            DFS(G, p->adjvex);
        }
        p = p->next;
    }
}
void DFSTraverse(GraphAdjList *G){
    int i;
    for(i = 0; i < G->vertexNum; i++){
        visited[i] = 0;
    }
    for(i = 0; i < G->vertexNum; i++){
        if(!visited[i]){
            DFS(G, i);
        }
    }
}
void  MenuGraph()                                     /*显示菜单子函数*/
{   printf("\n                    图子系统");
    printf("\n =================================================");  
    printf("\n|               1——创建图-邻接表法显示         |");
    printf("\n|               2——广度优先遍历                |");
    printf("\n|               3——深度优先遍历                |");    
    printf("\n|               0——返回                        |");
    printf("\n ================================================="); 
    printf("\n请输入菜单号（0-3）:"); 	
}
int Graph()
{
    GraphAdjList g;
    int choice;
    char ch1 = 'Y';
    while(ch1=='y'||ch1=='Y')
    {
        MenuGraph();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
            case 1:
            createGraph(&g);
            break;
            case 2:
            printf("BFS:");
            BFS(&g);
            break;
            case 3:
            printf("DFS:");
            DFSTraverse(&g);
            break;
            case  0:
             ch1= 'n';break;
            default:
                ch1= 'n';
                printf("输入有误！"); 
        }
    }
    return 0;
}


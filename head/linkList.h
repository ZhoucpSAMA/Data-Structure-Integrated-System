#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct StackNode
{
    int data;   //数据域
    struct StackNode * point_Next;  //指针域
}NODE , * POINT_NODE; 

POINT_NODE creat_list()
{
    int len; //长度 
    int val; //临时存放数据

    POINT_NODE pHead = (POINT_NODE)malloc(sizeof(NODE));//分配一个临时头结点
    if(NULL == pHead)
    {
        printf("临时头结点分配失败！程序终止···");
        exit(-1);
    }
    POINT_NODE pTail = pHead; //pTail永远指向最后一个结点
    pTail->point_Next = NULL;

    printf("输入所需要生成链表结点的个数：len = ");
    scanf("%d",&len);

    for(int i = 0; i < len; i++)
    {
        printf("请输入第%d个结点的数据值：",i+1);
        scanf("%d",&val);

        POINT_NODE pNEW = (POINT_NODE)malloc(sizeof(NODE));
        if(NULL == pNEW)
        {
            printf("分配失败！程序终止···");
            exit(-1);
        }
        //尾插法
        pNEW->data = val; //把数据传给一个新结点的数据域
        pTail->point_Next = pNEW;  //把新结点挂到最后一个结点上 
        pNEW->point_Next = NULL;  //令尾结点为NULL
        pTail = pNEW; //pTail一直指向最后一个结点
        //头插法
        // pNEW->data = val; //把数据传给一个新结点的数据域
        // pNEW->point_Next = pHead->point_Next;  // 把头结点的下一个结点 挂到新结点后面
        // pHead->point_Next = pNEW;  //把新结点挂到头结点    
    }
    return pHead;
}
void traverse_list(POINT_NODE pHead)
{
    POINT_NODE pMove  = pHead->point_Next;
    printf("遍历：");
    while(NULL != pMove)
    { 
        printf("%d   ",pMove->data);
        pMove = pMove->point_Next;
    }
    printf("\n");
}
bool is_Empty(POINT_NODE pHead)
{
    if(NULL == pHead->point_Next)
    return true; //true = 1
    else
    return false;//false = 0
}
int List_Length(POINT_NODE pHead)
{
    int len = 0;
    POINT_NODE pMove = pHead->point_Next;
    while(NULL != pMove)
    {
        len++;
        pMove = pMove->point_Next;
    }
    printf("该表长度：%d\n",len);
    return len;
}
void Sort(POINT_NODE pHead)
{
    int len = List_Length(pHead);
    int t , i ,j;
    POINT_NODE P;
    POINT_NODE Q;
    //选择排序
    for(i=0,P = pHead->point_Next; i<len-1; i++,P=P->point_Next )
    {
        for(j=i+1,Q = P->point_Next; j<len ; j++,Q=Q->point_Next)
        {
            if(P->data > Q->data)
            {
                t = P->data;
                P->data  = Q->data;
                Q->data = t;
            }
        }
    }
    return;
}
//插入
bool insort_List(POINT_NODE pHead, int pos, int val)
{
    int len = 0;
    POINT_NODE p = pHead;
    
    while(NULL != p && pos-1 > len)
    {
        p = p->point_Next;
        ++len;
    }

    if(len > pos-1 || NULL == p)
    return false;

    POINT_NODE pNew = (POINT_NODE)malloc(sizeof(NODE));
    if(NULL == pNew) 
    {
        printf("动态分配内存失败！");
        exit(-1);
    }
//插入关键步骤
//将后面结点放在临时变量t，将新结点插入phead和phead->next中间
    POINT_NODE temp = p->point_Next; 
    pNew->data = val; //数据
    p->point_Next = pNew;
    pNew->point_Next = temp;
    return true;
}
int FindPOS(POINT_NODE pHead, int pos)
{
    int i = 0;
    POINT_NODE p = pHead;
    
    while(NULL != p && pos-1 > i)
    {
        p = p->point_Next;
        ++i;
    }
    if(i > pos-1 || NULL == p)
    return -1;
    printf("位置%d的数据为%d\n",pos,p->point_Next->data);
    return p->point_Next->data;
}
//按内容查找
int FindPosByData(POINT_NODE pHead,int e)
{
    POINT_NODE p;//定义一个指向单链表的结点的指针p
    int i;
    if(is_Empty(pHead))//非空判断
    return 0;
    p =pHead->point_Next;//指针p指向一个结点
    i =1;
    while(p)
    {
        if(p->data==e)
        {
            printf("查找数据的Index：%d\n",i);
            return i;
        }
        else
        {
            p=p->point_Next;//指向下一个结点
            i++;
        }
    }
    if(!p)//如果没有找到与e相等的元素
    return 0;
    return i;
}
bool del_List(POINT_NODE pHead, int pos, int * pVal)
{
    int i = 0;
    POINT_NODE p = pHead;
    //找到pos-1的值
    while(NULL != p->point_Next && pos-1 > i)
    {
        p = p->point_Next;
        ++i;
    }

    if(i > pos-1 || NULL == p->point_Next)
    return false;

    //删除操作
    POINT_NODE t = p->point_Next;
    *pVal = p->point_Next->data;
    printf("被删除的数据:%d",*pVal); //返回删除的数据
    p->point_Next  = p->point_Next->point_Next;
    if(NULL != t)
    free(t);
    t = NULL;
    return true;
}
void  menuLinkList() /*显示菜单*/
{   /*显示菜单子函数*/
	printf("\n                  线性表子系统");
    printf("\n =================================================");  
    printf("\n|               1——建立                        |");
    printf("\n|               2——插入                        |");
    printf("\n|               3——删除                        |");
    printf("\n|               4——按位置查找                  |");
    printf("\n|               5——按元素值查找                |");
    printf("\n|               6——求表长                      |");
    printf("\n|               7——排序                        |");
    printf("\n|               0——返回                        |");
    printf("\n ================================================="); 
    printf("\n请输入菜单号（0-7）:"); 	
    return;
}
void insortTips(int *pos,int *data)
{
    printf("请输入插入的位置：");
    scanf("%d",pos);
    printf("\n请输入插入的数：");
    scanf("%d",data);
}
void delTips(int *pos,int *data)
{
    printf("请输入删除的位置：");
    scanf("%d",pos);
}
void find1Tips(int *pos)
{
    printf("请输入查找的位置：");
    scanf("%d",pos);
}
void find2Tips(int *val)
{
    printf("请输入查找的数据：");
    scanf("%d",val);
}

int linkList()
{
    POINT_NODE p_Head = NULL; // 等价于 struct StackNode p_Head = NULL;
    int val; //带回数据
    int choice;
    int pos;
    int data;
    char ch1 = 'Y';
    char a;
   
    while(ch1=='y'||ch1=='Y')
    {
         menuLinkList();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
            case 1:
            p_Head = creat_list();
            traverse_list(p_Head);
              break;
            case 2:
            insortTips(&pos,&data);
            insort_List(p_Head,pos,data);
            traverse_list(p_Head);
              break;
            case 3:
            delTips(&pos,&data);
            del_List(p_Head,pos,&val);
            traverse_list(p_Head);
               break;
            case 4:
            find1Tips(&pos);
            FindPOS(p_Head,pos);
              break;
            case 5:
            find2Tips(&val);
            FindPosByData(p_Head,val);
              break;
            case 6:
            List_Length(p_Head);
              break;
            case 7:Sort(p_Head);
            traverse_list(p_Head);
               break;
            case 0:ch1 = 'n';break;
            default:ch1 = 'n';printf("输入有误！");break;
        }
    }
    return 0;
}


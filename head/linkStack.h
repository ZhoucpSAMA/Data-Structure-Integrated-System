#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stack>
#include<string.h>
using namespace std;
typedef struct ListNODE
{
    int data;
    struct ListNODE * next;
}NODE_S,* P_NODE_S;

typedef struct Stack
{
    P_NODE_S pTOP;  //指向栈顶
    P_NODE_S pButtom; //指向栈底
    int len;
}STACK,* P_STACK;

void initStack(P_STACK pStack)
{
    P_NODE_S pHead = (P_NODE_S)malloc(sizeof(NODE_S));
    if(!pHead)
    {
        printf("动态内存分配失败！\n");
        exit(-1);
    }
    else
    {
        pStack->pButtom = pStack->pTOP = pHead;
        pHead->next = NULL;
        pStack->len = 0;
    }
    printf("初始化栈成功！\n");
    return;
}

bool push(P_STACK pStack,int data)
{
    P_NODE_S pNew = (P_NODE_S)malloc(sizeof(NODE_S));
    if(pNew)
    {
        pNew->data = data;  //把所需插入的数据赋给新结点的数据域
        pNew->next = pStack->pTOP;  // 把栈顶的结点地址赋给新结点指针域
        pStack->pTOP = pNew; // 把栈顶向上移动 指向最上面的结点
        printf("push:%d\n",data);
        pStack->len++;
        return true;
    }
    else
    {
        printf("新结点内存分配失败！\n");
        return false;
    }
}

void traverseStack(P_STACK pStack)
{
    P_NODE_S pMove = pStack->pTOP; //定义一个移动的结点
    printf("遍历：");
    while (pStack->pButtom != pMove) //当栈顶不等于栈底
    {
        printf("%d   ",pMove->data);
        pMove = pMove->next;//把下一个结点的地址赋给pMove
    }
    printf("\n");
    return;
}

bool is_emptyStack(P_STACK pStack)  //判断栈是否为空
{
    if(pStack->pTOP == pStack->pButtom)
    return true;
    else
    return false;
}
bool pop(P_STACK pStack,int * pData) 
//把pStack所指向的栈出栈一次，并把出栈元素赋给*pData
{
    if(is_emptyStack(pStack))
    {
        return false;
    }
    else
    {
        P_NODE_S pMove = pStack->pTOP;

        (*pData) = pMove->data;
        printf("pop:%d",*pData);
        pStack->pTOP = pMove->next;
        free(pMove);
        pMove = NULL;
        pStack->len--;
        return true;
    }
}

void clear(P_STACK pStack) //循环出栈
{
    while(!is_emptyStack(pStack))
    {
        P_NODE_S pMove = pStack->pTOP;
        pStack->pTOP = pMove->next;
        free(pMove);
        pMove = NULL;
    }
    pStack->len = 0;
    printf("清空成功！\n");
    return;
}
int GetTop(P_STACK pStack)
{
    if(!is_emptyStack(pStack))
    {
        printf("Top：%d",pStack->pTOP->data);
        return pStack->pTOP->data;
    }
    else
    printf("这是空栈！\n");
    return 0;
}
int Stack_Length(P_STACK pStack)
{
    int len = 0;
    P_NODE_S pMove = pStack->pTOP;
    while(pMove!=pStack->pButtom)
    {
        len++;
        pMove = pMove->next;
    }
    return len;
}
void Transform_Base(int data)
{
    stack<int> s;
    int t,num1,num2,figure = data;
    int len;
    while(figure)
    {
        num1 = figure/2;
        num2 = figure%2;
        s.push(num2);
        figure = num1;
    }
    printf("DEC：%d ——>BIN：",data);
    len = s.size();
    if(len>4&&len<8) //补齐前面的0
    printf("0");
    if(len>8&&len<12)
    printf("00");
    while(!s.empty())
    {
        t = s.top();
        s.pop();
        printf("%d",t);
    }
    printf("\n");
    //10 -> 8
    figure = data;
    while(figure)
    {
        num1 = figure/8;
        num2 = figure%8;
        s.push(num2);
        figure = num1;
    }
    printf("DEC：%d ——>OCT：",data);
    for(;!s.empty();)
    {
       t = s.top();
        s.pop();
        printf("%o",t);
    }
    printf("\n");
    //10->16
    figure = data;
    while(figure)
    {
        num1 = figure/16;
        num2 = figure%16;
        s.push(num2);
        figure = num1;
    }
    printf("DEC：%d ——>HEX：",data);
    while(!s.empty())
    {
        t = s.top();
        s.pop();
        printf("%X",t);
    }
    printf("\n");
    return;
}
void startTransform()
{
    int data;
    printf("请输入一个十进制数：");
    scanf("%d", &data);
    Transform_Base(data);
}
bool is_Digital(char c)
{
    if(c>='0'&&c<='9')
    return true;
    else
    return false;
}
int calcFx()
{
    stack<int> s;
    char data[100] = "\0";
    printf("请输入表达式：");
    scanf("%s",data);
    int res = 0, cur = 0; //结果/当前数
    char sign = '+';      //符号位默认
    int t;
    int len = strlen(data);
    for(int i = 0; i < len; i++)
    {
        char c = data[i];
        if(c==' ')
        continue;
        if(is_Digital(c))
        cur = cur * 10+(c - '0'); //char转int
        if((!is_Digital(c)&&c!=' ')||i==len-1) //如果是最后一个 说明没了
        {
            int pre;
            switch (sign)
            {
            case '+':
                s.push(cur);
                break;
            case '-':
                s.push(-cur);
                break;
            case '*':
                pre = s.top();
                s.pop();
                s.push(pre*cur);
                break;
            case '/':
                pre = s.top();
                s.pop();
                s.push(pre/cur);
                break;
            }//switch
            sign = c;
            cur = 0;
        }//if
    }//for
    for(;!s.empty();s.pop())
    res+=s.top();
    printf("%s = %d\n",data,res);
    return res;
}
void  MenuStack()                                    
{   /*显示菜单子函数*/ 
	printf("\n                     栈子系统");
    printf("\n =================================================");  
    printf("\n|               1——初始化栈                    |");
    printf("\n|               2——入栈操作                    |");
    printf("\n|               3——出栈操作                    |");
    printf("\n|               4——求栈顶元素                  |");
    printf("\n|               5——显示栈中元素                |");
    printf("\n|               6——二、八、十六进制转换        |");
    printf("\n|               7——表达式转换并求值            |");
    printf("\n|               0——返回                        |");
    printf("\n ================================================="); 
    printf("\n请输入菜单号（0-7）:"); 	
}
void pushTips(int *val)
{
    printf("请输入入栈的数据：");
    scanf("%d",val);
}
int linkStack()
{
    STACK Stack; //struct stack S;
    int val; 
    int choice;
    char ch1 = 'Y';
    while(ch1=='y'||ch1=='Y')
    {
        MenuStack();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
            case 1:
            initStack(&Stack);
              break;
            case 2:
            pushTips(&val);
            push(&Stack,val);
            traverseStack(&Stack);
              break;
            case 3:
            pop(&Stack,&val);
              break;
            case 4:
            GetTop(&Stack);
              break;
            case 5:
            traverseStack(&Stack);
              break;
            case 6:
            startTransform();
              break;
            case 7:
            calcFx();
              break;
            case 0:ch1 = 'n';break;
            default:ch1 = 'n';printf("输入有误！");break;
        }
    }
    return 0;
}
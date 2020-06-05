#include<stdio.h>
#include<stdlib.h>
#include"linkList.h"
#include"linkStack.h"
#include"linkQueue.h"
#include"HString.h"
#include"binaryTree.h"
#include"Graph.h"
#include"Search.h"
#include"Sort.h"
#include"StudentManage.h"
void  menuMain() /*显示菜单*/
{
	printf("\n     数据结构系统 - Powered by ZhoucpSAMA");
    printf("\n =======================================");  
    printf("\n|               1——线性表             |");
    printf("\n|               2—— 栈                |");
    printf("\n|               3——队 列              |");
    printf("\n|               4—— 串                |");
    printf("\n|               5——二叉树             |");
    printf("\n|               6—— 图                |");
    printf("\n|               7——查找               |");
    printf("\n|               8——排序               |");
    printf("\n|               9——学生管理系统       |");
    printf("\n|               0——退出               |");
    printf("\n ========================================"); 
    printf("\n请输入菜单号（0-9）:");
    return;
}
int main(){
    int choice;
    while(true)
    {
        menuMain();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
            case 1:linkList();break;
            case 2:linkStack();break;
            case 3:linkQueue();break;
            case 4:HString();break;
            case 5:binaryTree();break;
            case 6:Graph();break;
            case 7:Search();break;
            case 8:Sort();break;
            case 9:StudentManageSystem();break;
            case 0:exit(0);break;
            default:exit(0);break;
        }
    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
typedef struct BTNode{
	char data;
	BTNode *lchild;
	BTNode *rchild;
}BTNode;
int vec_left[100] = {0};
int count=0; //计数
BTNode *createtree()
{
	BTNode *bt;
	char x;
	scanf("%c",&x);
	getchar();	
	if(x=='0')
		bt=NULL;
	else{
		bt=(BTNode*)malloc(sizeof(BTNode));
		bt->data=x;
		printf("请输入%c节点的左子结点\n",bt->data);
		bt->lchild=createtree();
		printf("请输入%c节点的右子结点\n",bt->data);
		bt->rchild=createtree();
	}
	return bt;
}
void preOrder(BTNode *T)
{
	if(T==NULL) return;
	{
		printf("%c ",T->data);
		preOrder(T->lchild);
		preOrder(T->rchild);
	}
}
void inOrder(BTNode *T)
{
	if(T==NULL) return;
	{
		inOrder(T->lchild);
		printf("%c ",T->data);
		inOrder(T->rchild);
	}
}
void postOrder(BTNode *T)
{
	if(T==NULL) return;
	{
		postOrder(T->lchild);
		postOrder(T->rchild);
		printf("%c ",T->data);
	}
}
//5层次遍历
void levelorder(BTNode *T)
{
	int i,j;
	BTNode *q[100],*p;		//定义一个指针数组
	p=T;
	if(p!=NULL){
		i=1;
		q[i]=p;
		j=2;
	}
	while(i!=j){
		p=q[i];
		printf("%c ",p->data);
		if(p->lchild!=NULL){
			q[j]=p->lchild;
			j++;
		}
		if(p->rchild!=NULL){
			q[j]=p->rchild;
			j++;
		}
		i++;
	}
}
//6求叶子数
int leafnum(BTNode *T)		
{
	if(!T)
		return 0;
	else{
		if(T->lchild==NULL && T->rchild==NULL)
			count++;
		leafnum(T->lchild);
		leafnum(T->rchild);
		return count;
	}
}

//7求节点数
int nodenum(BTNode *T)
{
	if(!T)
		return 0;
	else{
		count++;
		nodenum(T->lchild);
		nodenum(T->rchild);
		return count;
	}		
}
//8求树深度
int treedepth(BTNode *T)
{
	int lDepth,rDepth,dep;
	if(T==NULL)
		return 0;
	else{
		lDepth=treedepth(T->lchild);
		rDepth=treedepth(T->rchild);
		dep=lDepth>rDepth?lDepth:rDepth;
		return dep+1;
	}
}
void Display(BTNode* root, int ident)
{
    if(ident > 0)
    {
        for(int i = 0; i < ident - 1; ++i)
        {
            printf(vec_left[i] ? "│   " : "    ");
        }
        printf(vec_left[ident-1] ? "├── " : "└── ");
    }

    if(! root)
    {
        printf("(null)\n");
        return;
    }

    printf("%c\n", root->data);
    if(!root->lchild && !root->rchild)
    return;

    vec_left[ident] = 1;
    Display(root->lchild, ident + 1);
    vec_left[ident] = 0;
    Display(root->rchild, ident + 1);
}
void  MenuTree()                                     /*显示菜单子函数*/
{
	printf("\n                  二叉树子系统");
    printf("\n =================================================");  
    printf("\n|               1——建立一个新二叉树            |");
    printf("\n|               2——先序遍历                    |");
    printf("\n|               3——中序遍历                    |");
    printf("\n|               4——后序遍历                    |");
    printf("\n|               5——层次遍历                    |");
    printf("\n|               6——求叶子结点数目              |");
    printf("\n|               7——求二叉树总结点数目          |");
    printf("\n|               8——求树深度                    |");
	printf("\n|               9——图形化表示二叉树            |");
    printf("\n|               0——返回                        |");
    printf("\n ================================================="); 
    printf("\n请输入菜单号（0-8）:"); 	
}
int binaryTree()
{
	BTNode * bt;
	int choice;
	char ch1 = 'Y';
	while(ch1=='Y'||ch1=='y'){
		MenuTree();
		scanf("%d",&choice);
		getchar();		
		switch(choice){
			case 1: 
				printf("请按先序序列输入二叉树的节点。说明：输入节点（‘0’表示后继节点为空）后按回车\n");		//提示不可少	
				printf("请输入根节点：");
				bt=createtree();
				printf("二叉树成功建立!\n");break;		
			case 2: 
				printf("该二叉树的先序遍历序列为：");
				preOrder(bt); 
				printf("\n");break;
			case 3: 
				printf("该二叉树的中序遍历序列为：");
				inOrder(bt); 
				printf("\n");break;
			case 4: 
				printf("该二叉树的后序遍历序列为：");
				postOrder(bt); 
				printf("\n");break;
			case 5: 
				printf("该二叉树的层次遍历序列为：");
				levelorder(bt); 
				printf("\n");break;
			case 6: 
				count=0;				
				printf("该二叉树有%d个叶子\n",leafnum(bt));break;
			case 7: 
				count=0;	
				printf("该二叉树总共有%d个节点\n",nodenum(bt));break;
			case 8:
				printf("该二叉树的深度是：%d\n",treedepth(bt));break;
			case 9:
				Display(bt,0);break;
 
			case 0:ch1 = 'n';break;
		}
	}
	return 0;
}
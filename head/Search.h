#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
//分块查找索引表
struct BlockTable
{
    int key;
    int start;
    int length;
};
//二叉搜索树
struct BSTNode
{
    int data;
    struct BSTNode *pLeft;
    struct BSTNode *pRight;
    struct BSTNode *pParent;
};
int NodeNums = 0;//节点数量
//先序
void PreTraverseBSTree(struct BSTNode *pBST)
{
    if(NULL != pBST)
    {
        printf("数据为：%d->父节点地址为：%p\n",pBST ->data,pBST ->pParent);
        if(NULL != pBST ->pLeft )
            PreTraverseBSTree(pBST ->pLeft);
        if(NULL != pBST ->pRight)
            PreTraverseBSTree(pBST ->pRight);
    }
}
//中序
void InTraverseBSTree(struct BSTNode *pBST)
{
    if(NULL != pBST)
    {
        if(NULL != pBST ->pLeft )
            PreTraverseBSTree(pBST ->pLeft);
        printf("数据为：%d->父节点地址为：%p\n",pBST ->data,pBST ->pParent);
        if(NULL != pBST ->pRight)
            PreTraverseBSTree(pBST ->pRight);
    }
}
//后序
void PostTraverseBSTree(struct BSTNode *pBST)
{
    if(NULL != pBST)
    {
        if(NULL != pBST ->pLeft )
            PreTraverseBSTree(pBST ->pLeft);
        if(NULL != pBST ->pRight)
            PreTraverseBSTree(pBST ->pRight);
        printf("数据为：%d->父节点地址为：%p\n",pBST ->data,pBST ->pParent);
    }
}
//查找成功返回该结点的地址，失败返回NULL
struct BSTNode *SearchBSTree(struct BSTNode *pBST,int key)
{
    while(NULL != pBST && key != pBST ->data)
    {
        if(key < pBST ->data)
            pBST = pBST ->pLeft;
        else 
        pBST = pBST ->pRight;
    }
    return pBST;
}
//查找二叉搜索树中最小的值
struct BSTNode *SearchMinBSTree(struct BSTNode *pBST,int *pMinData)
{
    while(NULL != pBST ->pLeft)
    {
        pBST = pBST ->pLeft;
    }
    *pMinData = pBST ->data;
    return pBST;
}
 //查找二叉搜索树中最大的值
struct BSTNode *SearchMaxBSTree(struct BSTNode *pBST,int *pMaxData)
{
    while(NULL != pBST ->pRight)
    {
        pBST = pBST ->pRight;
    }
    *pMaxData = pBST ->data;
    return pBST;
}
//插入元素
void InsertBSTree(struct BSTNode *pBST,int InsertVal) 
{
    struct BSTNode *pRoot = pBST;//记录根节点地址
    struct BSTNode *pNew = (struct BSTNode *)malloc(sizeof(struct BSTNode));
    if(NULL == pNew)
        exit(-1);
    pNew ->data = InsertVal;
    pNew ->pLeft = pNew ->pRight = NULL;
    struct BSTNode *pTmp = NULL;
    while(NULL != pBST )
    {
        pTmp = pBST;
        if(pNew ->data < pBST ->data)
            pBST = pBST ->pLeft;
        else
            pBST = pBST ->pRight;
    }
    pNew->pParent = pTmp;
    if(NULL == pTmp)  //当树为空时，将插入节点的地址赋给根节点
        *pRoot = *pNew;
    else if(pNew ->data <= pTmp ->data)
        pTmp ->pLeft = pNew;
    else
        pTmp ->pRight = pNew;
}
void DeleteBSTree(struct BSTNode *pBST,int DeleteVal)
{
    struct BSTNode *pTemp = SearchBSTree(pBST,DeleteVal);
    if(pTemp == NULL)
    {
        printf("没有找到要删除的元素！\n");
        exit(-1);
    }

    if(NULL == pTemp ->pLeft && NULL == pTemp ->pRight) //删除节点无左右孩子
    {
        if(pTemp == pTemp ->pParent ->pLeft)  //删除节点是其父节点的左孩子
        {
            pTemp ->pParent ->pLeft = NULL;
        }
        else              //删除节点是其父节点的右孩子
        {
            pTemp ->pParent ->pRight =NULL;
        }
        free(pTemp);
        pTemp = NULL;
    }

    else if(NULL == pTemp ->pLeft)    //删除节点无左孩子
    {
        if(pTemp == pTemp ->pParent ->pLeft)  //删除节点为其父节点的左孩子
        {
            pTemp ->pParent ->pLeft = pTemp ->pRight;
            pTemp ->pRight ->pParent =pTemp ->pParent;
        }
        else                                 //删除节点为其父节点的右孩子
        {
            pTemp ->pParent ->pRight = pTemp ->pRight;
            pTemp ->pRight ->pParent =pTemp ->pParent;
        }
        free(pTemp);
        pTemp = NULL;
    }

    else if(NULL == pTemp ->pRight) //删除节点无右孩子
    {
        if(pTemp == pTemp ->pParent->pLeft)  //删除节点为其父节点的左孩子
        {
            pTemp ->pParent ->pLeft = pTemp ->pLeft;
            pTemp ->pLeft ->pParent = pTemp ->pParent;
        }
        else   //删除节点为其父节点的右孩子
        {
            pTemp ->pParent ->pRight = pTemp ->pLeft;
            pTemp ->pLeft ->pParent = pTemp ->pParent;
        }
        free(pTemp);
        pTemp = NULL;
    }
    else    //删除节点有左右孩子，用删除节点左字树中的最大值或者右子树中最小值来代替删除节点
            //本例中用右子树中最小值来代替
    {
        struct BSTNode *pTail = pTemp ->pRight;
        while(NULL != pTail ->pLeft)  //查找右子树中的最小值
        {
               pTail = pTail ->pLeft;
        }
        if(pTemp == pTail ->pParent)  //右子树中的最小值的父节点是删除节点
        {
            if(pTemp == pTemp ->pParent ->pLeft)  //删除节点为其父节点的左孩子
            {
                pTemp ->pParent ->pLeft = pTail;
                pTail ->pLeft = pTemp ->pLeft;
                pTemp ->pLeft->pParent = pTail;
            }
            else
            {
                pTemp ->pParent ->pRight = pTail;
                pTail ->pLeft = pTemp ->pLeft;
                pTemp ->pLeft->pParent = pTail;
            }
            free(pTemp);
            pTemp = NULL;
        }
        else
        {
            pTail ->pRight ->pParent = pTail ->pParent;
            pTail ->pParent ->pLeft = pTail ->pRight;
            pTail ->pParent ->pParent = pTail;
            pTail ->pRight = pTail ->pParent;
            pTail ->pLeft = pTemp ->pLeft;
            pTemp ->pLeft ->pParent = pTail;
            if(pTemp == pTemp ->pParent ->pLeft)
            {
                pTemp ->pParent ->pLeft = pTail;
            }
            else
            pTemp ->pParent ->pRight = pTail;
            free(pTemp);
            pTemp = NULL;
        }
    }
}
struct BSTNode * createBSTree()
{
	struct BSTNode * curBST;
	int x;
	scanf("%d",&x);
	getchar();
	if(x == 0)
    {
		curBST = NULL;
    }
	else{
		curBST=(BSTNode *)malloc(sizeof(BSTNode));
		curBST->data=x;
        NodeNums++;
		printf("请输入%d节点的左子结点\n",curBST->data);
		curBST->pLeft=createBSTree();
		printf("请输入%d节点的右子结点\n",curBST->data);
		curBST->pRight=createBSTree();
	}
	return curBST;
}
void inputParent(struct BSTNode *pBST)
{
    struct BSTNode * curBST;
    int key, parent;
    printf("请分别输入各个元素的父节点[元素 父节点]:\n");
    for(int i = 0; i < NodeNums; i++)
    {
        scanf("%d %d",&key, &parent);
        struct BSTNode * curAddress = SearchBSTree(pBST,key);
        struct BSTNode * ParentAddress = SearchBSTree(pBST,parent);
        curAddress->pParent = ParentAddress;
    }
    return ;
}
void MenuBSTree()
{   /*显示二叉排序树子菜单函数*/
    printf("\n                      二叉排序树       ");
    printf("\n==================================================");
    printf("\n|               1------建立二叉排序树            |");
    printf("\n|               2------插入一个元素              |");
    printf("\n|               3------删除一个元素              |");
    printf("\n|               4------查找一个元素              |");
    printf("\n|               5------  先序遍历                |");
    printf("\n|               6------  中序遍历                |");
    printf("\n|               7------  后序遍历                |");
    printf("\n|               8------  求最大值                |");
    printf("\n|               9------  求最小值                |");
    printf("\n|               0------返回                      |");
    printf("\n==================================================");
    printf("\n请输入序号（0-9）选择要进行的操作:");
}
void startBST()
{
    struct BSTNode * bst;
    char ch1 = 'Y';
    int choice;
    int InsertVal;
    int DeleteVal;
    int SearchVal;
    int MAXVAL;
    int MINVAL;
    while (ch1 == 'Y' || ch1 == 'y')
    {
        MenuBSTree();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
        case 1:
            printf("请输入根节点：\n");
            bst = createBSTree();
            inputParent(bst);
            break;
        case 2:
            printf("请输入插入的元素:\n");
            scanf("%d",&InsertVal);
            InsertBSTree(bst,InsertVal);
            printf("插入成功!\n");
            break;
        case 3:
            printf("请输入删除的元素:\n");
            scanf("%d",&DeleteVal);
            DeleteBSTree(bst,DeleteVal);
            printf("删除成功!\n");
            break;
            
        case 4:
            printf("请输入查找的元素:\n");
            scanf("%d",&SearchVal);
            printf("查找的数据：%d!\n",SearchBSTree(bst,SearchVal)->data);
            break;
        case 5:
            printf("先序遍历：\n");
            PreTraverseBSTree(bst);
            break;
        case 6:
            printf("中序遍历：\n");
            InTraverseBSTree(bst);
            break;
        case 7:
            printf("后序遍历：\n");
            PostTraverseBSTree(bst);
            break;
        case 8:
            printf("MAX = %d\n",SearchMaxBSTree(bst,&MAXVAL)->data);
            break;
        case 9:
            printf("MIN = %d\n",SearchMinBSTree(bst,&MINVAL)->data);
            break;
        case 0:
            ch1 = 'n';
            break;
        }
    }
    return ;
}
//顺序查找
int SeqSearch(int * arrays, int n,int key)
{
	int i=0;
	arrays[0]=key;//哨兵
	i=n;
	while(arrays[i]!=key)
	i--;
	return i;//0查找失败
}
void startSeqSearch()
{
    int n,data,index;
    printf("请输入元素个数：");
    scanf("%d",&n);
    printf("请分别输入%d个元素数据[int]:\n",n);
    int arrays[n];
    for(int i = 0 ; i < n; i++)
    scanf("%d",&arrays[i]);
    printf("请输入你要查找的数据:");
    scanf("%d",&data);
    index = SeqSearch(arrays, n,data);
    if(index == 0)
    {
        printf("查找失败,无此元素！");
        return;
    }
    printf("查找成功，该元素下标为%d！",index);
}
//折半查找
int BinarySearch(int * arrays,int len , int key)
{
    int index;
    int low = 0;
    int high = len - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if(arrays[mid] == key)
        return mid;
        else if(arrays[mid]>key)
        high = mid - 1;
        else
        low = mid + 1;
    }
    return -1;
}
void startBinarySearch()
{
    int n,data,index;
    printf("请输入元素个数：");
    scanf("%d",&n);
    printf("请分别输入%d个元素数据[升序]:\n",n);
    int arrays[n];
    for(int i = 0 ; i < n; i++)
    scanf("%d",&arrays[i]);
    printf("请输入你要查找的数据:");
    scanf("%d",&data);
    index = BinarySearch(arrays,n,data);
    if(index == -1)
    {
        printf("查找失败,无此元素！");
        return;
    }
    printf("该元素下标为%d!",index);
}
//分块查找
int BlockSearch(int * arrays,struct BlockTable * blockTable,int BlockTableLen,int key)
{
    struct BlockTable * curBlock;
    if(BlockTableLen==1)
    {
        printf("索引表长度不能为1!");
        return -1;
    }
    for(int i = 0; i < BlockTableLen; i++)
    {
        if(key > blockTable[i].key)
        {
            curBlock = &blockTable[i+1];
            break;
        }
        else
        {
            curBlock = &blockTable[i];
            break;
        }
    }
    for(int i = curBlock->start; i < curBlock->start+curBlock->length; i++)
    {
        if(key==arrays[i])
        {
            return i;
        }
    }
    return -1;
}
void startBlockSearch()
{
    int DataNums,BlockTableLen,data;
    printf("请输入元素个数：");
    scanf("%d",&DataNums);
    printf("请分别输入%d个元素数据[int]:\n",DataNums);
    int arrays[DataNums];
    for(int i = 0 ; i < DataNums; i++)
    scanf("%d",&arrays[i]);
    printf("请输入索引表长度:");
    scanf("%d",&BlockTableLen);
    printf("请分别输入索引表[块起始位置,块键最大值,块长度](Space隔开):\n");
    struct BlockTable blockTable[BlockTableLen];
    for(int i = 0; i < BlockTableLen; i++)
    scanf("%d %d %d",&blockTable[i].start,&blockTable[i].key,&blockTable[i].length);
    printf("请输入你要查找的数据:");
    scanf("%d",&data);
    int index = BlockSearch(arrays,blockTable,BlockTableLen,data);
    if(index == -1)
    {
        printf("查找失败！");
        return ;
    }
    printf("该元素下标为%d!",index);
    return ;
}
void  SearchMenu()                                    
{   /*显示菜单子函数*/
	printf("\n                  查找子系统");
    printf("\n==================================================");  
    printf("\n|               1——顺序查找                    |");
    printf("\n|               2——折半查找                    |");
    printf("\n|               3——分块查找                    |");
    printf("\n|               4——二叉树排序树查找            |");
    printf("\n|               0——返回                        |");
    printf("\n=================================================="); 
    printf("\n请输入菜单号（0-4）:"); 	
}
int Search()
{
    char ch1 = 'Y';
    int choice;
    while (ch1 == 'Y' || ch1 == 'y')
    {
        SearchMenu();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
        case 1:
            startSeqSearch();
            break;
        case 2:
            startBinarySearch();
            break;
        case 3:
            startBlockSearch();
            break;
        case 4:
            startBST();
            break;
        case 0:
            ch1 = 'n';
            break;
        }
    }
    return 0;
}
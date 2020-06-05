#include<stdio.h>
int cmp(int a, int b)
{
    return a-b;
}
void swap(int * a,int * b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void PreprintArrays(int * arrays, int len)
{
    printf("排序前:");
    for(int i = 0; i < len ; i++)
    printf("%d  ",arrays[i]);
    printf("\n");
}
//遍历排序后数组
void printArrays(int * arrays, int len)
{
    printf("排序后:");
    for(int i = 0; i < len ; i++)
    printf("%d  ",arrays[i]);
    printf("\n");
}
//冒泡
void BuSort(int * arrays, int len)
{
    for(int end = len - 1; end > 0; end--)
    {
        for(int begin = 1; begin <= end ; begin++)
        {
            if(arrays[begin] < arrays[begin - 1])
            {
                swap(&arrays[begin],&arrays[begin - 1]);
            }
        }
    }
}
//直接选择
void SelectSort(int * arrays, int len)
{
    for(int end = len - 1; end > 0; end--)
    {
        int maxIndex = 0;
        for(int begin = 1; begin <= end; begin++)
        {
            if(arrays[maxIndex] <= arrays[begin])
            maxIndex = begin;
        }
        swap(&arrays[maxIndex],&arrays[end]);
    }
}
//插入排序  从第一个开始 找到合适的位置 插入
void insertSort(int * arrays, int len)
{
	int tmp,i,j;
	for (i = 1;i < len;i++)
	{
		tmp = arrays[i];
		for (j = i - 1;j >= 0 && arrays[j] > tmp;j--)
		{
			arrays[j + 1] = arrays[j];
		}
		arrays[j + 1] = tmp;
	}
}
//快速排序
void QuickSwap(int arr[], int left, int right)
{
    int temp;
    temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
    return;
}
void Partition(int arr[], int left, int right)
{
    int key = arr[left];
    while(left < right)
    {
        while(left < right && arr[right] >= key)
        right --;
        QuickSwap(arr, left, right);
        while(left < right && arr[left] <= key)
        left ++;
        QuickSwap(arr, left, right);
    }
    return;
}
void QuickSort(int arr[], int left, int right)
{
    if(left < right)
    {
        Partition(arr, left, right);
        QuickSort(arr, left, right - 1);
        QuickSort(arr, left + 1, right);
    }
    return;
}
//希尔排序
void ShellSort(int *arrays, int len)
{
    int i, j , temp , Step;
    for (Step = len / 2; Step >= 1; Step /= 2)
    {
        for (i = 0 + Step; i < len; i += Step)
        {
            temp = arrays[i];
            j = i - Step;
            while (j >= 0 && arrays[j] > temp)
            {
                arrays[j + Step] = arrays[j];
                j -= Step;
            }
            arrays[j + Step] = temp;
        }
    }
}
//归并排序
void Merge(int a[], int begin ,int mid, int end)
{
    int leftArrays[end>>1] = {0};
    int leftI = 0, leftEnd = mid - begin;
    int rightI = mid, rightEnd = end;
    int aI = begin;
    for(int i = leftI; i < leftEnd; i++)
    leftArrays[i] = a[begin + i];
    
    while (leftI < leftEnd) //左边未结束
    {
        if((rightI<rightEnd)&&(a[rightI] <= leftArrays[leftI]))
        a[aI++] = a[rightI++];
        else
        a[aI++] = leftArrays[leftI++];
    }
}
void MergeSort(int a[],int begin, int end)
{
    if(end - begin < 2) return ;
    int mid = (begin + end) >> 1;
    MergeSort(a,begin,mid);
    MergeSort(a,mid,end);
    Merge(a, begin ,mid, end);
}
//堆排序
void AdjustHeap(int * arrays, int location, int n)
{   //调整堆的性质
    int key = arrays[location];
    for (int i = 2 * location; i < n; i *= 2)
    {
        if (i < n && arrays[i] < arrays[i + 1]) //找两者中最大的值
            i++;
        if (key >= arrays[i]) //确定location的位置为i
            break;
        arrays[location] = arrays[i];
        location = i;
    }
    arrays[location] = key;
}
void CreateHeap(int * arrays, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        AdjustHeap(arrays, i, n);
    }
}
void HeapSort(int * arrays, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arrays[i],&arrays[0]);
        AdjustHeap(arrays, 0, i - 1);
    }
}
void  MenuSort()                                    
{   /*显示菜单子函数*/
	printf("\n                   排序子系统");
    printf("\n==================================================");  
    printf("\n|               1——更新排序数据                |");
    printf("\n|               2——直接插入排序                |");
    printf("\n|               3——希尔排序                    |");
    printf("\n|               4——冒泡排序                    |");
    printf("\n|               5——快速排序                    |");
    printf("\n|               6——直接选择排序                |");   
    printf("\n|               7——堆排序                      |"); 
    printf("\n|               8——归并排序                    |");   
    printf("\n|               0——返回                        |");
    printf("\n=================================================="); 
    printf("\n请输入菜单号（0-8）:"); 	
}
int Sort()
{
    int n;
    int MaxArrays[100];
    int choice;
    char ch1 = 'Y';
    while (ch1 == 'y' || ch1 == 'Y')
    {
        MenuSort();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            printf("请输入数据长度:\n");
            scanf("%d",&n);
            printf("请输分别输入数据:\n");
            for(int i = 0 ; i < n; i++)
            scanf("%d",&MaxArrays[i]);
            break;
        case 2:
            PreprintArrays(MaxArrays, n);
            insertSort(MaxArrays, n);
            printArrays(MaxArrays, n);
            break;
        case 3:
            PreprintArrays(MaxArrays, n);
            ShellSort(MaxArrays, n);
            printArrays(MaxArrays, n);
            break;
        case 4:
            PreprintArrays(MaxArrays, n);
            BuSort(MaxArrays, n);
            printArrays(MaxArrays, n);
            break;
        case 5:
            PreprintArrays(MaxArrays, n);
            QuickSort(MaxArrays, 0, n - 1);
            printArrays(MaxArrays, n);
            break;
        case 6:
            PreprintArrays(MaxArrays, n);
            SelectSort(MaxArrays, n);
            printArrays(MaxArrays, n);
            break;
        case 7:
            PreprintArrays(MaxArrays, n);
            CreateHeap(MaxArrays, n);
            HeapSort(MaxArrays, n);
            printArrays(MaxArrays, n);
            break;
        case 8:
            PreprintArrays(MaxArrays, n);
            MergeSort(MaxArrays, 0, n);
            printArrays(MaxArrays, n);
            break;
        case 0:
            ch1 = 'n';
            break;
        default:
            printf("输入有误！");
            ch1 = 'n';
        }
    }
    return  0;
}
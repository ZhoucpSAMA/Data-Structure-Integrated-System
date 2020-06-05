#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
//学生信息的定义：
typedef struct
{
	char ID[100];	//学号
	char Name[100]; //姓名
	int Score;		//成绩
	char Class[100];	//班级
} Student;
//链表结点的定义：
typedef struct LNode
{
	Student data;		//数据域
	struct LNode *next; //指针域
} LNode, *LinkList;

LinkList *p, *r;

//输入学生信息
void inputStudent(LNode *head)
{
	LinkList p, r; //p指向新结点； r指向当前链表的尾结点
	int i, n;	   //n表示学生的人数
	r = head;
	printf("请输入学生的人数:");
	scanf("%d", &n);
	printf("请输入学生的信息:\n");
	for (i = 1; i <= n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p->next = NULL;
		printf("学号:");
		scanf("%s", p->data.ID);
		printf("\n");
		printf("姓名:");
		scanf("%s", p->data.Name);
		printf("\n");
		printf("班级：");
		scanf("%s", p->data.Class);
		printf("\n");
		printf("成绩:");
		scanf("%d", &p->data.Score);
		r->next = p;
		r = r->next;
		printf("\n =========分===========割============线===========\n");
	}
}

//输出学生信息
void printStudent(LNode *head)
{
	LinkList p;
	p = head;
	printf("请输出学生的信息：\n\n\n");
	printf("学号\t姓名\t班级\t成绩\n");
	while (p->next != NULL)
	{
		p = p->next;
		printf("%s\t%s\t%s\t%d\n", p->data.ID, p->data.Name, p->data.Class, p->data.Score);
	}
}

void SearchByName(LNode *head, Student e)
{
	LinkList p;
	p = head;
	printf("请输入查找的姓名：\n");
	scanf("%s", e.Name);
	while ((p->next != NULL) && strcmp(e.Name, p->data.Name))
	{
		p = p->next;
	}
	printf("学号 %s\t班级 %s\t 成绩  %d\n", p->data.ID, p->data.Class, p->data.Score);
}
void SearchByPos(LNode *head, Student e)
{
	LinkList p;
	p = head;
	printf("请输入查找的学号：\n");
	scanf("%s", e.ID);
	while ((p->next != NULL) && strcmp(e.ID, p->data.ID))
	{
		p = p->next;
	}
	printf("姓名 %s\t班级 %s\t 成绩  %d\n", p->data.Name, p->data.Class, p->data.Score);
}

void SearchByID(LNode *head, int i)
{
	int k;
	LinkList p;
	printf("请输入你要查询的位置：");
	scanf("%d", &i);
	if (i < 0)
	{
		printf("查找失败！\n");
	}
	p = head;
	k = 0;
	while (p->next != NULL && k < i)
	{
		p = p->next;
		k = k + 1;
	}
	if (i == k)
		printf("学号：%s\t 姓名：  %s\t 班级：%s\t 成绩： %d\n", p->data.ID, p->data.Name, p->data.Class, p->data.Score);
	else
		printf("查找失败！\n");
}

void InsertStudent(LNode *head, int i, Student e)
{
	int k;
	LinkList p, r;
	r = head;
	k = 0;
	printf("请输入你要插入的位置：\n");
	scanf("%d", &i);
	printf("请输入插入学生的信息：\n");
	printf("学号:\n");
	scanf("%s", e.ID);
	printf("姓名:\n");
	scanf("%s", e.Name);
	printf("班级：\n");
	scanf("%s", e.Class);
	printf("成绩:\n");
	scanf("%d", &e.Score);
	while (r != NULL && k < i - 1)
	{
		r = r->next;
		k = k + 1;
	}
	if (r == NULL)
	{
		printf("插入失败！\n");
	}
	p = (LinkList)malloc(sizeof(LNode));
	p->data = e;
	p->next = r->next;
	r->next = p;
	printf("插入成功！\n");
}

void DelStudent(LNode *head, int pos, Student *e)
{
	LinkList p, r;
	int k;
	r = head;
	k = 0;
	printf("请输入你要删除的位置：\n");
	scanf("%d", &pos);
	while (r->next != NULL && k < pos - 1)
	{
		r = r->next;
		++k;
	}
	if (k > pos - 1 || NULL == r->next)
	{
		printf("删除失败！\n");
		return;
	}
	p = r->next;
	r->next = p->next;
	*e = p->data;
	free(p);
	printf("删除成功！\n");
}
void StudentNums(LNode *head)
{
	int i;
	LinkList p;
	p = head->next;
	i = 0;
	while (p != NULL)
	{
		p = p->next;
		i++;
	}
	printf("学生总数为：%d\n", i);
	printf("\n");
}
void StudentMenu()
{
    printf("\n     学生管理系统 - Powered by ZhoucpSAMA");
    printf("\n ==============================================");  
    printf("\n|               1——录入学生信息              |");
    printf("\n|               2——显示学生信息              |");
    printf("\n|               3——根据姓名查找              |");
    printf("\n|               4——根据学号查找              |");
    printf("\n|               5——根据位置查找              |");
    printf("\n|               6——插入学生信息              |");
    printf("\n|               7——根据位置删除              |");
    printf("\n|               8——统计学生人数              |");
    printf("\n|               0——返回                      |");
    printf("\n =============================================="); 
    printf("\n请输入菜单号（0-8）:");
}
int StudentManageSystem()
{
	LNode* head;
	head = (LinkList)malloc(sizeof(LNode));
	head->next = NULL;
	int i = 0;
	Student e;
    int choice;
    char ch1 = 'Y';
    while (ch1 == 'Y' || ch1 == 'y')
    {
        StudentMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
            case 1: inputStudent(head); break;
            case 2: printStudent(head); break;
            case 3: SearchByName(head, e); break;
            case 4: SearchByID(head, i); break;
            case 5: SearchByPos(head, e); break;
            case 6: InsertStudent(head, i, e); break;
            case 7: DelStudent(head, i, &e); break;
            case 8: StudentNums(head); break;
            case 0:ch1 = 'n';break;
        }
    }
	return 0;
}

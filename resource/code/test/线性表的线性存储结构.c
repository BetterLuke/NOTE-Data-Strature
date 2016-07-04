#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0


typedef int Status;		/* Status是函数的类型，其值是函数结果状态代码，如OK等 */

typedef struct Node     /* 线性表的单链表存储结构 */
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Node * LinkList;   /* 定义LinkList */

typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

/* 初始条件：顺序线性表L已存在，1 ≤ i ≤ ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;         
	p = L->next;        /*  让p指向链表L的第1个结点 */
	j = 1;
	/* p不为空且计数器j还没有等于i时，循环继续。 */
    /* 如果i不是1，进入循环体，j还为1，但执行第一句后p就指向了第2个结点，
       所以p指向的真实结点总是领先j一个单位，所以j < i,而不是j <= i*/
	while (p && j < i)  
	{
		p = p->next; //当j = 1时，
		j++;
	}
	if (!p || j > i)
		return ERROR;
	*e = p->data;
	return OK;
}

/* 初始条件：顺序线性表L已存在，1 ≤ i ≤ ListLength(L) */
/* 操作结果：在L中第i个位置结点之前插入新的数据元素，L的长度加1 */
Status ListInsert(LinkList *L, int i; ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	/* 寻找第i-1个结点 */
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	/* 生成新节点：
	   1. 使用malloc开辟一块空间，用于盛放Node类型的结点——转换为LinkList类型。
	   2. s接受这个地址，s完成了初始化 
	   3. 向s->data中填入数据*/
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;

	/*针线活：
		1.将p的后继结点赋值给s的后继
		2.将s赋值给p的后继
	 */
	s->next = p->next;
	p->next = s;
	return OK;
}

/* 初始条件：顺序线性表L已存在，1 ≤ i ≤ ListLength(L) */
/* 操作结果：删除L上的第i个结点，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L, int i)
{
	int j;
	LinkList p, q;
	j = 1;
	/* 遍历寻找第i-1个结点 */
	while(p && j < i)
	{
		p = p->next;
		j++;
	}
	if(!p || j > i)
		return ERROR;

	/* 针线活：
		 1.将q的后继赋值给p的后继，让p实现了跳跃 
		 2.将q结点中的数据给e */
	q = p->next;
	p->next = q->next;

	*e = q->data;
	/* 使用内存释放函数，让系统回收此结点，释放内存 */
	free(q);
	return OK;
}


/* 随机产生n个元素的值，建立带表头结点的单链线性表L (头插法) */
void CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;
	srand(time(0)); 	/* 以当前系统时间数初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;		/* 先建立了一个带头节点的单链表 */
	for(i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node)); /* 生成新节点 */
		p->data = rand() % 100 + 1; /* 随机生成100以内的数字 */
		p->next = (*L)->next;
		(*L)->next = p; /* 插入到表头 */
	}
}

/* 随机产生n个元素的值，建立带表头结点的单链线性表L (尾插法) */
void CreateListTail(LinkList *L, int n)
{
	LinkList p,r;
	int i;
	srand(time(0)); /* 以当前系统时间数初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	r = *L; /* r为指向尾部的结点 */
	for(i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1; /* 随机生成100以内的数字 */
		r->next = p; /* 将表尾端结点的指针指向新节点 */
		r = p;/* 将当前的新节点定义为表尾终端节点 */
	}
	r->next = NULL; /* 表示当前链表结束 */
}

/* 初始条件：链式线性表L已存在 */
/* 操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
	LinkList p,q;
	p = (*L)->next; /* p指向第一个节点 */
	while(p)   /* 只要p不为空，就没到表尾，因为尾结点的指针域为空 */
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL; /* 头节点指针域为空 */
	return OK;
}
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000 /* 存储空间初始分配量 */  

typedef int Status;		/* Status是函数的类型，其值是函数结果状态代码，如OK等 */
typedef char ElemType; /* ElemType 类型根据实际情况而定,这里假设为 char */

/* 线性链表静态链表的存储结构 */
typedef struct 
{
	ElemType data;
	int cur; /* 游标(Cursor),为0时表示无指向 */
} Component, StaticLinkList[MAXSIZE];

/* 初始化一个空的静态链表，注意：将一维数组space中各分量链成一个备用链表，
   并不是让每一个元素的cur为0 */
/* space[0].cur为头指针，“0” 表示空指针 */
Status InitList(StaticLinkList space)
{
	int i;
	for (i = 0; i <= MAXSIZE; i++)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur = 0; /* 目前静态链表为空，最后一个元素的的cur为0 */
	return OK;
}


/* 若备用空间链表非空，则分配返回的结点下标，否则返回0 */
int Malloc_SSL(StaticLinkList space)
{
	int i = space[0].cur; /* 当前数组第一个元素的cur值，就是备用链表的第一个分量 */
	if(space[0].cur) 
		space[0].cur = space[i].cur;/* 使用了备用链表的一个分量，所以把下一个备用链
		                               表的分量的下标存为数组第一个元素的cur值，也就
		                               是为下一次的使用准备好 */
	return i; /* 返回备用链表的第一个分量 */
}


/* 在 L 中第 i 个元素之前插入新的数据元素 e */  
Status ListInsert(StaticLinkList L, int i, ElemType e) 
{  
    int j, k, l;  
  
    k = MAXSIZE - 1; /* 注意 k 首先是最后一个元素的下标 */  
    if (i < 1 || i > ListLength(L) + 1)  /* 判断插入位置是否正确 */
        return ERROR;  
    j = Malloc_SSL(L);  /* 获得空闲分量的下标 */
    if (j) {    
        L[j].data = e; /* 将数据赋值给此分量的 data */  
        for (l = 1; l <= i - 1; l++) /* 找到第 i 个元素之前的位置 */  
            k = L[k].cur;  
        L[j].cur = L[k].cur;  /* 把第 i 个元素之前的 cur 赋值给新元素的 cur */  
        L[k].cur = j;  /* 把新元素的下标赋值给第 i 个元素之前元素的 ur */  
        return OK;  
    }  
    return ERROR;  
}  

/* 删除再L中第 i 个数据元素e*/  
Status ListDelete(StaticLinkList L, int i)
{
	int j, k;
	if(i < 1 || i > ListLength(L))
		return ERROR;
	k = MAXSIZE -1;
	for(j = 1; j <= i - 1; j++)
		k = L[k].cur;
	j = L[k].cur;
	L[k].cur = L[j].cur;
	Free_SSL(L,j);
	return OK;
}

/* 将下标为k的空闲结点回收到备用链表 */
void Free_SSL(StaticLinkList space, int k)
{
	space[k].cur = space[0].cur; /* 把数组的第一个元素的cur值赋值给要删除分量的cur */
	space[0].cur = k; /* 把要删除的分量的下标赋值给数组第一个元素的cur */
}


/* 初始条件：静态链表L已存在 */
/* 操作结果：返回L中数据元素的个数 */
int ListLength(StaticLinkList L)
{
	int j = 0;
	int i = L[MAXSIZE - 1].cur;
	while(i)
	{
		i = L[i].cur;
		j++;
	}
	return j;
}







/* 存储空间初始分配量 */
#define MAXSIZE 20
/* ElemType类型根据实际情况而定，这里假设为int */
typedef int ElemType;
typedef struct SqList
{
    /* 数组存储数据元素，最大值为MAXSIZE */
    ElemType data[MAXSIZE];
    /* 线性表当前长度 */
    int length;
};

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/* Status是函数的类型，其值是函数结果状态代
码，如OK等 */
/* 初始条件：顺序线性表L已存在，1≤i≤
ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(SqList L, int i, ElemType *e)
{
	if(L.length == 0 || i < 1 || i > L.length)
		return ERROR;
	*e = L.data[i-1];
	return OK;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
	int k;
	/* 顺序线性表已经满 */
	if(L->length == MAXSIZE)
		return ERROR;
	/* 当i不在范围内时,当i = L->length + 1时代表在末尾插入，这点容易疏漏 */
	if(i < 1 || i > L->length + 1)
		return ERROR;
	if(i <= L->length)
	{
		/*将要插入位置后所有数据元素向后移动一位 */
		for(k = L->length - 1; k >= i-1; k--)
			L->data[k+1] = L->data[k];
	}
	L->data[i-1] = e; /* 将新元素插入 */
	L->length++;     
	return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
	int k;
	/* 线性表为空 */
	if(L->length == 0)
		return ERROR;
	/* 判断删除位置是否合法 */
	if(i > L->length)
		return ERROR;
	/* 如果删除不是最后位置，需将删除位置后继元素前移 */
	if(i < L->length)
	{
		for(k = i; k < L->length; k++)
		L->data[k + 1] = L->data[k];
	}
	L->length--;
	return OK;
}


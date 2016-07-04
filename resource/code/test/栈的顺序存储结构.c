/* SElemType类型根据实际情况而定，这里假设为int */
typedef int SElemType;
typedef struct 
{
    SElemType data[MAXSIZE];
    int top; /* 用于栈顶指针，指示栈顶元素在数组中的位置，
               想象这top就如同中学物理学过的游标卡尺的游标 */
             /* 当栈存在一个元素时，top等于0，因此通常把空
             栈的判定条件定为top等于-1。 */
} SqStack;


/* 插入元素e为新的栈顶元素 */
Status Push(SqStack *S, SElemType e)
{
	/* 如果发生栈已经满了的情况，则会栈溢出 */
	if( S->top == MAXSIZE - 1 )
		return ERROR;
 	S->top++; /* 栈顶指针增加1个单位 */
	S->data[S->top] = e;
	return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR */
Status pop(SqStack *S, SElemType *e)
{
	if(S->top == -1)
		return ERROR;
	*e = S->data[S->top]; /* 将要删除的栈顶元素赋值给e */
	S->top--;
	return OK;
}

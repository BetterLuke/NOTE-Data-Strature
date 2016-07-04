/* 两栈共享空间结构 */
typedef struct
{
	SElemType data[MAXSIZE];
	int top1; /* 栈1栈顶指针 */
	int top2; /* 栈2栈顶指针 */
} SqDoubleStack;

/* 插入元素e为新的栈顶元素 */
Status push(SqDoubleStack *S, SElemType e, int stackNumber)
{
	if(top1 + 1 == top2) /* 栈已满，不能再push新元素了 */
		return ERROR;
	if(stackNumber == 1)
		S->data[++S->top1]; /* 若栈1则先top1+1后给数组元素赋值 */
	else if(stackNumber == 2)
		S->data[--S->top2]; /* 若栈2则先top2-1后给数组元素赋值 */
	return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status pop(SqDoubleStack *S, SElemType *e,int stackNumber)
{
	if (stackNumber == 1)
	{
		if(S->top1 == -1) /* 说明栈1已经是空栈，溢出 */
			return ERROR;
		*e = S->data[S->top1--]; /* 将栈1的栈顶元素出栈 */
	} else if(stackNumber ==2)
	{
		if(S->top2 == MAXSIZE) /* 说明栈2已经是空栈，溢出 */
			return ERROR;
		*e = S->data[S->top2++]; /* 将栈2的栈顶元素出栈 */
	}
	return OK;
}
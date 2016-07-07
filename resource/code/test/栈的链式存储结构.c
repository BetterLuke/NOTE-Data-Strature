typedef struct StackNode
{
  SElemType data;
  struct StackNode *next;
} StackNode, *LinkStackPtr;
typedef struct LinkStackPtr
{
  LinkStackPtr top;
  int count;
} LinkStack;

/* 插入元素e为新的栈顶元素 */
Status push(LinkStack *S, SElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top; // 把当前的栈顶元素直接赋值给新结点的直接后继
	S->top = s; // 将新节点s赋值给栈顶元素，充当新的栈顶元素
	S->count++;
	return OK;
}

/* 若栈不为空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status pop(LinkStack *S, SElemType *e)
{
	LinkStackPtr p;
	if(StackEmpty(*S))
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next; //使得栈顶指针下移一位，指向后一结点
	free(p);
	S->count--;
	return OK;
}
# High!栈与队列之队列

## 认识什么是队列

__队列是一种先进先出（First in First out）的线性表，简称FIFO。__允许插入的一端称为队尾，允许删除的一端称为对头。图示：

![](resource/img/Stack-and-Queue/队列图示.png)

## 队列的抽象数据类型

队列也有类似线性表的各种操作，不同的就是插入数据只能在队尾进行，删除数据只能在队头进行。
```
ADT 队列（Queue）
Data
    同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。
Operation
    InitQueue(*Q)：    初始化操作，建立一个空队列Q。
    DestroyQueue(*Q)： 若队列Q存在，则销毁它。
    ClearQueue(*Q)：   将队列Q清空。
    QueueEmpty(Q):     若队列Q为空，返回true，否则返回false。
    GetHead(Q, *e):    若队列存在且非空，用e返回队列Q的对头元素。
    EnQueue(*Q, e):    若队列Q存在，插入新元素e到队列Q中并成为队尾元素。
    DeQueue(*Q, *e):   删除队列Q中队头元素，并用e返回其值。
    QueueLength(Q):    返回队列Q的元素个数。
```

## 队列顺序存储结构——循环队列

### 队列顺序存储结构的不足

想象一下，如果不采取一些优化措施，其本质就是单链表的队列，它的顺序存储结构的性能其实就和线性表的顺序存储结构的性能一致。

入队操作时间性能等于O(1),也就是等于线性表顺序存储结构的添加元素操作``ListInsert(*L,i,e)``的时间复杂度,其中i=ListLength()。如图所示：

<!-- 插入队列的删除与插入操作的图示 -->
![插入队列的删除与插入操作的图示](resource/img/Stack-and-Queue/插入队列的删除与插入操作的图示1.png)

出队操作的时间复杂度为O(n),也就是等于线性表顺序存储结构的删除操作``ListDelete(*L,i,*e)``执行删除第一个元素（i=0）的的时间复杂度。如图所示：

![插入队列的删除与插入操作的图示2](resource/img/Stack-and-Queue/插入队列的删除与插入操作的图示2.png)

__循环队列__结构，解决了上述尴尬，大大提高了队列顺序存储结构的时间性能。

对队列顺序存储结构引入两个指针``front``和``rear``,分别标识着队头和队尾，值得注意的是，front指针指着第一个队列元素，但rear指针并不指着队尾元素，而是指着队尾元素的下一个位置。队列为空时的状态，和有队列元素时的状态，如图所示：

<!-- 循环队列的两指针图示 -->
![循环队列的两指针图示](resource/img/Stack-and-Queue/循环队列的两指针图示.png)

那么，问题来了？如果出现下图__假溢出__情况，就尴尬啦

<!-- 循环队列假溢出图示 -->
![循环队列假溢出图示](resource/img/Stack-and-Queue/循环队列假溢出图示.png)

### 循环队列的定义

解决假溢出的办法就是后面满了，就再从头开始，也就是头尾相接，使其实现循环，逻辑意义上就像一个环一样。__队列的这种头尾相接的顺序存储结构成为循环队列。__ 如图所示：

<!-- 循环队列循环图示  -->
![循环队列循环图示](resource/img/Stack-and-Queue/循环队列循环图示.png)

接着入队$a_6$,将它放置在下标为0处，rear指针指向下标为1处，如图所示：

![循环链表满的状态](resource/img/Stack-and-Queue/循环链表满的状态.png)

如上图所示，__像这种rear指针在front指针之前，且之间距离只有一个位置，就认为这样的状态是循环队列满的状态。__

接着，再记两个重要的公式：

* 若队列的最大尺寸为QueueSize，那么队列满的判定条件是表达式``(rear + 1) % QueueSize == front``是否成立。

* 计算队列长度的公式: ``(rear - front + QueueSize) % QueueSize``

### 循环队列的实现代码

#### 循环队列的顺序存储结构
```c
/* QElemType类型根据实际情况而定，这里假设为int */
typedef int QElemType;
/* 循环队列的顺序存储结构 */
typedef struct
{
  QElemType data[MAXSIZE];
  int front; //头指针
  int rear; //尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;
```

#### 循环队列的初始化
```c
/* 初始化一个空队列 */
Status InitQueue(SqQueue *Q)
{
  Q->front = 0;
  Q->rear = 0;
  return OK;
}
```

#### 循环队列求队列长度
```c
/* 返回Q的元素个数，也就是队列的当前长度 */
int QueueLength(SqQueue Q)
{
  return (Q.rear - Q.front + MAXSIZE) % MAXSIZE);
}
```

#### 循环队列的入队列操作
```c
/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnQueue(SqQueue *Q, QElemType e)
{
  if( (Q.rear + 1) % MAXSIZE == Q.front )
    return ERROR;
  Q->data[Q.rear] = e;
  Q->rear = (Q->rear + 1) % MAXSIZE; //rear指针向后移动一位，若到最后则转到数组头部
  return OK;
}
```

#### 循环队列的出队列操作
```c
/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeQueue(SqQueue *Q, QElemType *e)
{
  if(Q.front == Q.rear) //判断队列是否为空
    return ERROR;
  e = Q->data[Q->front];
  Q->front = (Q->front + 1) % MAXSIZE; // front指针向后移一位置，若到最后则转到数组头部
  return OK;
}
```

>最后，你还要明白：循环队列只是优化了时间性能，并没有优化空间性能。

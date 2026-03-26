// 顺序栈——课上练
#include <stdio.h>
#include <stdlib.h>

/*此处是顺序栈数据结构定义*/
typedef int DataType;
struct seqStack
{
  int MAXNUM;      // 用于记录顺序栈中能存放的最大元素个数
  int top;         // 用于存放顺序栈的栈顶位置，初始化为0
  DataType *element; // 连续空间的起始地址
};

typedef struct seqStack *PseqStack;

// 第一关：创建空栈
PseqStack createNullStack_seq(int m)
{
    if (m <= 0) return NULL;
    PseqStack L = (PseqStack)malloc(sizeof(struct seqStack));
    if (L == NULL) return NULL;

    L->element = (DataType *)malloc(sizeof(DataType) * m);
    if (L->element == NULL) {
        free(L);
        return NULL;
    }

    L->MAXNUM = m;
    L->top = 0; // 题目要求初始化为0，表示top指向下一个可存放的位置
    return L;
}

// 第二关：判断栈是否为空
int isNullStack_seq(PseqStack L)
{
    if (L == NULL) return -1;
    return (L->top == 0) ? 1 : 0;
}

// 第三关：判断栈是否已满
int isFullStack_seq(PseqStack L)
{
    if (L == NULL) return 0;
    return (L->top == L->MAXNUM) ? 1 : 0;
}

// 第四关：入栈
int push_seq(PseqStack L, DataType x)
{
    if (L == NULL || isFullStack_seq(L)) return 0;
    L->element[L->top] = x;
    L->top++;
    return 1;
}

// 第五关：出栈
DataType pop_seq(PseqStack L)
{
    if (L == NULL || isNullStack_seq(L)) return -1;
    L->top--;
    return L->element[L->top];
}

// 第六关：取栈顶元素
DataType top_seq(PseqStack L)
{
    if (L == NULL || isNullStack_seq(L)) return -1;
    return L->element[L->top - 1];
}

// 销毁顺序栈
int destroystack_seq(PseqStack L)
{
    if (L == NULL) return 0;
    int currentNum = L->top;
    free(L->element);
    free(L);
    return currentNum;
}

// 第七关：数制转换

// 辅助打印函数：逐个弹出并输出
void print(PseqStack L)
{
    while (!isNullStack_seq(L)) {
        DataType val = pop_seq(L);
        if (val < 10) {
            printf("%d", val);
        } else {
            // 处理十六进制 A-F
            printf("%c", val - 10 + 'A');
        }
    }
}

void convert(int data, int k)
{
    // 假设最大转换位数不超过100位
    PseqStack L = createNullStack_seq(100);
    if (L == NULL) return;

    // 特殊情况处理：data为0
    if (data == 0) {
        printf("0");
        destroystack_seq(L);
        return;
    }

    // 进制转换逻辑：除k取余，余数入栈
    int temp = data;
    while (temp > 0) {
        push_seq(L, temp % k);
        temp = temp / k;
    }

    // 输出结果
    print(L);

    // 释放栈空间
    destroystack_seq(L);
}
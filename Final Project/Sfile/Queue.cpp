#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
	int data;
	struct QNode *next;
} QNode;
typedef struct {
	QNode *front;
	QNode *rear;
} LinkQueue;
void InitQueue(LinkQueue *q);
void EnQueue(LinkQueue *q, int x);
int DeQueue(LinkQueue *q, int *x);
int GetFront(LinkQueue *q, int *x);
int GetRear(LinkQueue *q, int *x);
void PrintQueue(LinkQueue *q);
void MenuQueue();
// 初始化队列
void InitQueue(LinkQueue *q) {
	q->front = q->rear = (QNode *)malloc(sizeof(QNode));
	q->front->next = NULL;
}

// 入列
void EnQueue(LinkQueue *q, int x) {
	QNode *node = (QNode *)malloc(sizeof(QNode));
	node->data = x;
	node->next = NULL;
	q->rear->next = node;
	q->rear = node;
}

// 出列
int DeQueue(LinkQueue *q, int *x) {
	if (q->front == q->rear) return 0;
	QNode *p = q->front->next;
	*x = p->data;
	q->front->next = p->next;
	if (q->rear == p) q->rear = q->front;
	free(p);
	return 1;
}

// 取队头元素
int GetFront(LinkQueue *q, int *x) {
	if (q->front == q->rear) return 0;
	*x = q->front->next->data;
	return 1;
}

// 取队尾元素
int GetRear(LinkQueue *q, int *x) {
	if (q->front == q->rear) return 0;
	*x = q->rear->data;
	return 1;
}

// 显示队列所有元素
void PrintQueue(LinkQueue *q) {
	QNode *p = q->front->next;
	printf("队列内容: ");
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void MenuQueue() {
	printf("队列的基本操作及应用\n");
	printf("1. 入列\n");
	printf("2. 出列\n");
	printf("3. 取队头元素\n");
	printf("4. 取队尾元素\n");
	printf("5. 显示队列\n");
	printf("6. 退出\n");
}

int MainQueue() {
	LinkQueue q;
	InitQueue(&q);
	int choice, val, res;
	while (1) {
		MenuQueue();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		switch (choice) {
		case 1:
			printf("请输入入列元素: ");
			scanf("%d", &val);
			while (getchar() != '\n');
			EnQueue(&q, val);
			printf("入列成功！\n");
			break;
		case 2:
			res = DeQueue(&q, &val);
			if (res)
				printf("出列元素: %d\n", val);
			else
				printf("队列为空，无法出列！\n");
			break;
		case 3:
			res = GetFront(&q, &val);
			if (res)
				printf("队头元素: %d\n", val);
			else
				printf("队列为空！\n");
			break;
		case 4:
			res = GetRear(&q, &val);
			if (res)
				printf("队尾元素: %d\n", val);
			else
				printf("队列为空！\n");
			break;
		case 5:
			PrintQueue(&q);
			break;
		case 6:
			printf("程序退出！\n");
			return 0;
		}
	}
}


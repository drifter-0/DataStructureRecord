#include "Stack.h"
#include "History.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 10
#define OVERFLOW -1
#define MAX_LEN 100
typedef struct {
	double *base;
	double *top;
	int stacksize;
} Stack;
void InitStack(Stack *S);
void Push(Stack *S, double e);
double Pop(Stack *S);
double Peek(Stack S);
bool IsEmpty(Stack S);
void MenuStack();

void InitStack(Stack *S) {
	S->base = (double *)malloc(INIT_SIZE * sizeof(double));
	if (!S->base) {
		fprintf(stderr, "内存分配失败！\n");
		exit(EXIT_FAILURE);
	}
	S->top = S->base;
	S->stacksize = INIT_SIZE;
}

void Push(Stack *S, double e) {
	if (S->top - S->base >= S->stacksize) {
		double *newBase = (double *)realloc(S->base, S->stacksize * 2 * sizeof(double));
		if (!newBase) {
			fprintf(stderr, "扩容失败！\n");
			exit(OVERFLOW);
		}
		S->top = newBase + (S->top - S->base);
		S->base = newBase;
		S->stacksize *= 2;
	}
	*(S->top++) = e;
}

double Pop(Stack *S) {
	if (S->top == S->base) {
		fprintf(stderr, "出栈错误: 栈为空！\n");
		exit(EXIT_FAILURE);
	}
	return *(--S->top);
}

double Peek(Stack S) {
	if (S.top == S.base) {
		fprintf(stderr, "获取栈顶错误: 栈为空！\n");
		exit(EXIT_FAILURE);
	}
	return *(S.top - 1);
}

bool IsEmpty(Stack S) {
	return S.base == S.top;
}

void MenuStack() {
	printf("栈的基本操作及应用\n");
	printf("1. 进栈\n");
	printf("2. 出栈\n");
	printf("3. 取栈顶\n");
	printf("4. 应用\n");
	printf("5. 退出\n");
}

int MainStack() {
	Stack S;
	InitStack(&S);
	int choice;
	char inputBuffer[256];
	double result;
	
	while (1) {
		MenuStack();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		switch (choice) {
		case 1:
			printf("请输入要进栈的值: ");
			fgets(inputBuffer, sizeof(inputBuffer), stdin);
			result = strtod(inputBuffer, NULL);
			Push(&S, result);
			printf("进栈成功！栈顶元素: %.10lf\n", Peek(S));
			break;
		case 2:
			if (IsEmpty(S)) {
				printf("空栈不可出栈\n");
			} else {
				printf("出栈成功，弹出的元素为: %.10lf\n", Pop(&S));
			}
			break;
		case 3:
			if (IsEmpty(S)) {
				printf("空栈不可操作\n");
			} else {
				printf("栈顶元素: %.10lf\n", Peek(S));
			}
			break;
		case 4:
			MainHistory();
			break;
		case 5:
			printf("程序退出！\n");
			return 0;
		}
	}
}



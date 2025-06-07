#include "History.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LEN 100
#define STACK_SIZE 100

typedef struct {
	char urls[STACK_SIZE][MAX_URL_LEN];
	int top;
} Stack;
void initStack(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);
int push(Stack* s, const char* url);
int pop(Stack* s, char* url);

typedef struct {
	Stack backStack;
	Stack forwardStack;
	char current[MAX_URL_LEN];
} BrowserHistory;
void initHistory(BrowserHistory* bh, const char* homepage);
void visit(BrowserHistory* bh, const char* url);
int back(BrowserHistory* bh);
int forward(BrowserHistory* bh);
void printCurrent(BrowserHistory* bh);

void initStack(Stack* s) {
	s->top = -1;
}

int isEmpty(Stack* s) {
	return s->top == -1;
}

int isFull(Stack* s) {
	return s->top == STACK_SIZE - 1;
}

int push(Stack* s, const char* url) {
	if (isFull(s)) return 0;
	s->top++;
	strncpy(s->urls[s->top], url, MAX_URL_LEN - 1);
	s->urls[s->top][MAX_URL_LEN - 1] = '\0';
	return 1;
}

int pop(Stack* s, char* url) {
	if (isEmpty(s)) return 0;
	strncpy(url, s->urls[s->top], MAX_URL_LEN);
	s->top--;
	return 1;
}

// 初始化浏览器历史
void initHistory(BrowserHistory* bh, const char* homepage) {
	initStack(&bh->backStack);
	initStack(&bh->forwardStack);
	strncpy(bh->current, homepage, MAX_URL_LEN - 1);
	bh->current[MAX_URL_LEN - 1] = '\0';
}

// 访问新网页
void visit(BrowserHistory* bh, const char* url) {
	push(&bh->backStack, bh->current);
	strncpy(bh->current, url, MAX_URL_LEN - 1);
	bh->current[MAX_URL_LEN - 1] = '\0';
	initStack(&bh->forwardStack); // 清空前进栈
}

// 后退
int back(BrowserHistory* bh) {
	if (isEmpty(&bh->backStack)) return 0;
	if (isFull(&bh->forwardStack)) initStack(&bh->forwardStack);
	push(&bh->forwardStack, bh->current);
	pop(&bh->backStack, bh->current);
	return 1;
}

// 前进
int forward(BrowserHistory* bh) {
	if (isEmpty(&bh->forwardStack)) return 0;
	if (isFull(&bh->backStack)) initStack(&bh->backStack);
	push(&bh->backStack, bh->current);
	pop(&bh->forwardStack, bh->current);
	return 1;
}

// 打印当前页面
void printCurrent(BrowserHistory* bh) {
	printf("当前页面: %s\n", bh->current);
}

int MainHistory() {
	BrowserHistory bh;
	char command[20];
	char url[MAX_URL_LEN];
	
	initHistory(&bh, "home.com");
	printCurrent(&bh);
	
	printf("指令: visit <url> | back | forward | exit\n");
	
	while (1) {
		printf("请输入指令: ");
		scanf("%s", command);
		
		int op = -1;
		if (strcmp(command, "visit") == 0) op = 1;
		else if (strcmp(command, "back") == 0) op = 2;
		else if (strcmp(command, "forward") == 0) op = 3;
		else if (strcmp(command, "exit") == 0) op = 4;
		
		switch (op) {
		case 1:
			scanf("%s", url);
			visit(&bh, url);
			printCurrent(&bh);
			break;
		case 2:
			if (back(&bh))
				printCurrent(&bh);
			else
				printf("无法后退！\n");
			break;
		case 3:
			if (forward(&bh))
				printCurrent(&bh);
			else
				printf("无法前进！\n");
			break;
		case 4:
			printf("程序退出！\n");
			return 0;
		}
	}
}

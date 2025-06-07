#include <stdio.h>
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Tree.h"
#include "Graph.h"

void menu() {
	printf("算法与数据结构\n");
	printf("1. 线性表的基本操作及应用\n");
	printf("2. 栈的基本操作及应用\n");
	printf("3. 队列的基本操作及应用\n");
	printf("4. 二叉树的基本操作及应用\n");
	printf("5. 图的基本操作及应用\n");
	printf("6. 退出\n");
}

int main() {
	int choice;
	
	while (1) {
		menu();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		switch (choice) {
		case 1:
			MainList();
			break;
		case 2:
			MainStack();
			break;
		case 3:
			MainQueue();
			break;
		case 4:
			MainTree();
			break;
		case 5:
			MainGraph();
			break;
		case 6:
			printf("程序退出！\n");
			return 0;
		}
	}
}

#include "LinkedList.h"
#include "Song.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
	int data;
	struct LNode *next;
} LNode, *LinkedList;
int CreateList(LinkedList *L, int n);
void InsertList(LinkedList *L, int i, int e);
int DeleteList(LinkedList *L, int i);
int LocateElem(LinkedList *L, int e);
void ShowList(LinkedList L);
void MenuList();

int CreateList(LinkedList *L, int n) {
	if (n < 1) {
		return -1;
	}
	
	*L = (LinkedList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	LinkedList tail = *L;
	
	for (int i = 0; i < n; i++) {
		printf("请输入第 %d 个整数: ", i + 1);
		LinkedList node = (LinkedList)malloc(sizeof(LNode));
		scanf("%d", &(node->data));
		node->next = NULL;
		tail->next = node;
		tail = node;
	}
	
	return 1;
}

void InsertList(LinkedList *L, int i, int e) {
	LinkedList p = *L;
	for (int j = 0; j < i - 1; j++) {
		p = p->next;
	}
	
	LinkedList node = (LinkedList)malloc(sizeof(LNode));
	node->data = e;
	node->next = p->next;
	p->next = node;
}

int DeleteList(LinkedList *L, int i) {
	LinkedList p = *L;
	for (int j = 0; j < i - 1; j++) {
		p = p->next;
	}
	
	LinkedList temp = p->next;
	int delelem = temp->data;
	p->next = temp->next;
	free(temp);
	return delelem;
}

int LocateElem(LinkedList *L, int e) {
	LinkedList p = (*L)->next;
	int index = 1;
	
	while (p) {
		if (p->data == e) {
			return index;
		}
		p = p->next;
		index++;
	}
	
	return -1;
}

void ShowList(LinkedList L) {
	LinkedList p = L->next;
	printf("链表内容: ");
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void MenuList() {
	printf("线性表的基本操作及应用\n");
	printf("1. 创建\n");
	printf("2. 插入\n");
	printf("3. 删除\n");
	printf("4. 查找\n");
	printf("5. 遍历\n");
	printf("6. 应用\n");
	printf("7. 退出\n");
} 

int MainList() {
	LinkedList L = NULL;
	int choice, n, pos, val, length;
	
	while (1) {
		MenuList();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		if (L == NULL && (choice == 2 || choice == 3 || choice == 4 || choice == 5)) {
			printf("不可操作空链表\n");
			continue;
		}
		switch (choice) {
		case 1:
			printf("请输入记录数 n = ");
			scanf("%d", &n);
			if (CreateList(&L, n) != 1) {
				printf("创建失败！\n");
				break;
			}
			printf("创建成功！\n");
			length = n;
			break;
		case 2:
			printf("请输入要插入的位置（1 - %d）和值: ", length + 1);
			scanf("%d %d", &pos, &val);
			if (pos < 1 || pos > length + 1) {
				printf("位置不合法\n");
				break;
			}
			InsertList(&L, pos, val);
			printf("已在第 %d 位插入值 %d\n", pos, val);
			length++;
			break;
		case 3:
			printf("请输入要删除的位置（1 - %d）: ", length);
			scanf("%d", &pos);
			if (pos < 1 || pos > length) {
				printf("位置不合法\n");
				break;
			}
			val = DeleteList(&L, pos);
			printf("已从第 %d 位删除值 %d\n", pos, val);
			length--;
			break;
		case 4:
			printf("请输入要查找的值: ");
			scanf("%d", &val);
			pos = LocateElem(&L, val);
			if (pos != -1) {
				printf("值 %d 位于第 %d 位\n", val, pos);
			}
			else
				printf("未找到\n");
			break;
		case 5:
			printf("表长: %d\n", length);
			ShowList(L);
			break;
		case 6:
			MainSong();
			break;
		case 7:
			printf("程序退出！\n");
			return 0;
		}
	}
}

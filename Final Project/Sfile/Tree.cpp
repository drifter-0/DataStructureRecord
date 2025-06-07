#include "Tree.h"
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
	char data;
	struct TNode *lchild, *rchild;
}TNode, *Tree;
void CreateTree(Tree *T);
void PreOrderTraverse(Tree T, void (*Visit)(char));
void InOrderTraverse(Tree T, void (*Visit)(char));
void PostOrderTraverse(Tree T, void (*Visit)(char));
TNode* FindNode(Tree T, char data);
TNode* FindParent(Tree root, TNode* child);
TNode* FindSibling(Tree root, TNode* node);
void VisitTree(char e);
void MenuTree();

void CreateTree(Tree *T) {
	char ch;
	scanf(" %c", &ch);
	if (ch == '*')
		*T = NULL;
	else {
		*T = (TNode *)malloc(sizeof(TNode));
		(*T)->data = ch;
		CreateTree(&((*T)->lchild));
		CreateTree(&((*T)->rchild));
	}
}

void PreOrderTraverse(Tree T, void (*VisitTree)(char)) {
	if (T) {
		VisitTree(T->data);
		PreOrderTraverse(T->lchild, VisitTree);
		PreOrderTraverse(T->rchild, VisitTree);
	}
}

void InOrderTraverse(Tree T, void (*VisitTree)(char)) {
	if (T) {
		InOrderTraverse(T->lchild, VisitTree);
		VisitTree(T->data);
		InOrderTraverse(T->rchild, VisitTree);
	}
}

void PostOrderTraverse(Tree T, void (*VisitTree)(char)) {
	if (T) {
		PostOrderTraverse(T->lchild, VisitTree);
		PostOrderTraverse(T->rchild, VisitTree);
		VisitTree(T->data);
	}
}

TNode* FindNode(Tree T, char data) {
	if (!T)
		return NULL;
	if (T->data == data)
		return T;
	TNode* leftResult = FindNode(T->lchild, data);
	if (leftResult)
		return leftResult;
	return FindNode(T->rchild, data);
}

TNode* FindParent(Tree root, TNode* child) {
	if (!root || !child)
		return NULL;
	if (root->lchild == child || root->rchild == child)
		return root;
	TNode* leftSearch = FindParent(root->lchild, child);
	if (leftSearch)
		return leftSearch;
	return FindParent(root->rchild, child);
}

TNode* FindSibling(Tree root, TNode* node, bool *isLeftSibling) {
	if (!root || !node)
		return NULL;
	TNode* parent = FindParent(root, node);
	if (!parent)
		return NULL;
	if (parent->lchild == node) {
		if (isLeftSibling)
			*isLeftSibling = false;
		return parent->rchild;
	} else if (parent->rchild == node) {
		if (isLeftSibling)
			*isLeftSibling = true;
		return parent->lchild;
	}
	return NULL;
}

TNode* FindChild(Tree node, bool findLeft) {
	if (!node) {
		return NULL;
	}
	
	return findLeft ? node->lchild : node->rchild;
}

void VisitTree(char e) {
	printf("%c ", e);
}

void MenuTree() {
	printf("二叉树的基本操作及应用\n");
	printf("1. 创建\n");
	printf("2. 遍历\n");
	printf("3. 查找双亲\n");
	printf("4. 查找兄弟\n");
	printf("5. 查找孩子\n");
	printf("6. 应用\n");
	printf("7. 退出\n");
}

int MainTree() {
	Tree T = NULL;
	int choice;
	char input;
	
	while (1) {
		MenuTree();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		switch (choice) {
		case 1:
			printf("请输入二叉树的先序序列（*表示空节点）: \n");
			CreateTree(&T);
			printf("创建成功！\n");
			break;
		case 2:
			printf("先序遍历: ");
			PreOrderTraverse(T, VisitTree);
			printf("\n");
			printf("中序遍历: ");
			InOrderTraverse(T, VisitTree);
			printf("\n");
			printf("后序遍历: ");
			PostOrderTraverse(T, VisitTree);
			printf("\n");
			break;
		case 3: {
			printf("请输入要查找双亲的节点: ");
			scanf(" %c", &input);
			TNode *targetNode = FindNode(T, input);
			if (targetNode) {
				TNode *parent = FindParent(T, targetNode);
				if (parent)
					printf("节点 %c 的双亲是 %c\n", input, parent->data);
				else
					printf("节点 %c 无双亲\n", input);
			} else {
				printf("节点 %c 不存在\n", input);
			}
			break;
		}
		case 4: {
			printf("请输入要查找兄弟的节点: ");
			scanf(" %c", &input);
			TNode *targetNode = FindNode(T, input);
			if (targetNode) {
				bool isLeft;
				TNode *sibling = FindSibling(T, FindNode(T, input), &isLeft);
				if (sibling)
					printf("节点 %c 的%s兄弟是 %c\n", input, isLeft ? "左" : "右", sibling->data);
				else
					printf("节点 %c 无兄弟\n", input);
				break;
			} else {
				printf("节点 %c 不存在\n", input);
			}
			break;
		}
		case 5: {
			printf("请输入要查找孩子的节点: ");
			scanf(" %c", &input);
			TNode *targetNode = FindNode(T, input);
			
			if (targetNode) {
				TNode *leftChild = FindChild(targetNode, true);
				TNode *rightChild = FindChild(targetNode, false);
				
				if (leftChild) {
					printf("节点 %c 的左孩子是 %c\n", input, leftChild->data);
				} else {
					printf("节点 %c 没有左孩子\n", input);
				}
				
				if (rightChild) {
					printf("节点 %c 的右孩子是 %c\n", input, rightChild->data);
				} else {
					printf("节点 %c 没有右孩子\n", input);
				}
			} else {
				printf("节点 %c 不存在\n", input);
			}
			break;
		}
		case 6:
			MainParser();
			break;
		case 7:
			printf("程序退出！\n");
			return 0;
		}
	}
}

#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100
typedef enum { INT_TYPE, FLOAT_TYPE, UNKNOWN_TYPE } Type;
typedef struct Node {
	char op;
	Type type;
	char varName;
	struct Node *left, *right;
} Node;
typedef struct {
	char name;
	Type type;
} Variable;
Type getType(char name);
Node* createLeafNode(char name);
Node* createOpNode(char op, Node* left, Node* right);
int precedence(char op);
void infixToPostfix(const char* expr, char* output);
Node* constructTreeFromPostfix(char* postfix);
void printTree(Node* node);
void removeSpaces(char* src);
int MainParser();

Variable vars[MAX_SIZE];
int varCount = 0;

// 获取变量类型
Type getType(char name) {
	for (int i = 0; i < varCount; i++) {
		if (vars[i].name == name) {
			return vars[i].type;
		}
	}
	return UNKNOWN_TYPE;
}

// 创建叶子节点
Node* createLeafNode(char name) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->op = '\0';
	node->varName = name;
	node->type = getType(name);
	node->left = node->right = NULL;
	return node;
}

// 创建运算符节点
Node* createOpNode(char op, Node* left, Node* right) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->op = op;
	node->left = left;
	node->right = right;
	node->varName = '\0';
	
	if (left->type == UNKNOWN_TYPE || right->type == UNKNOWN_TYPE) {
		node->type = UNKNOWN_TYPE;
	} else if (left->type == INT_TYPE && right->type == INT_TYPE) {
		node->type = INT_TYPE;
	} else {
		node->type = FLOAT_TYPE;
	}
	
	return node;
}

// 获取运算符优先级
int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

// 中缀表达式转后缀表达式
void infixToPostfix(const char* expr, char* output) {
	char stack[MAX_SIZE];
	int top = -1, j = 0;
	
	for (int i = 0; expr[i] != '\0'; i++) {
		if (isalpha(expr[i])) { 
			output[j++] = expr[i];
		} else if (expr[i] == '(') {
			stack[++top] = expr[i];
		} else if (expr[i] == ')') {
			while (top >= 0 && stack[top] != '(') {
				output[j++] = stack[top--];
			}
			top--;
		} else {
			while (top >= 0 && precedence(stack[top]) >= precedence(expr[i])) {
				output[j++] = stack[top--];
			}
			stack[++top] = expr[i];
		}
	}
	
	while (top >= 0) {
		output[j++] = stack[top--];
	}
	output[j] = '\0';
}

Node* constructTreeFromPostfix(char* postfix) {
	Node* stack[MAX_SIZE];
	int top = -1;
	
	for (int i = 0; postfix[i] != '\0'; i++) {
		if (isalpha(postfix[i])) {
			stack[++top] = createLeafNode(postfix[i]);
		} else {
			Node* right = stack[top--];
			Node* left = stack[top--];
			stack[++top] = createOpNode(postfix[i], left, right);
		}
	}
	return stack[top];
}

void printTree(Node* node) {
	if (node == NULL) return;
	if (node->op == '\0') {
		if (node->type == INT_TYPE) {
			printf("int %c", node->varName);
		} else if (node->type == FLOAT_TYPE) {
			printf("float %c", node->varName);
		} else {
			printf("unknown %c", node->varName);
		}
	} else {
		printf("(");
		printTree(node->left);
		printf(" %c ", node->op);
		printTree(node->right);
		printf(")");
	}
}

void removeSpaces(char* src) { 
	int i = 0, j = 0; 
	while (src[i]) { 
		if (src[i] != ' ') { 
			src[j++] = src[i]; 
		} 
		i++; 
	} 
	src[j] = '\0'; 
}
// 解析器主函数
int MainParser() {
	char expr[MAX_SIZE], postfix[MAX_SIZE];
	
	printf("请输入变量数量: ");
	scanf("%d", &varCount);
	for (int i = 0; i < varCount; i++) {
		printf("请输入变量类型和名称（单字母）（如 int x 或 float y）: ");
		char varName;
		char typeStr[10];
		scanf(" %s %c", typeStr, &varName);
		vars[i].type = strcmp(typeStr, "float") == 0 ? FLOAT_TYPE : INT_TYPE;
		vars[i].name = varName;
	}
	
	printf("请输入表达式: ");
	scanf(" %[^\n]", expr);
	removeSpaces(expr); // 去除空格
	
	infixToPostfix(expr, postfix);
	Node* root = constructTreeFromPostfix(postfix);
	printf("表达式语法树: ");
	printTree(root);
	printf("\n");
	printf("最终表达式类型: ");
	if (root->type == INT_TYPE) {
		printf("int\n");
	} else if (root->type == FLOAT_TYPE) {
		printf("float\n");
	} else {
		printf("unknown\n");
	}
	return 0;
}


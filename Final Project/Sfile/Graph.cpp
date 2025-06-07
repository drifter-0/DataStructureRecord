#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50
#define INF 99999
typedef enum {UNDIRECTED_GRAPH, DIRECTED_GRAPH, UNDIRECTED_NETWORK, DIRECTED_NETWORK} GraphType;
typedef struct {
	int vertices;                           // 顶点数量
	int edges;                              // 边的数量
	char vexs[MAX_VERTICES];                // 顶点标识数组
	int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵
	GraphType type;                         // 图的类型
} Graph;
void CreateGraph(Graph *graph, GraphType type);
int addEdge(Graph *graph, char v1, char v2, int weight);
int FindVertexIndex(Graph *graph, char v);
void dfsTraverse(Graph *graph, void (*Visit)(char));
void dfs(Graph *graph, int v, void (*Visit)(char ch));
void bfs(Graph *graph, void (*Visit)(char ch));
void VisitGraph(char ch);
int FindFirstNeighbor(Graph* graph, char vertex);
int FindNextNeighbor(Graph* graph, char vertex, char currentNeighbor);
int GetVertexDegree(Graph* graph, char vertex, int* outDegree, int* inDegree);
void MenuGraph();

int visited[MAX_VERTICES];

void CreateGraph(Graph *graph, GraphType type) {
	int vertices, edges;
	graph->type = type;
	printf("请输入顶点数量: ");
	scanf("%d", &vertices);
	graph->vertices = vertices;
	printf("请输入边的数量: ");
	scanf("%d", &edges);
	graph->edges = edges;
	
	printf("请输入每个顶点的字符:\n");
	for (int i = 0; i < vertices; i++) {
		printf("顶点: ");
		scanf(" %c", &graph->vexs[i]);
		for (int j = 0; j < i; j++) {
			if (graph->vexs[j] == graph->vexs[i]) {
				printf("顶点不可重复\n");
				i--;
			}
		}
	}
	
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (graph->type == UNDIRECTED_GRAPH || graph->type == DIRECTED_GRAPH)
				graph->adjacencyMatrix[i][j] = 0;
			else
				graph->adjacencyMatrix[i][j] = INF;
		}
	}
	
	printf("请输入边的相关信息:\n");
	for (int k = 0; k < edges; k++) {
		char v1, v2;
		int weight;
		if (graph->type == UNDIRECTED_GRAPH || graph->type == DIRECTED_GRAPH) {
			printf("请输入边 (格式: 顶点1 顶点2): ");
			scanf(" %c %c", &v1, &v2);
			weight = 1; // 图不需要权值，默认权值为1
		} else {
			printf("请输入边 (格式: 顶点1 顶点2 权值): ");
			scanf(" %c %c %d", &v1, &v2, &weight);
		}
		if (addEdge(graph, v1, v2, weight) != 1) k--;
	}
	
	printf("图创建成功!\n");
}

int addEdge(Graph *graph, char v1, char v2, int weight) {
	int index1 = FindVertexIndex(graph, v1);
	int index2 = FindVertexIndex(graph, v2);
	if (index1 == -1 || index2 == -1) {
		printf("错误: 输入的顶点不在图中！\n");
		return -1;
	}
	if (graph->type == UNDIRECTED_GRAPH || graph->type == DIRECTED_GRAPH) {
		if (graph->adjacencyMatrix[index1][index2] != 0) {
			printf("错误: 不可重复添加边！\n");
			return -1;
		}
	}
	else if (graph->adjacencyMatrix[index1][index2] != INF){
		printf("错误: 不可重复添加边！\n");
		return -1;
	}
	graph->adjacencyMatrix[index1][index2] = weight;
	if (graph->type == UNDIRECTED_GRAPH || graph->type == UNDIRECTED_NETWORK) {
		graph->adjacencyMatrix[index2][index1] = weight;
	}
	return 1;
}

int FindVertexIndex(Graph *graph, char v) {
	for (int i = 0; i < graph->vertices; i++) {
		if (graph->vexs[i] == v)
			return i;
	}
	return -1;
}

void dfsTraverse(Graph *graph, void (*Visit)(char)) {
	for (int i = 0; i < graph->vertices; i++) {
		if (!visited[i])
			dfs(graph, i, Visit);
	}
}

void dfs(Graph *graph, int v, void (*Visit)(char)) {
	visited[v] = 1;
	Visit(graph->vexs[v]);
	
	for (int i = 0; i < graph->vertices; i++) {
		if (!visited[i] && graph->adjacencyMatrix[v][i] != 0 && graph->adjacencyMatrix[v][i] != INF)
			dfs(graph, i, Visit);
	}
}

void bfs(Graph *graph, void (*Visit)(char)) {
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;
	
	for (int i = 0; i < graph->vertices; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			queue[rear++] = i;
			
			while (front < rear) {
				int u = queue[front++];
				Visit(graph->vexs[u]);
				for (int j = 0; j < graph->vertices; j++) {
					if (!visited[j] && graph->adjacencyMatrix[u][j] != 0 && graph->adjacencyMatrix[u][j] != INF) {
						visited[j] = 1;
						queue[rear++] = j;
					}
				}
			}
		}
	}
}

void VisitGraph(char ch) {
	printf("%c ", ch);
}

int FindFirstNeighbor(Graph* graph, char vertex) {
	int index = FindVertexIndex(graph, vertex);
	if (index == -1) {
		printf("错误: 顶点 %c 不存在！\n", vertex);
		return -1;
	}
	
	for (int i = 0; i < graph->vertices; i++) {
		if (graph->adjacencyMatrix[index][i] != 0 && graph->adjacencyMatrix[index][i] != INF) {
			return i;  // 返回邻接点索引
		}
	}
	return -1;  // 没有邻接点
}

int FindNextNeighbor(Graph* graph, char vertex, char currentNeighbor) {
	int vIndex = FindVertexIndex(graph, vertex);
	int nIndex = FindVertexIndex(graph, currentNeighbor);
	
	if (vIndex == -1 || nIndex == -1) {
		printf("错误: 顶点 %c 或邻接点 %c 不存在！\n", vertex, currentNeighbor);
		return -1;
	}
	
	for (int i = nIndex + 1; i < graph->vertices; i++) {
		if (graph->adjacencyMatrix[vIndex][i] != 0 && graph->adjacencyMatrix[vIndex][i] != INF) {
			return i;  // 返回下一个邻接点索引
		}
	}
	return -1;  // 没有下一个邻接点
}

int GetVertexDegree(Graph* graph, char vertex, int* outDegree, int* inDegree) {
	int index = FindVertexIndex(graph, vertex);
	if (index == -1) {
		return -1;
	}
	
	if (graph->type == UNDIRECTED_GRAPH || graph->type == UNDIRECTED_NETWORK) {
		int degree = 0;
		for (int i = 0; i < graph->vertices; i++) {
			if (graph->adjacencyMatrix[index][i] != 0 && graph->adjacencyMatrix[index][i] != INF) {
				degree++;
			}
		}
		return degree;
	} else {
		int outD = 0, inD = 0;
		for (int i = 0; i < graph->vertices; i++) {
			if (graph->adjacencyMatrix[index][i] != 0 && graph->adjacencyMatrix[index][i] != INF) {
				outD++;
			}
			if (graph->adjacencyMatrix[i][index] != 0 && graph->adjacencyMatrix[i][index] != INF) {
				inD++;
			}
		}
		if (outDegree) *outDegree = outD;
		if (inDegree) *inDegree = inD;
		return 1;
	}
}

void MenuGraph() {
	printf("图的基本操作及应用\n");
	printf("1. 创建无向图\n");
	printf("2. 创建有向图\n");
	printf("3. 创建无向网\n");
	printf("4. 创建有向网\n");
	printf("5. 深度优先搜索(DFS)\n");
	printf("6. 广度优先搜索(BFS)\n");
	printf("7. 第一个邻接点\n");
	printf("8. 下一个邻接点\n");
	printf("9. 顶点的度\n");
	printf("10. 退出\n");
}

int MainGraph() {
	Graph graph;
	int choice;
	
	while (1) {
		MenuGraph();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		switch (choice) {
		case 1:
		case 2:
		case 3:
		case 4:
			CreateGraph(&graph, (GraphType)(choice - 1));
			break;
		case 5:
			printf("深度优先搜索 (DFS) 结果: ");
			memset(visited, 0, sizeof(visited));
			dfsTraverse(&graph, VisitGraph);
			printf("\n");
			break;
		case 6:
			printf("广度优先搜索 (BFS) 结果: ");
			memset(visited, 0, sizeof(visited));
			bfs(&graph, VisitGraph);
			printf("\n");
			break;
			case 7: {
				char v;
				printf("请输入顶点: ");
				scanf(" %c", &v);
				int neighborIndex = FindFirstNeighbor(&graph, v);
				if (neighborIndex != -1) {
					printf("顶点 %c 的第一个邻接点是 %c\n", v, graph.vexs[neighborIndex]);
				} else {
					printf("顶点 %c 没有邻接点\n", v);
				}
				break;
			}
			case 8: {
				char v, neighbor;
				printf("请输入顶点和当前邻接点 (格式: 顶点 邻接点): ");
				scanf(" %c %c", &v, &neighbor);
				int nextNeighborIndex = FindNextNeighbor(&graph, v, neighbor);
				if (nextNeighborIndex != -1) {
					printf("顶点 %c 的下一个邻接点是 %c\n", v, graph.vexs[nextNeighborIndex]);
				} else {
					printf("顶点 %c 没有更多邻接点\n", v);
				}
				break;
			}
			case 9: {
				char v;
				printf("请输入顶点: ");
				scanf(" %c", &v);
				int outD = 0, inD = 0;
				int degree = GetVertexDegree(&graph, v, &outD, &inD);
				if (degree == -1) {
					printf("错误: 顶点 %c 不存在！\n", v);
				} else if (graph.type == UNDIRECTED_GRAPH || graph.type == UNDIRECTED_NETWORK) {
					printf("顶点 %c 的度是 %d\n", v, degree);
				} else {
					printf("顶点 %c 的出度是 %d，入度是 %d\n", v, outD, inD);
				}
				break;
			}
			case 10: 
			printf("程序退出！\n");
			return 0;
		}
	}
}

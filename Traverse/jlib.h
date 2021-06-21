#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"
#define INFINITIVE_VALUE 10000
typedef JRB Graph;
struct Queue{
    int info;
    double priority;
    struct Queue* link;
};
typedef struct Queue* Queue;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2, int trong_so);
int hasVertex(Graph g, int key);
int getAdjacentVertices(Graph graph, int v, int* output);
void DFS(Graph graph, int v1, int v2);
void BFS(Graph graph, int v1, int v2);
int getEdgeValue(Graph graph, int v1, int v2);
void dropGraph(Graph graph);
double dijkstra(Graph graph, int start, int stop, int *path, int* length);
//P_Queue
Queue createQueue();
int IsQueueEmpty(Queue queue);
Queue Enqueue(Queue queue, int item, double priority);
Queue Dequeue(Queue queue, int* output);
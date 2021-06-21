#include "jlib.h"
Graph createGraph(){
    Graph g = make_jrb();
    return g;
}
void addEdge(Graph graph, int v1, int v2, int trong_so){
    Graph node = jrb_find_int(graph, v1);
    if (node == NULL){
        Graph list = make_jrb();
        jrb_insert_int(graph, v1, new_jval_v(list));
        jrb_insert_int(list, v2, new_jval_i(trong_so));
    }
    else{
        Graph list = (JRB)jval_v(node->val);
        jrb_insert_int(list, v2, new_jval_i(trong_so));
    }
    
    Graph node_ = jrb_find_int(graph, v2);
    if (node_ == NULL){
        Graph list = make_jrb();
        jrb_insert_int(graph, v2, new_jval_v(list));
        jrb_insert_int(list, v1, new_jval_i(trong_so));
    }
    else{
        Graph list = (JRB)jval_v(node_->val);
        jrb_insert_int(list, v1, new_jval_i(trong_so));
    }
}
int hasVertex(Graph g, int key){
    return (jrb_find_int(g, key) != NULL);
}
int getAdjacentVertices(Graph graph, int v, int* output){
    Graph node = jrb_find_int(graph, v);
    if (node == NULL) return 0;
    int dem = 0;
    Graph list = (JRB)jval_v(node->val);
    Graph temp;
    jrb_traverse(node, list){
        output[dem] = jval_i(node->key);
        dem++;
    }
    return dem;
}
void BFS(Graph graph, int v1, int v2){
    int* visited = (int*)calloc(10000, sizeof(int));
    Dllist q = new_dllist();
    dll_append(q, new_jval_i(v1));
    
    while(!dll_empty(q)){
        Dllist a =  dll_first(q);
        int x = jval_i(a->val);
        dll_delete_node(a);
        if (!visited[x] && x != v2){    // if x is not visited
            printf("%d ",x);            // then print x
            visited[x] = 1;             // and change x is visited
            int* list_adj = (int*)malloc(10000*sizeof(int));              // create list of x'adjacent
            int i = getAdjacentVertices(graph, x, list_adj);
            //traverse x'adjacent
            for (int j = 0; j < i; j++){
                if (!visited[list_adj[j]]) //if list_adj[j] is not visited
                    dll_append(q, new_jval_i(list_adj[j]));     //enqueue list_adj[j]
                }
            }
        else if (x == v2){
            printf("%d ",x);
            break;
        }
    }
}
void DFS(Graph graph, int v1, int v2){//stacks
    //create "visited" list, make all of them FALSE
     int* visited = (int*)calloc(10000, sizeof(int));
    //initialize a new queue q
    Dllist q = new_dllist();
    //enqueue v1 to 
    dll_prepend(q, new_jval_i(v1));
        while(!dll_empty(q)){
        //let x is dequeue of q
        Dllist a =  dll_first(q);
        int x = jval_i(a->val);
        dll_delete_node(a);

        if (!visited[x] && x != v2){               // if x is not visited
            printf("%d ", x);           // then print x
            visited[x] = 1;             // and change x is visited
            int* list_adj = (int*)malloc(10000*sizeof(int));              // create list of x'adjacent
            int i = getAdjacentVertices(graph, x, list_adj);
            //traverse x'adjacent
            for (int j = 0; j < i; j++){
                if (!visited[list_adj[j]]) //if list_adj[j] is not visited
                    dll_prepend(q, new_jval_i(list_adj[j]));     //enqueue list_adj[j]
                }
            }
        else if (x == v2){
            printf("%d ", x);
            break;
        }
    }
}
int NumberVertex(Graph graph){
    int stop = 0;
    JRB trav;
    jrb_traverse(trav, graph) stop++;
    return stop;
}
int getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph, v1);
    JRB tree = (JRB) jval_v(node->val);
    JRB search = jrb_find_int(tree, v2);
    if(search == NULL) return INFINITIVE_VALUE;
    else return jval_i(search->val);
}
Queue createQueue()
{
    Queue queue = NULL;
    return queue;
}
int IsQueueEmpty(Queue queue)
{
    return queue==NULL;
}
Queue Enqueue(Queue queue, int item, double priority)
{
	Queue temp, q;
	temp = (Queue)malloc(sizeof(struct Queue));
	temp->info = item;
	temp->priority = priority;

	if( queue == NULL || priority < queue->priority )//< to >
	{
		temp->link = queue;
		queue = temp;
	}
	else
	{
		q = queue;
		while( q->link != NULL && q->link->priority <= priority ) q=q->link;
		temp->link = q->link;
		q->link = temp;
	}

    return queue;
}
Queue Dequeue(Queue queue, int* output)
{
	Queue temp;
	if(queue == NULL) printf("Queue Underflow\n");
	else
	{
		temp = queue;
		*output = temp->info;
		queue = queue->link;
		free(temp);
	}

    return queue;
}
double dijkstra(Graph graph, int start, int stop, int* path, int* length){
    int number = NumberVertex(graph)+1;

    int prev[number], t[number];
    //visited array
    int* visited = (int*)calloc(number, sizeof(int));
    visited[start] = 1;

    //distance from start to u array
    double distance[number];
    for (int i = 0; i < number; i++) distance[i] = INFINITIVE_VALUE;
    distance[start] = 0;

    //path and length

    // Initialize Priority Queue
    Queue q = createQueue();
    q = Enqueue(q, start, distance[start]);


    int n; //number of adjacent
    int* output = (int*)malloc(number*sizeof(int)); //list of outdgree
    int deq; //record dequeue of q
    //Dijkstra
    while(!IsQueueEmpty(q)){
        q = Dequeue(q, &deq);
        n = getAdjacentVertices(graph, deq, output);
        visited[deq] = 1;
        for (int i = 0; i < n; i++){
            if (*(visited + output[i]) == 0){
                int temp = distance[deq] + getEdgeValue(graph, deq, output[i]);
                if (temp < distance[output[i]]){
                    distance[output[i]] = temp;
                    prev[output[i]] = deq;
                    q = Enqueue(q, output[i], distance[output[i]]);
                }
            }
        }
    }
    int dis = distance[stop];
    if(dis != INFINITIVE_VALUE){
        t[0] = stop;
        int a = 1;
        while(stop != start){
            stop = prev[stop];
            t[a++] = stop;
        }
        for (int i = a-1; i>=0; i--) path[a-i-1] = t[i];
        *length = a;
    }
    return dis;
}
void dropGraph(Graph graph){
    JRB node;
    jrb_traverse(node, graph){
        jrb_free_tree(node);
    }
}
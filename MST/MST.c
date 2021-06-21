#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "jrb.h"
#include "dllist.h"
#include "weightedGraphlib.h"
#define INFINITE 10000

struct edge
{
    int v1;
    int v2;
    double weight;
};
typedef struct edge Edge;

//void dropGraph(Graph graph);
double shortest_Path(Graph g, int start, int target, int *path, int *length);
int delete_edge(Graph graph,int v1,int v2);
void edge_sort(Graph g,int num_vertex,Edge edge_list[]);
int check_cycle(Graph graph);

void PrintMenu(){
    printf("\n============\n");
    printf("1.Nhap so lieu ve do thi\n");
    printf("2.Cay khung nho nhat\n");
    printf("0.Thoat\n");
    printf("============\n");
}
int main(){
    int i, j;
    double w;
    int v,e,n;
    int total=0,output[100],menu;
    int temp1,temp2, temp3;
    double temp; 
    char buff[5];
    int in[10], max=0;
    JRB tree,temp_tree;
    FILE *fin=fopen("dothi_source.txt","r");
    FILE *fout=fopen("demo_output.txt", "w+");//in ra cay output
    FILE *ftemp=fopen("demo_input.txt", "w+");//in ra cay input
    Graph g = createGraph();
    Graph mst = createGraph();
    int num_edge=0;
    Edge edge_list[10];
    do
    {
        PrintMenu();
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
    
        fscanf(fin,"%d\t%d", &v, &e);
        for ( i = 0; i <= v; i++)
        {
            itoa(i,buff,10);
            addVertex(g,i,buff);
        }
        
        fprintf(ftemp, "graph dothi{\n");
         int* matran = (int*)calloc((v+1)*(v+1), sizeof(int));
         while(!feof(fin)){
                        fscanf(fin, "%d\t%d\t%d", &temp1, &temp2, &temp3);
                        temp=(double)temp3;
                        fprintf(ftemp,"%d -- %d [label = \"%d\"]\n", temp1, temp2, temp3);
                        addEdge(g, temp1, temp2, temp);
                        addEdge(g, temp2, temp1, temp);
                        matran[temp1*(v+1) + temp2] = 1;
                        matran[temp2*(v+1) + temp1] = 1;
                    }
        fprintf(ftemp, "}\n");
            for ( i = 1; i < v+1; i++)
            {
                for ( j = 1; j< v+1; j++)
                {
                    printf("%d ",matran[i*(v+1)+j]);
                }
                printf("\n");
                
            }
            
            break;
        
        case 2:
            edge_sort(g,v,edge_list);
            i=0;
            for ( i = 1; i <= v; i++)
            {
                itoa(i,buff,10);
                addVertex(mst,i,buff);
            }
            i=0;
            for ( i = 0 ; num_edge < v; i++)
            {
                addEdge(mst,edge_list[i].v1,edge_list[i].v2,edge_list[i].weight);
                addEdge(mst,edge_list[i].v2,edge_list[i].v1,edge_list[i].weight);
                num_edge++;
                if (check_cycle(mst)==0)
                {
                    delete_edge(mst,edge_list[i].v1,edge_list[i].v2);
                    delete_edge(mst,edge_list[i].v2,edge_list[i].v1);
                    num_edge--;
                }
                
            }
            
            
            fprintf(fout, "graph dothi\n{");
            jrb_traverse(tree,mst->edges){
                n=outdegree(mst,tree->key.i,output);
                for ( i = 0; i < n; i++)
                {
                    //printf("%d %d\n",tree->key.i,output[i]);
                    if (output[i] > tree->key.i)
                    fprintf(fout, "%d -- %d [label = \"%.f\"]\n",tree->key.i, output[i], getEdgeValue(g, tree->key.i, output[i]));
                }
            }
            fprintf(fout, "}");
            fclose(fout);
            break;
        default:
            break;
        }
    } while (menu!=0);

}

double shortest_Path(Graph graph, int start, int stop, int *path, int *length){
	double total, distance[1000];
	int min, id, i, n, neighbor, position, previous[1000], output[1000], temp[1000];
	Dllist queue, shortest, node;
	
	for(i = 0; i < 100; i++){
		distance[i] = INFINITIVE_VALUE;
	}
	
	distance[start] = 0;
	previous[start] = start;
	
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	
	while(!dll_empty(queue)){
		
		min = INFINITIVE_VALUE;
		
		dll_traverse(node, queue){
			id = jval_i(node->val);
			if(min > distance[id]){
				min = distance[id];
				shortest = node;
			}
		}
		
		id = jval_i(shortest->val);
		dll_delete_node(shortest);
			
		if(id == stop)break;
			
		n = outdegree(graph, id, output);
		for(i = 0; i < n; i++){
			neighbor = output[i];
			if(distance[neighbor] > distance[id] + getEdgeValue(graph, id, neighbor)){
				distance[neighbor] = distance[id] + getEdgeValue(graph, id, neighbor);
				previous[neighbor] = id;
				dll_append(queue, new_jval_i(neighbor));
			}
		}
	}
	
	total = distance[stop];
	if(total != INFINITIVE_VALUE){
		temp[0] = stop;
		position = 1;
		while(stop != start){
			stop = previous[stop];
			temp[position] = stop;
			position += 1;
		}
		for(i = position - 1; i >= 0; i --){
            path[position - i - 1] = temp[i];
		}
        *length = position;
	}
	
	return total;
}

int check_cycle(Graph graph)
{
   int visited[1000] = {};
   int n, output[100], i, u, v, start;
   Dllist node, queue;
   JRB vertex;
   
   jrb_traverse(vertex, graph->vertices)
   {
       memset(visited, -1, sizeof(visited));
       start = jval_i(vertex->key);              
       queue = new_dllist();
       dll_append(queue, new_jval_i(start));
       visited[start]=0;
       while (!dll_empty(queue))
       {
          node = dll_first(queue);
          u = jval_i(node->val);
          dll_delete_node(node);
          if (visited[u]!=1)
          {
              visited[u] = 1;
              n = outdegree(graph, u, output);
              for (i=0; i<n; i++)
              {
                  v = output[i];
                  if(visited[v]==0){
                      //printf("\nA cycle Detected");
                      return 0;
                  }
                  if (visited[v]==-1){
                      dll_append(queue, new_jval_i(v));
                      visited[v]=0;
                  }    
                     
              }
          }           
       }
   }
   return 1; // no cycle    
}

int delete_edge(Graph graph,int v1,int v2){
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB tree;
	if(enode==NULL) {
		printf("vertex not found!\n");
		return 0;
    	}
    	tree=(JRB)(enode->val).v;
		JRB temp=jrb_find_int(tree,v2);
		if(temp!=NULL){
			jrb_delete_node(temp);
			return 1;
		}
		else return 0; 
}

void edge_sort(Graph g,int num_vertex,Edge edge_list[]){
    JRB temp;
    int i, k, output[num_vertex];
    int j=0, n;
    
    //get all edges of the graph to the edge list
    for ( i = 1; i < num_vertex+1; i++)
    {
        n=indegree(g,i,output);
        
        for (k = 0; k < n; k++)
        {
            edge_list[j].v1=i;
            edge_list[j].v2=output[k];
            edge_list[j].weight=getEdgeValue(g,i,output[k]);
            j++;
            
        }    
    }
    
    //sort the edge list by weight

    int check=0;
    for ( i = 0; i < j-1; i++)
    {
        check=0;
        for ( k = 0; k < j-i-1; k++)
        {
            
            if(edge_list[k].weight > edge_list[k+1].weight){
                Edge temp;
                temp=edge_list[k];
                edge_list[k]=edge_list[k+1];
                edge_list[k+1]=temp;
                check = 1;
            }
        
        }
        if(check == 0) break;
    }
    for ( i = 0; i < j-1; i++)
    {
        for ( k = i+1; k < j; k++)
        {
            if (edge_list[i].v1 == edge_list[k].v2 && edge_list[i].v2 == edge_list[k].v1)
            {
                for ( n = k; n < j; n++)
                {
                    edge_list[n]=edge_list[n+1];
                }
                j-=1;
            }
        }
    }
    
    // for ( i = 0; i < j; i++)
    // {
    //     printf("%d %d %.1f\n",edge_list[i].v1,edge_list[i].v2,edge_list[i].weight);
    // }
    
}
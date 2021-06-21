#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 100000
typedef JRB Graph;
Graph input( char * filename, int *v, int *n);
void addEdge(Graph graph, int v1, int v2);
int getEdgeValue(Graph graph, int v1, int v2);
int outdegree(Graph graph, int v, int* output);
int checkcolor( Graph graph, int v, int color[]);
void output (char * filename, Graph graph, int v);
int main()
{
    int v,n;
    Graph graph = input("source.txt", &v, &n);
    output ("target.txt", graph, v);
    return 0;
}
Graph input(char * filename, int *v, int *n)
{
    int i,v1,v2;
    FILE *f = fopen(filename,"r");
    if (f == NULL) printf("\nCannot read file");
    fscanf(f,"%d %d",v,n);
    Graph graph;
    graph = make_jrb();
    for(i = 0; i < *n; i++)
    {
        fscanf(f,"%d %d",&v1,&v2);
        addEdge(graph, v1, v2);
        addEdge(graph, v2, v1);
    }
    fclose(f);
    return graph;
}
void addEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(graph, v1);
        if (node == NULL) 
        {
           tree = make_jrb();
           jrb_insert_int(graph, v1, new_jval_v(tree));
        } 
        else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
}
int getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node,tree;
    node = jrb_find_int(graph, v1);
    if (node == NULL)
        return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return INFINITIVE_VALUE;
    else
        return jval_i(node->val);
}
int outdegree(Graph graph, int v, int* output)
{   
    JRB node = jrb_find_int(graph, v);
    if (node == NULL) return 0;
    JRB tree = (JRB) jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree)
    {   
        output[total++] = jval_i(node->key);
    }
    return total;
}
void output (char * filename, Graph graph, int v)
{
    FILE *f = fopen(filename,"w+");
    fprintf(f,"graph dothi\n{");
    int i,j,n,k,m;
    int s[v];
    int output[v];
    int outdeg[v];
    int color[v];
    for( i = 0; i < v; i++)
    {
        n = outdegree( graph, i + 1, output);
        outdeg[i] = n;
        color[i] = -1;
    }
    for( i = 0; i < v; i++)
    {
        m = outdeg[i];
        k = i;
        for( j = i + 1; j < v; j++)
        {
            if( m > outdeg[j]) 
            {
                m = outdeg[j];
                k = j;
            }
        }
        s[i] = k + 1;
        outdeg[k] = -1;
    }
    color[s[0] - 1] = 0;
    for(i = 1; i < v; i++)
    {
        color[s[i] - 1] = checkcolor( graph, s[i], color);  
    }
    char *mau[8]={"red","green","blue","yellow","pink","violet","navy","teal"};
    for( i = 1; i <= v; i++)
    {    
        fprintf(f,"\n  %d [fillcolor=%s, style=filled];", i, mau[color[i - 1]]);
    }
    for ( i = 1; i <= v; i++)
        for ( j = i + 1; j <= v; j++)
        {
            if(getEdgeValue( graph, i, j) == 1)fprintf(f,"\n  %d -- %d;", i, j);
        }
    fprintf(f,"\n}");
    fclose(f);
}
int checkcolor( Graph graph, int v, int color[])
{
    int i = 0, j = 0, n, output[v];
    n = outdegree( graph, v, output);
    while(j < n)
    {
        if(color[output[j] - 1] == i)
        {
            i++;
            j = 0;
        }
        else
        {
            j++;
        }
    }
    return i;
}
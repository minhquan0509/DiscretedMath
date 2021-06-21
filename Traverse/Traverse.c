#include "jlib.h"

int main(){
    Graph g = createGraph();
    FILE* source = fopen("dothi_source.txt", "r");
    //read file
    int v,e;
    fscanf(source, "%d %d\n", &v, &e);
    int temp1, temp2, temp3;
    while(!feof(source)){
        fscanf(source, "%d %d %d\n",&temp1, &temp2, &temp3);
        addEdge(g, temp1, temp2, temp3);
    }
    fclose(source);
    
    int choice, s, t;
    do{
        printf("========================\n");
        printf("1. BFS\n");
        printf("2. DFS\n");
        printf("3. Dijkstra\n");
        printf("0. Thoat\n");
        printf("========================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Xuat phat: "); scanf("%d", &s);
                printf("Ket thuc (Nhap -1 de duyet ca do thi): "); scanf("%d", &t);
                printf("BFS: ");
                BFS(g, s, -1);
                printf("\n");
            break;
            case 2:
                printf("Xuat phat: "); scanf("%d", &s);
                printf("Ket thuc (Nhap -1 de duyet ca do thi): "); scanf("%d", &t);
                printf("DFS: ");
                DFS(g, s, -1);
                printf("\n");
            break;
            case 3:
                printf("Xuat phat: "); scanf("%d", &s);
                printf("Ket thuc: "); scanf("%d", &t);
                if (jrb_find_int(g, s) == NULL || jrb_find_int(g, t) == NULL){
                    printf("Route from %d to %d does not exist!\n", s, t);
                    exit(1);
                }
                int path[100];
                int l;
                double weight = dijkstra(g, s, t, path, &l);
                if (weight == INFINITIVE_VALUE) printf("Route from %d to %d does not exist!\n", s, t);
                else{  
                    printf("Length: %.lf\n", weight);
                    printf("Path: ");
                    for (int i = 0; i < l; i++) printf("%d ", path[i]);
                    printf("\n");
                }
            break;
            default:
                break;
        }   
    }while(choice != 0);
}
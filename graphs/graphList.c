#include "graphList.h"
#include "queue.h"

graphNode * createNode(int vertex, int weight){
    graphNode *nn = (graphNode *)malloc(sizeof(graphNode));
    if(!nn)
        return NULL;

    nn -> vertex = vertex;
    nn -> weight = weight;
    nn -> next = NULL;
    return nn;
}

void initGraph(graph *g, char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp)
        return;

    fscanf(fp, "%d", &g->n);
    g->adjList = (graphNode **)malloc(g->n * sizeof(graphNode *));
    if(!g->adjList)
        return;

    //initialise adjlist to null
    for(int i =0; i < g->n ; i++)
        g->adjList[i]= NULL;
    
    int w;
    graphNode *nn;
    for(int i =0; i < g->n ; i++){
        //printf("%d:  ",i);
        for(int j = 0; j < g->n; j++){
            //store weight
            fscanf(fp, "%d", &w);
            if(w){ //nn created only if edge exists
                nn = createNode(j, w);
                if(!g->adjList[i]){
                    g->adjList[i]= nn;
                }
                else{
                    nn->next = g->adjList[i];
                    g->adjList[i] = nn;
                }
                    //printf("%d-%d  ", g->adjList[i]->vertex,  g->adjList[i]->weight);
            }
        }
        //printf("\n");
    }
    printf("Graph created with %d vertices\n", g->n);
    return;
}

void displayGraph(graph g){
    graphNode *p;
    for(int i = 0; i < g.n; i++){
        printf("%d:  ",i); //start vertex
        p = g.adjList[i];
        while(p){
            printf("%d-%d  ", p->vertex, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

void BFS(graph g, int start) {
    int* visited = (int*)malloc(g.n * sizeof(int));
    if(!visited)
        return;

    for (int i = 0; i < g.n; ++i)
        visited[i] = 0;

    queue q;
    initQ(&q);
    visited[start] = 1;
    enqueue(&q, start);

    while (!isEmptyQ(q)) {
        int v = dequeue(&q);
        printf("%d ", v);

        graphNode *p; 
        p = g.adjList[v];
        while (p != NULL) {
            int adjVertex = p->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(&q, adjVertex);
            }
            p = p->next;
        }
    }
    printf("\n");
    free(visited);
}

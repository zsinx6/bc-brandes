#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void read_graph(graph** g){
    int node_a, node_b;
    for(int i=0; i<(*g)->n_edges; i++){
        scanf("%d %d", &node_a, &node_b);
        create_edge(g, node_a, node_b); 
    }
}

int main(int argc, char *argv[]){
    graph *g = NULL;
    int graph_size, n_edges;
    scanf("%d", &graph_size);
    scanf("%d", &n_edges);
    create_graph(&g, graph_size, n_edges);
    read_graph(&g);
    destroy_graph(&g);
    return 0;
}

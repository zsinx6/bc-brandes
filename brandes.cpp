#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void read_graph(graph** g, FILE *input){
    int node_a, node_b;
    for(int i=0; i < (*g)->n_edges; i++){
        fscanf(input, "%d %d", &node_a, &node_b);
        create_edge(g, node_a, node_b); 
    }
}

int main(int argc, char *argv[]){
    FILE *input;
    int n_nodes, n_edges;
    graph *g = NULL;

    if(argc != 2){
        printf("Expects a FILE as argument\n");
        return 0;
    }
    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("cannot access '%s': No such file or directory\n", argv[1]);
        return 0;
    }

    fscanf(input, "%d", &n_nodes);
    fscanf(input, "%d", &n_edges);
    create_graph(&g, n_nodes, n_edges);
    read_graph(&g, input);

    fclose(input);
    destroy_graph(&g);
    return 0;
}

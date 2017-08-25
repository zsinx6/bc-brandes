#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include "graph.h"

void read_graph(graph **g, FILE *input){
    int node_a = -1, node_b = -1;
    for(int i=0; i < (*g)->n_edges; i++){
        fscanf(input, "%d %d", &node_a, &node_b);
        add_edge(g, node_a, node_b); 
        add_edge(g, node_b, node_a); 
    }
}

int main(int argc, char *argv[]){
    FILE *input = NULL;
    int n_nodes = -1, n_edges = -1;
    graph *g = NULL;
    double *Cb = NULL;

    if(argc != 2){
        printf("Expected a FILE as argument\nfor example: 'brandes input.txt'\n");
        return 0;
    }
    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("cannot access '%s': No such file or directory\n", argv[1]);
        return 0;
    }

    fscanf(input, "%d", &n_nodes);
    fscanf(input, "%d", &n_edges);
    Cb = (double*) malloc(n_nodes*sizeof(double));
    for(int i=0; i < n_nodes; i++){
        Cb[i] = 0;
    }
    create_graph(&g, n_nodes, n_edges);
    read_graph(&g, input);

    adjacent_node *node = NULL;
    for(int i=0; i<n_nodes; i++){
        node = g->nodes[i]->edges;
        printf("%d:", i);
        while(node != NULL){
            printf(" %d", node->id);
            node = node->next;
        }
        printf("\n");
    }

    fclose(input);
    destroy_graph(&g);
    free(Cb);
    return 0;
}

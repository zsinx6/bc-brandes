#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void create_graph(graph **g, int n_nodes, int n_edges){
    (*g) = (graph*) malloc(sizeof(graph));
    (*g)->n_edges = n_edges;
    (*g)->n_nodes = n_nodes;
    (*g)->nodes = (node_list**) malloc(n_nodes*sizeof(node_list*));
    for(int i=0; i < (*g)->n_nodes; i++){
        (*g)->nodes[i] = (node_list*) malloc(sizeof(node_list));
        (*g)->nodes[i]->degree = 0;
        (*g)->nodes[i]->edges = NULL;
    }
}

void destroy_graph(graph **g){
    adjacent_node *node = NULL, *node_prev = NULL;
    for(int i=0; i < (*g)->n_nodes; i++){
        for(int j=0; j < (*g)->nodes[i]->degree; j++){
            if(j==0){
                node_prev = (*g)->nodes[i]->edges;
            }
            else{
                node_prev = node;
            }
            node=node_prev->next;
            free(node_prev);
        }
        free(node);
        free((*g)->nodes[i]);
    }
    free((*g)->nodes);
    free(*g);
}

void add_edge(graph **g, int node_a, int node_b){
    adjacent_node *node = NULL;
    adjacent_node *new_node = (adjacent_node*) malloc(sizeof(adjacent_node));
    new_node->id = node_b;
    new_node->next = NULL;
    if((*g)->nodes[node_a]->edges == NULL){
        (*g)->nodes[node_a]->edges = new_node;
    }
    else{
        node = (*g)->nodes[node_a]->edges;
        while(node->next != NULL){
            node = node->next;
        }
        node->next = new_node;
    }
    (*g)->nodes[node_a]->degree += 1;
}

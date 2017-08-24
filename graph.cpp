#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void create_graph(graph **g, int n_nodes, int n_edges){
    (*g) = (graph*) malloc(sizeof(graph));
    (*g)->n_edges = n_edges;
    (*g)->n_nodes = n_nodes;
    (*g)->nodes = (node_list*) malloc(n_nodes*sizeof(node_list));
    for(int i=0; i < (*g)->n_nodes; i++){
        (*g)->nodes[i].degree = 0;
        (*g)->nodes[i].edges = NULL;
    }
}

void destroy_graph(graph **g){
    adjacent_node *node = NULL, *node_prev = NULL;
    for(int i=0; i<(*g)->n_nodes; i++){
        for(int j=0; j<(*g)->nodes[i].degree+1; j++){
            if(j==0){
                node_prev = (*g)->nodes[i].edges;
            }
            else{
                node_prev = node;
            }
            node=node_prev->next;
            free(node_prev);
        }
    }
    free((*g)->nodes);
    free(*g);
}

void append_node(adjacent_node *node_list, int node_id){
    adjacent_node *node = NULL;
    node = node_list;
    while(node->next != NULL){
        node = node->next;
    }
    node->next = (adjacent_node*) malloc(sizeof(adjacent_node));
    node = node->next;
    node->id = node_id;
    node->next = NULL;
}

void create_edge(graph **g, int node_a, int node_b){
    if((*g)->nodes[node_a].edges == NULL){
        (*g)->nodes[node_a].edges = (adjacent_node*) malloc(sizeof(adjacent_node));
        (*g)->nodes[node_a].edges->next = NULL;
    }
    if((*g)->nodes[node_b].edges == NULL){
        (*g)->nodes[node_b].edges = (adjacent_node*) malloc(sizeof(adjacent_node));
        (*g)->nodes[node_b].edges->next = NULL;
    }
    append_node((*g)->nodes[node_a].edges, node_a);
    append_node((*g)->nodes[node_b].edges, node_b);
    (*g)->nodes[node_a].degree += 1;
    (*g)->nodes[node_b].degree += 1;
}

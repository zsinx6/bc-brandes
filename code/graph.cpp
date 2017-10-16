#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void create_graph(graph **g, int n_nodes, int n_edges){
    /*
     * Function for creating the graph, given the number os edges and vertices
     */
    (*g) = (graph*) malloc(sizeof(graph));
    (*g)->n_edges = n_edges;
    (*g)->n_nodes = n_nodes;
    //it allocates the graph and initiates
    (*g)->nodes = (node_list**) malloc(n_nodes*sizeof(node_list*));
    //then, the nodes field is allocated as a array of size equals to the
    //number of nodes in the graph
    for(int i=0; i < (*g)->n_nodes; i++){
        //for each node in the graph, its allocated a neighbors list
        //starting with the degree as 0 and the pointer to the first neighbor
        //as null
        (*g)->nodes[i] = (node_list*) malloc(sizeof(node_list));
        (*g)->nodes[i]->degree = 0;
        (*g)->nodes[i]->edges = NULL;
    }
}

void destroy_graph(graph **g){
    /*
     * Function for free the memory used by the graph
     */
    adjacent_node *node = NULL, *node_prev = NULL;
    for(int i=0; i < (*g)->n_nodes; i++){
        for(int j=0; j < (*g)->nodes[i]->degree; j++){
            if(j==0){
                //special case in the first because its needed to keep track of the next
                node_prev = (*g)->nodes[i]->edges;
            }
            else{
                node_prev = node;
            }
            node=node_prev->next;
            free(node_prev);
            //for node in the neighbors list
        }
        //free in the last node for the neighbor list
        free(node);
        //free in position i of the array of nodes
        free((*g)->nodes[i]);
    }
    //free in the array of nodes
    free((*g)->nodes);
    //free in the graph
    free(*g);
}

void add_edge(graph **g, int node_a, int node_b){
    /*
     * Function to add a new edge in the graph between node_a and node_b
     * note: this graph is undirected
     */
    adjacent_node *node = NULL;
    adjacent_node *new_node = (adjacent_node*) malloc(sizeof(adjacent_node));
    new_node->id = node_b;
    new_node->next = NULL;
    //allocated memory for the new edge
    if((*g)->nodes[node_a]->edges == NULL){
        //se for o primeiro da lista
        //if is the first in the neighbor
        (*g)->nodes[node_a]->edges = new_node;
    }
    else{
        //else, searches the list for the null position, indicating the last
        //node of the neighbor list, then append the new neighbor in the end
        node = (*g)->nodes[node_a]->edges;
        while(node->next != NULL){
            node = node->next;
        }
        node->next = new_node;
    }
    //then the degree of the given node (node_a) is incremented by 1
    (*g)->nodes[node_a]->degree += 1;
}

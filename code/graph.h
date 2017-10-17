#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct adjacent_node{
    /*
     * Struct for the adjacent list, having an id and the pointer 
     * for the next
     */
    int id;
    struct adjacent_node *next;
} adjacent_node;

typedef struct node_list{
    /*
     * Struct for each node, having a list of neighbors
     * and the node's degree
     */ 
    int degree;
    struct adjacent_node *edges;
} node_list;

typedef struct graph{
    /*
     * Main structure, stores the list of all vertices,
     * the number of edges and vertices
     * graph->nodes is an array of struct node_list, so in this
     * implementation, to access a node i in the graph:
     * graph->nodes[i]
     */
    int n_edges;
    int n_nodes;
    struct node_list **nodes;
} graph;

void create_graph(graph **, int, int);

void destroy_graph(graph **);

void add_edge(graph **, int, int);

#endif

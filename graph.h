#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct adjacent_node{
    int id;
    struct adjacent_node *next;
} adjacent_node;

typedef struct node_list{
    int degree;
    struct adjacent_node *edges;
} node_list;

typedef struct graph{
    int n_edges;
    int n_nodes;
    struct node_list *nodes;
} graph;

void create_graph(graph **, int, int);

void destroy_graph(graph **);

void create_edge(graph **, int, int);

#endif

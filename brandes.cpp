#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include "graph.h"


void fscanf_error(){
    printf("I/O error\n");
    exit(1);
}

void read_graph(graph **g, FILE *input){
    /*
     * Read the input file and add the edges in the graph
     */
    int node_a = -1, node_b = -1;
    int fscanf_return;
    for(int i=0; i < (*g)->n_edges; i++){
        fscanf_return = fscanf(input, "%d %d", &node_a, &node_b);
        if(fscanf_return == EOF){
            fscanf_error();
        }
        //node: the graph is undirected, then if the edge a->b exists
        //a edge b->a needs to be created too.
        add_edge(g, node_a, node_b); 
        add_edge(g, node_b, node_a); 
    }
}

long double * brandes(graph **g){
    /*
     * The main Function, run the Betweenness Centrality based on 
     * Brandes algorithm for the graph and returns a long double array
     */
    int n_nodes = -1, *d = NULL, *sigma = NULL, v = -1, w = -1;
    int i = -1, s = -1;
    long double *delta = NULL;
    long double *Cb = NULL;
    std::stack<int> S;
    std::queue<int> Q;
    std::vector< std::vector<int> > P;
    adjacent_node *node = NULL;
    n_nodes = (*g)->n_nodes;

    sigma = (int*) malloc(n_nodes*sizeof(int));
    delta = (long double*) malloc(n_nodes*sizeof(long double));
    d = (int*) malloc(n_nodes*sizeof(int));
    Cb = (long double*) malloc(n_nodes*sizeof(long double));
    for(i=0; i < n_nodes; i++){
        //for each node i in the graph
        Cb[i] = 0.0;
    }
    for(i=0; i < n_nodes; i++){
        //P is a list of vectors, in this implementation
        //it is a vector of vectors
        P.push_back(std::vector<int>());
    }
    for(s=0; s < n_nodes; s++){
        //s is the index of the current node

        //empty stack
        while(!(S.empty())){
            S.pop();
        }
        //empty list, for all the nodes in the graph
        for(i=0; i < n_nodes; i++){
            while(!(P[i].empty())){
                P[i].pop_back();
            }
        }
        for(i=0; i < n_nodes; i++){
            //for all the nodes in the graph
            sigma[i] = 0;
            d[i] = -1;
        }
        sigma[s] = 1;
        d[s] = 0;
        //empty queue
        while(!(Q.empty())){
            Q.pop();
        }
        //start by enqueue the node s in Q
        Q.push(s);
        while(!(Q.empty())){
            //dequeue v from Q
            v = Q.front();
            Q.pop();
            //push v in S
            S.push(v);
            //for node w of neighbor of node v
            //get the first item, then iterates until the last (node==NULL)
            node = (*g)->nodes[v]->edges;
            while(node != NULL){
                w = node->id;
                //w found for the first time?
                if(d[w] < 0){
                    //enqueue w in Q
                    Q.push(w);
                    d[w] = d[v] + 1;
                }
                //shortest path to w via v?
                if(d[w] == d[v] + 1){
                    sigma[w] += sigma[v];
                    //append V in P[w]
                    P[w].push_back(v);
                }
                node = node->next;
            }
        }
        //delta[v] = 0, for each node in graph
        for(i=0; i < n_nodes; i++){
            delta[i] = 0;
        }
        //S retuns vertices in order of non-increaning distance from s
        while(!(S.empty())){
            //pop w from S
            w = S.top();
            S.pop();
            //for all nodes in P[w]
            for(std::vector<int>::size_type j = 0; j != P[w].size(); j++){
                delta[P[w][j]] += ((1.0 * sigma[P[w][j]]/sigma[w]) * (1 + delta[w]));
            }
            if(w != s){
                Cb[w] += delta[w];
            }
        }
    }
    for(i=0; i < n_nodes; i++){
        //the centrality scores must be divided by two in this case, cause the
        //graph is undirected, since all shortest paths are considered two times
        Cb[i] = Cb[i]/2;
    }
    free(sigma);
    free(delta);
    free(d);
    return Cb;
}

int main(int argc, char *argv[]){
    FILE *input = NULL, *output = NULL;
    int n_nodes = -1, n_edges = -1;
    int fscanf_return1, fscanf_return2;
    int ext_pos = 0;
    //ext_pos is the position in the input file name of the extension
    //needed for changing to .btw
    char output_name[250];
    //the output_name is a string of max size 250 for the output name
    graph *g = NULL;
    long double *Cb = NULL;

    if(argc != 2){
        //if don't have a input as argument  
        printf("Expected a FILE as argument\nfor example: 'brandes input.txt'\n");
        return 0;
    }
    input = fopen(argv[1], "r");
    if(input == NULL){
        //if any errors in opening the file for reading
        printf("cannot access '%s': No such file or directory\n", argv[1]);
        return 0;
    }

    ext_pos = strlen(argv[1]);
    for(unsigned int i=0; i < strlen(argv[1]); i++){
        //searches the argv[1] (the input file name)
        //for the '.' then keeps its position in ext_pos
        if(argv[1][i] == '.'){
            if(i != strlen(argv[1]) - 1){
                //only if the '.' position is not the last but one
                ext_pos = i;
            }
            break;
            //this break statement is important, ONLY the first '.' will
            //be treated as a extension
        }
    }
    for(int i=0; i < ext_pos; i++){
        //go to the location of the '.' -1 while copies the chars
        output_name[i] = argv[1][i];
    }
    //then, adds a '.' (in case there is no '.' in the original
    //after the last char adds a new '.') in the position ext_pos
    output_name[ext_pos] = '.';
    output_name[ext_pos+1] = 'b';
    output_name[ext_pos+2] = 't';
    output_name[ext_pos+3] = 'w';
    output_name[ext_pos+4] = '\0';

    //then the file begins to be read
    fscanf_return1 = fscanf(input, "%d", &n_nodes);
    fscanf_return2 = fscanf(input, "%d", &n_edges);
    if(fscanf_return1 == EOF || fscanf_return2 == EOF){
        fscanf_error();
    }
    create_graph(&g, n_nodes, n_edges);
    read_graph(&g, input);
    fclose(input);
    //and after all the reading the file is closed

    //at this point, all the lines of the file are already in the graph
    //so the graph is ready to be used for the brandes function

    Cb = brandes(&g);
    //Cb is a long double array, at this point contains
    //the values for Betweenness Centrality of each node of the graph

    output = fopen(output_name, "w+");
    //the output file is open for writing, that is, it will be overwritten
    for(int i=0; i < n_nodes; i++){
        fprintf(output, "%Lf\n", Cb[i]);
    }
    fclose(output);

    //after the file is closed, the memory needs to be freed
    destroy_graph(&g);
    free(Cb);
    return 0;
}

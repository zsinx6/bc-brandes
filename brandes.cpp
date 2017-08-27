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

void brandes(graph **g, long double *Cb){
    int n_nodes = -1, *d = NULL, *sigma = NULL, v = -1, w = -1;
    int i = -1, s = -1;
    long double *delta = NULL;
    std::stack<int> S;
    std::queue<int> Q;
    std::vector< std::vector<int> > P;
    adjacent_node *node = NULL;
    n_nodes = (*g)->n_nodes;
    sigma = (int*) malloc(n_nodes*sizeof(int));
    delta = (long double*) malloc(n_nodes*sizeof(long double));
    d = (int*) malloc(n_nodes*sizeof(int));
    for(int i=0; i < n_nodes; i++){
        P.push_back(std::vector<int>());
    }
    for(s=0; s < n_nodes; s++){
        //empty stack
        while(!(S.empty())){
            S.pop();
        }
        //empty list, for all
        for(i=0; i < n_nodes; i++){
            while(!(P[i].empty())){
                P[i].pop_back();
            }
        }
        for(i=0; i < n_nodes; i++){
            sigma[i] = 0;
            d[i] = -1;
        }
        sigma[s] = 1;
        d[s] = 0;
        //empty queue
        while(!(Q.empty())){
            Q.pop();
        }
        Q.push(s);
        while(!(Q.empty())){
            v = Q.front();
            Q.pop();
            S.push(v);

            //for node w of neighbor of node v
            //get the first item, then iterates until the last (node==NULL)
            node = (*g)->nodes[v]->edges;
            while(node != NULL){
                w = node->id;
                if(d[w] < 0){
                    Q.push(w);
                    d[w] = d[v] + 1;
                }
                if(d[w] == d[v] + 1){
                    sigma[w] += sigma[v];
                    P[w].push_back(v);
                }
                node = node->next;
            }
        }
    
        for(i=0; i < n_nodes; i++){
            delta[i] = 0;
        }
        while(!(S.empty())){
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
    free(sigma);
    free(delta);
    free(d);
}

int main(int argc, char *argv[]){
    FILE *input = NULL, *output = NULL;
    int n_nodes = -1, n_edges = -1;
    int ext_pos = 0;
    char output_name[150];
    graph *g = NULL;
    long double *Cb = NULL;

    if(argc != 2){
        printf("Expected a FILE as argument\nfor example: 'brandes input.txt'\n");
        return 0;
    }
    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("cannot access '%s': No such file or directory\n", argv[1]);
        return 0;
    }
    else{
        ext_pos = strlen(argv[1]);
        for(unsigned int i=0; i < strlen(argv[1]); i++){
            if(argv[1][i] == '.'){
                if(i != strlen(argv[1]) - 1){
                    ext_pos = i;
                }
                break;
            }
        }
        for(int i=0; i < ext_pos; i++){
            output_name[i] = argv[1][i];
        }
        output_name[ext_pos] = '.';
        output_name[ext_pos+1] = 'b';
        output_name[ext_pos+2] = 't';
        output_name[ext_pos+3] = 'w';
        output_name[ext_pos+4] = '\0';
    }

    fscanf(input, "%d", &n_nodes);
    fscanf(input, "%d", &n_edges);
    Cb = (long double*) malloc(n_nodes*sizeof(long double));
    for(int i=0; i < n_nodes; i++){
        Cb[i] = 0;
    }
    create_graph(&g, n_nodes, n_edges);
    read_graph(&g, input);
    fclose(input);

    brandes(&g, Cb);

    output = fopen(output_name, "w+");
    for(int i=0; i < n_nodes; i++){
        fprintf(output, "%Lf\n", Cb[i]);
    }
    fclose(output);

    destroy_graph(&g);
    free(Cb);
    return 0;
}

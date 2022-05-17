#pragma once
#include "private/private.h"
#include "private/nodes.h"
#include "private/types.h"
//https://stackoverflow.com/questions/8700246/define-scope-in-multiple-files
struct node_t{
    node_t* deps[6];
    int deps_count;
    char* sig;
    spl_t in;
    spl_t out;
    
    //[in] already pre summed at time of calling processor_func
    void* processor;
    void (*processor_func)(void*);
};

struct wire_t{
    node_t* src;
    node_t* dst;
};

struct agraph_t{
    node_t** nodes;
    int nodes_count;
    
    wire_t* wires;
    int wires_count;
    
    bool stale;
};

struct dac_t {
    node_t* io;
    spl_t* out_spl;
};

void libintdsp_init(agraph_t* graph);
int connect(agraph_t* graph, node_t* source, node_t* destination);
void disconnect(agraph_t* graph, int connection_id);
void recalc_graph(agraph_t* graph);
void proc_graph(agraph_t* graph);

void proc_dac(void* processor);
node_t* new_dac(agraph_t* graph, char* signature, int16_t* output_pointer);

#pragma once
#include <stdint.h>
#include "private/private.h"
#include "private/nodes.h"


typedef struct node_t{
    struct node_t* deps[6];
    int deps_count;
    char* sig;
    spl_t in;
    spl_t out;
    
    //[in] already pre summed at time of calling processor_func
    void* processor;
    void (*processor_func)(void*);
} node_t; 

typedef struct {
    node_t* src;
    node_t* dst;
} wire_t;

typedef struct {
    node_t** nodes;
    int nodes_count;
    
    wire_t* wires;
    int wires_count;
    
    uint8_t stale;
} agraph_t;

typedef struct  {
    node_t* io;
    spl_t* out_spl;
} dac_t;

node_t* new_node(agraph_t* gg, char* sig);
void del_node(agraph_t* gg, node_t* n);

void libintdsp_init(agraph_t* graph, int(*sin_fn)(int));
int connect(agraph_t* graph, node_t* source, node_t* destination);
void disconnect(agraph_t* graph, int connection_id);
void recalc_graph(agraph_t* graph);
void proc_graph(agraph_t* graph);

void proc_dac(void* processor);
node_t* new_dac(agraph_t* graph, char* signature, int16_t* output_pointer);

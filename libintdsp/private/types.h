#pragma once

typedef struct node_t node_t;
typedef struct wire_t wire_t;
typedef struct agraph_t agraph_t;
typedef struct dac_t dac_t;

node_t* new_node(agraph_t* gg, char* sig);
void del_node(agraph_t* gg, node_t* n);

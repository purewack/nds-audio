#ifndef _LIB
#define _LIB
#include "../private/nodes.h"

typedef struct node_t{
	int data;
	struct node_t* deps;
	void* processor;
} node_t;
node_t* new_node(char* sig);

#endif
#ifndef TYPES
#define TYPES

typedef struct node_t{
	int data;
	struct node_t* deps;
	int deps_count;
    void* processor;
    char* sig;

} node_t;
node_t* new_node(char* sig);

#endif
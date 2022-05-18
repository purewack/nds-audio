#include "lib.h"
#include <stdlib.h>

node_t* new_node(char* sig){
    node_t* n = (node_t*)malloc(sizeof(node_t));
    n->deps_count = 0;
    n->sig = sig;
    return n;
}


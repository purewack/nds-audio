#include "nodes.h"
#include <stdlib.h>

node_t* new_osc(char* sig){
    node_t* b = new_node(sig);
    osc_t* n = (osc_t*)malloc(sizeof(osc_t));
    n->freq = 440;
    b->processor = (void*)n;
    n->io = b;
    return b;
}
void set_osc_freq(osc_t* oo, int f_big, int srate){
  //256 = fixed int resolution for multiplication
  oo->freq = 1;
}
void proc_osc(void* v){
  osc_t* oo = (osc_t*)v;
  oo->freq = 2;
}
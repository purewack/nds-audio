#ifndef OSC
#define OSC

#include "types.h"

typedef struct osc_t{
	node_t* io;
	int freq;
} osc_t;
node_t* new_osc(char* sig);
void set_osc_freq(osc_t* oo, int f_big, int srate);
void proc_osc(void* v);

#endif
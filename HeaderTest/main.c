#include "lib.h"

int main(int argc, char *argv[]){

	node_t* o = new_osc("osc");
	 set_osc_freq((osc_t*)(o->processor), 10,0);
	 proc_osc(o->processor);

	return 0;
}
#include <stdio.h>
#include "libintdsp.h"

int main(){
	printf("hello main\n");
	agraph_t a;
	node_t* n = new_osc(&a,"hello");
	set_osc_freq((osc_t*)n->processor, 3000, 32000);
	proc_osc(n->processor);
	printf("%d\n",((osc_t*)(n->processor))->acc);
	printf("done\n");
	return 0;
}

#pragma once
#include "../libintdsp.h"

typedef struct adr_t{
  node_t* io;
  int32_t a_v, r_v, a;
  int32_t vv,v;
  uint8_t state, old_state;
} adr_t;

node_t* new_adr(agraph_t* graph, char* signature);
void proc_adr(void* processor);
//~30 seconds max
void set_adr_attack_ms(adr_t* processor, uint32_t ms, uint32_t srate);
//~30 seconds max
void set_adr_release_ms(adr_t* processor, uint32_t ms, uint32_t srate);
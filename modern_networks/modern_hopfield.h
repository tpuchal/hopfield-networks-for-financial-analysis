#ifndef MODERN_HOPFIELD
#define MODERN_HOPFIELD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int num_neurons;
  int num_patterns;
  float beta;
  float **keys;
  float **values;
  float *state;
} ModernHopfield;

ModernHopfield* create_modern_hopfield(int num_neurons, int num_patterns, float beta);
float calculate_energy(ModernHopfield *net);
void update_state(ModernHopfield *net);
void store_patterns(ModernHopfield *net, float **patterns);
#endif

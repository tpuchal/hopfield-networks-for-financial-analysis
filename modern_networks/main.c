#include "modern_hopfield.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main() {
  ModernHopfield *net = create_modern_hopfield(3, 2, 1.0);
 
  float pattern1[] = { 1.0, 0.5, -0.3 };
  float pattern2[] = { -0.2, 1.0, 0.7 };
  float *patterns[] = { pattern1, pattern2 };

  store_patterns(net , patterns);

  float input_state[] = { 0.9, 0.4, -0.2 };
  memcpy(net->state, input_state, 3 * sizeof(float));

  for(int i = 0 ; i < 5 ; i++) {
    update_state(net);
    printf("Step %d: Energy = %.4f\n", i, calculate_energy(net));
  }

  printf("Final state: ");
  for(int j = 0 ; j < net->num_neurons ; j++) {
    printf("%.2f ", net->state[j]);
  }
  printf("\n");

  free(net->state);
  for(int i = 0 ; i < net->num_neurons ; i++) {
    free(net->keys[i]);
    free(net->values[i]);
  }
  free(net->keys);
  free(net->values);
  free(net);
  return 0;
}

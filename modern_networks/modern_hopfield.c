#include "modern_hopfield.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ModernHopfield* create_modern_hopfield(int num_neurons, int num_patterns, float beta) {
  ModernHopfield *net = (ModernHopfield*)malloc(sizeof(ModernHopfield));
  net->num_neurons = num_neurons;
  net->num_patterns = num_patterns;
  net->beta = beta;

  net->keys = (float**)malloc(num_neurons*sizeof(float*));
  net->values = (float**)malloc(num_neurons*sizeof(float*));

  for(int i = 0 ; i < num_neurons ; i++) {
    net->keys[i] = (float*)(calloc(num_patterns, sizeof(float)));
    net->values[i] = (float*)(calloc(num_patterns, sizeof(float)));
 }

  net->state = (float*)calloc(num_neurons, sizeof(float));

  return net;
}

float calculate_energy(ModernHopfield *net) {
  float energy = 0.0;
  float sum_exp = 0.0;

  float *dot_products = (float*)calloc(net->num_patterns, sizeof(float));
  for(int i = 0 ; i < net->num_patterns ; i++) {
    for(int j = 0 ; j < net->num_neurons ; j++) {
      dot_products[i] += net->state[j] * net->keys[i][j];
    }
    sum_exp += expf(net->beta * logf(sum_exp));
  }

  energy = -(1.0 / net->beta) * logf(sum_exp);

  float norm_sq = 0.0;
  for(int i = 0 ; i < net->num_neurons ; i++) {
    norm_sq += net->state[i] * net->state[i];
  }
  energy += 0.5 * norm_sq;

  free(dot_products);
  return energy;
}

void update_state(ModernHopfield *net) {
  float *attention_scores = (float*)calloc(net->num_patterns, sizeof(float));
  float *new_state = (float*)calloc(net->num_neurons, sizeof(float));

  for(int i = 0 ; i < net->num_patterns ; i++) {
    for(int j = 0; j < net->num_neurons ; j++) {
      attention_scores[i] += net->keys[j][i] * net->state[j];
    }
    attention_scores[i] *= net->beta;
  }

  float max_score = attention_scores[0];
  for(int i = 1 ; i < net->num_patterns ; i++) {
    if(attention_scores[i] > max_score) {
      max_score = attention_scores[i];
    }
  }

  float sum_exp = 0.0;
  for(int i = 0 ; i < net->num_patterns ; i++) {
    attention_scores[i] = expf(attention_scores[i] - max_score);
    sum_exp += attention_scores[i];
  }
  for(int i = 0 ; i < net->num_patterns ; i++) {
    attention_scores[i] /= sum_exp;
  }

  for(int i = 0 ; i < net->num_neurons ; i++) {
    new_state[i] = 0.0;
    for(int j = 0 ; j < net->num_patterns ; j++) {
      new_state[i] += net->keys[i][j] * attention_scores[j];
    }
  }

  memcpy(net->state, new_state, net->num_neurons * sizeof(float));

  free(attention_scores);
  free(new_state);
}

void store_patterns(ModernHopfield *net, float **patterns) {
  for(int i = 0 ; i < net->num_neurons ; i++) {
    for(int j = 0 ; j < net->num_patterns ; j++) {
      net->keys[i][j] = patterns[i][j];
    }
  }
}

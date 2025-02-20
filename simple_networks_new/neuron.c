#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neuron.h"

HopfieldNetwork* create_network(int size) {
    HopfieldNetwork* net = (HopfieldNetwork*) malloc(sizeof(HopfieldNetwork));
    net->size = size;
    net->weights = (float**) malloc(size * sizeof(float*));
    for(int i = 0 ; i < size ; i++) {
        net->weights[i] = (float*) calloc(size, sizeof(float));
    }
    net->neurons = (int*) malloc(size * sizeof(int));

    return net;
}

void train_pattern(HopfieldNetwork* net, int* pattern) {
    for(int i = 0 ; i < net->size ; i++) {
        for(int j = 0 ; j < net->size ; j++) {
            if(i != j) {
                net->weights[i][j] += (pattern[i] * pattern[j]);
            }
        }
    }
}

void update_neuron(HopfieldNetwork* net, int index) {
    float sum = 0.0;
    for(int i = 0 ; i < net->size ; i++) {
        sum+=net->weights[index][i] * net->neurons[i];
    }
    net->neurons[index] = (sum >= 0) ? 1 : -1;
}

void update_network(HopfieldNetwork* net, int max_iter) {
    for(int iter = 0 ; iter < max_iter ; iter++) {
        for(int i = 0 ; i < net->size ; i++) {
            update_neuron(net, i);
        }
    }
}

float calculate_energy(HopfieldNetwork* net) {
    float energy = 0.0;
    for (int i = 0; i < net->size; i++) {
        for (int j = 0; j < net->size; j++) {
            energy -= net->weights[i][j] * net->neurons[i] * net->neurons[j];
        }
    }
    return energy / 2.0;
}

void recover_pattern(HopfieldNetwork *net, int *input_pattern, int max_iter) {
    for (int i = 0; i < net->size; i++) {
        net->neurons[i] = input_pattern[i];
    }
    update_network(net, max_iter);
}

void free_network(HopfieldNetwork *net) {
    for (int i = 0; i < net->size; i++) {
        free(net->weights[i]);
    }
    free(net->weights);
    free(net->neurons);
    free(net);
}
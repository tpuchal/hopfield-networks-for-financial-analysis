#ifndef NEURON_H
#define NEURON_H

typedef struct {
    int size;
    float** weights;
    int* neurons;
} HopfieldNetwork;

HopfieldNetwork* create_network(int size);

void train_pattern(HopfieldNetwork* net, int* pattern);

void update_neuron(HopfieldNetwork* net, int index);

void update_network(HopfieldNetwork* net, int max_iter);

float calculate_energy(HopfieldNetwork* net);

void recover_pattern(HopfieldNetwork *net, int *input_pattern, int max_iter);

void free_network(HopfieldNetwork *net);

#endif
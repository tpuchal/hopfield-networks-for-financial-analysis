#include <stdlib.h>
#include <stdio.h>
#include "neuron.h"

int main() {
    HopfieldNetwork *net = create_network(4);
    
    int pattern[] = {1, -1, -1, 1};
    
    train_pattern(net, pattern);
    
    int corrupted[] = {1, -1, 1, 1}; // Flip one value
    
    recover_pattern(net, corrupted, 10);
    
    printf("Recovered pattern: ");
    for (int i = 0; i < net->size; i++) {
        printf("%d ", net->neurons[i]);
    }
    printf("\nEnergy: %.2f\n", calculate_energy(net));
    
    free_network(net);
    return 0;
}
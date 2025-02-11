#ifndef NEURON_HEADER
#define NEURON_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum STATE {
    POSITIVE = 1,
    NEGATIVE = -1
};

struct Neuron {
    int state;
};

struct Network {
    int numberOfNeurons;
    struct Neuron* neurons;
    int** weights;
};

void print_network(struct Network* n) {
    printf("NETWORK STATE\n");
    printf("Number of neurons: %d\n\n", n->numberOfNeurons);
    printf("NEURON STATES\n");
    for(int i = 0; i < n->numberOfNeurons; i++) {
        printf("%d, ", n->neurons[i].state);
    }
    printf("\nWEIGHT MATRIX\n");
    for(int i = 0; i < n->numberOfNeurons; i++) {
        for(int j = 0; j < n->numberOfNeurons; j++) {
            printf("%d, ", n->weights[i][j]);
        }
        printf("\n");
    }
}

int** calculate_weight_matrix(int* pattern, int patternSize) {
    int newWeightMatrix[patternSize][patternSize];
    for(int i = 0; i < patternSize; i++) {
        for(int j = 0; j < patternSize; j++) {
            if(i == j) {
                newWeightMatrix[i][j] = 0;
            }
            else {
                newWeightMatrix[i][j] = pattern[i] * pattern[j];
            }
        }
    }

    return newWeightMatrix;
}


//allocate memory, put first pattern to store
void initiate_network(struct Network* n, int numberOfNeurons, int* initialState, int initialStateSize) {

    //initial check
    if(initialStateSize != numberOfNeurons) {
        printf("Initialization failed. Number of neurons does not match initial state size");
        return;
    }

    //define number of neurons in the network
    n->numberOfNeurons = numberOfNeurons;

    //allocate memory for weights and Neurons
    n->weights = (int**) malloc(n->numberOfNeurons * sizeof(int*));
    n->neurons = (struct Neuron*) malloc(numberOfNeurons * sizeof(struct Neuron));

    for(int i = 0; i < n->numberOfNeurons; i++) {
        n->weights[i] = (int*) malloc(n->numberOfNeurons * sizeof(int));
        n->neurons[i].state = initialState[i];

        for(int j = 0; j < n->numberOfNeurons; j++) {
            if(i == j) {
                n->weights[i][j] = 0;
            }
            else {
                n->weights[i][j] = (int) n->neurons[i].state * n->neurons[j].state;
            }
        }
    }
}

void update_network(struct Network* n){
    for(int j = 0; j < n->numberOfNeurons ; j++) {
        int weightedSum = 0;
        for(int i = 0 ; i < n->numberOfNeurons ; i++) {
            weightedSum += n->neurons[i].state * n->weights[j][i];
        }
        n->neurons[j].state = (weightedSum >= 0) ? 1 : -1;
    }
}

//function does not check whether newState has valid values
void change_network_state(struct Network* n, int* newState, int newStateSize) {

    if(newStateSize != n->numberOfNeurons)
        return;

    for(int i = 0 ; i < n->numberOfNeurons; i++) {
        n->neurons[i].state = newState[i];
    }
}

bool isStateEqual(int prevState[], struct Network* n) {

    for(int i = 0 ; i < n->numberOfNeurons ; i++) {
        if(prevState[i] != n->neurons[i].state)
            return false;
    }
    return true;
}

void converge_network(struct Network* n) {
    int prevState[n->numberOfNeurons];
    for(int i = 0 ; i < n->numberOfNeurons ; i++) {
        prevState[i] = n->neurons[i].state;
    }

    int counter = 0;
    do{
        counter++;
        update_network(n);
        print_network(n);
        for(int i = 0 ; i < n->numberOfNeurons ; i++) {
        prevState[i] = n->neurons[i].state;
        }
    } while(!isStateEqual(prevState,n));
}

void add_new_pattern(struct Network* n, int* newPattern, int newPatternSize) {
    if(newPatternSize != n->numberOfNeurons)
        return;
    
    //calculate new weight matrix
    int** newWeights = calculate_weight_matrix(newPattern,newPatternSize);
    
}

void free_network(struct Network* n) {
    for(int i = 0; i < n->numberOfNeurons; i++) {
        free(n->weights[i]);
    }
    free(n->weights);
    free(n->neurons);
}

#endif
#include <stdio.h>
#include "neuron.h"

int main() 
{

    int *patterns[] = {
        (int[]){-1, 1, -1, 1, -1, 1, -1, 1},
        (int[]){1,-1, 1, 1, -1, 1, -1, -1}
    };


   struct Network net;

   initiate_network(&net, 8, patterns[0], 8);
   print_network(&net);

   printf("AFTER NETWORK STATE CHANGE\n");
   change_network_state(&net, patterns[1], 8);
   print_network(&net);

   printf("NETWORK CONVERGENCE");
   converge_network(&net);
   print_network(&net);
    return 0;
}
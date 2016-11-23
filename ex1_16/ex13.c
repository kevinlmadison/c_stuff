#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    //go through each string in argv
    //why am i skipping argv[0]??
    for(i = 1; i < argc; i++){
        printf("arg %d: %s \n", i, argv[i]);
    }

    //Let's make our own array of strings
    char *states[] = {"California", "Oregon", "Washington", "Texassssss"};

    int num_states = 4;
    //for now this is not working to check the size of each part of the array
    long state_size = sizeof(states);
    long *state_sizes = { 0 };
    for (int i = 0; i < 4; i++){
        char *state = states[i];
        state_sizes[i] = sizeof(state);
        printf("State: %s, Size %ld \n", states[i], state_sizes[i]);
    }
    printf("State Size: %ld \n", state_size);

    for (i = 0; i < num_states; i++){
        printf("State %d: %s\n", i, states[i]);
    }
    return 0;
}

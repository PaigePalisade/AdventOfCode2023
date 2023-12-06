#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUM_SEEDS 20


#define NUM_RACES 4

int main() {
    FILE* f = fopen("input.txt", "r");

    int times[NUM_RACES];
    int distances[NUM_RACES];

    int total = 1;

    fscanf(f, "Time: ");
    for (int i = 0; i < NUM_RACES; i++) {
        fscanf(f, "%d ", &times[i]);
    }

    fscanf(f, "Distance: ");
    for (int i = 0; i < NUM_RACES; i++) {
        fscanf(f, "%d ", &distances[i]);
    }

    for (int i = 0; i < NUM_RACES; i++) {
        int numWays = 0;
        for (int t = 0; t <= times[i]; t++) {
            if (t * (times[i] - t) > distances[i]) {
                numWays ++;
            }
        }
        total *= numWays;
    }

    printf("%d\n", total);

    fclose(f);
}
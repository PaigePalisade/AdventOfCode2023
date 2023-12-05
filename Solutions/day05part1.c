#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUM_SEEDS 20


int main() {
    char name[512];

    FILE* f = fopen("input.txt", "r");

    long seeds[NUM_SEEDS];

    fscanf(f, "seeds: ");
    for (int i = 0; i < NUM_SEEDS; i++) {
        fscanf(f, "%ld ", &seeds[i]);
    }
    
    long nextSeeds[NUM_SEEDS];
    memcpy(nextSeeds, seeds, sizeof(seeds));
    
    while (!feof(f)) {
        char next = fgetc(f);
        fseek(f, -1, SEEK_CUR);
        if (next < '0' || next > '9') {
            memcpy(seeds, nextSeeds, sizeof(seeds));
            fscanf(f, "%s map: ", name);
        }
        long destination, source, range;
        fscanf(f, "%ld %ld %ld ", &destination, &source, &range);

        for (int i = 0; i < NUM_SEEDS; i++) {
            if (seeds[i] >= source && seeds[i] < source + range) {
                nextSeeds[i] = seeds[i] - source + destination;
            }
        }
    }

    memcpy(seeds, nextSeeds, sizeof(seeds));

    long lowestLocation = __INT_MAX__;

    for (int i = 0; i < NUM_SEEDS; i++) {
        if (seeds[i] < lowestLocation) {
            lowestLocation = seeds[i];
        }
    }

    printf("%d\n", lowestLocation);

    fclose(f);
}
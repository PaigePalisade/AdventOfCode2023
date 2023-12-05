#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SEEDS 512
#define INITIAL_NUM_RANGES 20

int main() {
    char name[512];

    FILE* f = fopen("input.txt", "r");

    long seeds[MAX_SEEDS] = {0};

    int numRanges = INITIAL_NUM_RANGES;

    fscanf(f, "seeds: ");
    for (int i = 0; i < numRanges; i+=2) {
        long start, run;
        fscanf(f, "%ld %ld ", &start, &run);
        seeds[i] = start;
        seeds[i+1] = start + run - 1;
    }
    
    int nextNumRanges = numRanges;
    long nextSeeds[MAX_SEEDS] = {0};
    memcpy(nextSeeds, seeds, sizeof(seeds));
    
    while (!feof(f)) {
        char next = fgetc(f);
        fseek(f, -1, SEEK_CUR);
        if (next < '0' || next > '9') {
            memcpy(seeds, nextSeeds, sizeof(seeds));
            numRanges = nextNumRanges;
            fscanf(f, "%s map: ", name);
        }
        long destination, sourceStart, range;
        fscanf(f, "%ld %ld %ld ", &destination, &sourceStart, &range);

        long sourceEnd = sourceStart + range - 1;

        for (int i = 0; i < numRanges; i+=2) {
            // fully within transformation range
            if (seeds[i] >= sourceStart && seeds[i+1] <= sourceEnd) {
                nextSeeds[i] = seeds[i] - sourceStart + destination;
                nextSeeds[i+1] = seeds[i+1] - sourceStart + destination;
            }
            // seed range overlaps and is greater than transformation range
            else if (seeds[i] >= sourceStart && seeds[i] <= sourceEnd) {
                // split the range
                long newStart = seeds[i] - sourceStart + destination;
                long newEnd = destination + range - 1;
                assert(newEnd >= newStart);
                assert(nextNumRanges + 2 <= MAX_SEEDS);
                nextSeeds[nextNumRanges] = newStart;
                nextSeeds[nextNumRanges + 1] = newEnd;
                nextNumRanges += 2;
                nextSeeds[i] = sourceEnd + 1;
                seeds[i] = sourceEnd + 1;
            }
            // seed range overlaps and is less than the transformation range
            else if (seeds[i+1] >= sourceStart && seeds[i+1] <= sourceEnd) {
                // split the range
                long newStart = destination;
                long newEnd = seeds[i+1] - sourceStart + destination;
                assert(newEnd >= newStart);
                assert(nextNumRanges + 2 <= MAX_SEEDS);
                nextSeeds[nextNumRanges] = newStart;
                nextSeeds[nextNumRanges + 1] = newEnd;
                nextNumRanges += 2;
                nextSeeds[i+1] = sourceStart - 1;
                seeds[i+1] = sourceStart - 1;
            }
        }
    }

    memcpy(seeds, nextSeeds, sizeof(seeds));
    numRanges = nextNumRanges;

    long lowestLocation = __LONG_MAX__;

    for (int i = 0; i < numRanges; i++) {
        if (seeds[i] < lowestLocation) {
            lowestLocation = seeds[i];
        }
    }

    printf("%d\n", lowestLocation);

    fclose(f);
}
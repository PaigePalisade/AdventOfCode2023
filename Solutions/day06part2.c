#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUM_RACES 4

int main() {
    FILE* f = fopen("input.txt", "r");

    char strTime[512] = "";
    char strDist[512] = "";

    long time;
    long distance;


    fscanf(f, "Time: ");
    for (int i = 0; i < NUM_RACES; i++) {
        char part[10];
        fscanf(f, "%s ", part);
        strcat(strTime, part);
    }


    fscanf(f, "Distance: ");
    for (int i = 0; i < NUM_RACES; i++) {
        char part[10];
        fscanf(f, "%s ", part);
        strcat(strDist, part);
    }

    time = atol(strTime);
    distance = atol(strDist);

    long numWays = 0;
    for (long t = 0; t <= time; t++) {
        if (t * (time - t) > distance) {
            numWays ++;
        }
    }


    printf("%ld\n", numWays);

    fclose(f);
}
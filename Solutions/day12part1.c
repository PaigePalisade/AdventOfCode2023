#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

int countPossibilities(int* hints, int numHints, char* springs, int numSprings) {
    if (numHints <= 0) {
        return 1;
    }

    int count = 0;
    for (int i = 0; i <= numSprings - hints[0]; i++) {
        int valid = 1;
        for (int j = 0; j < hints[0]; j++) {
            if (springs[i+j] == '.') {
                valid = 0;
            }
        }
        if (i + hints[0] < numSprings && springs[i + hints[0]] == '#') {
            valid = 0;
        }
        if (i > 0 && springs[i-1] == '#') {
            valid = 0;
        }
        if (numHints == 1) {
            for (int j = i+hints[0]+1; j < numSprings; j++) {
                if (springs[j] == '#') {
                    valid = 0;
                }
            }
        }

        if (valid) {
            count += countPossibilities(&hints[1], numHints-1, &springs[i+hints[0]+1], numSprings-i-hints[0]-1);
        }
        

        if (springs[i] == '#') {
            break;
        }
    }
    return count;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    int sum = 0;

    int lineNum = 1;

    while (!feof(f)) {
        char springs[512];

        int hints[512];
        int numHints = 0;

        fscanf(f, "%s ", springs);

        int numSprings = strlen(springs);

        int c = ',';
        while (c == ',') {
            fscanf(f, "%d", &hints[numHints]);
            numHints ++;
            c = fgetc(f);
        }
        int count = countPossibilities(hints, numHints, springs, numSprings);
        printf("%d %d\n", lineNum, count);
        lineNum ++;
        sum += count;
    }

    printf("%d\n", sum);

    fclose(f);
}
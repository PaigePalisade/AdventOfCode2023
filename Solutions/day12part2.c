#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

char springs[512];
int hints[512];
int numSprings;
int numHints;

long cachedAnswers[512][512];

long countPossibilities(int hintInd, int springInd) {
    if (hintInd == numHints) {
        return 1;
    }

    if (springInd < numSprings && cachedAnswers[hintInd][springInd] != -1) {
        return cachedAnswers[hintInd][springInd];
    }

    long count = 0;
    for (int i = springInd; i <= numSprings - hints[hintInd]; i++) {
        int valid = 1;
        for (int j = 0; j < hints[hintInd]; j++) {
            if (springs[i+j] == '.') {
                valid = 0;
            }
        }
        if (i + hints[hintInd] < numSprings && springs[i + hints[hintInd]] == '#') {
            valid = 0;
        }
        if (i > 0 && springs[i-1] == '#') {
            valid = 0;
        }
        if (hintInd == numHints - 1) {
            for (int j = i+hints[hintInd]+1; j < numSprings; j++) {
                if (springs[j] == '#') {
                    valid = 0;
                }
            }
        }

        if (valid) {
            count += countPossibilities(hintInd + 1, i+hints[hintInd]+1);
        }
        

        if (springs[i] == '#') {
            break;
        }
    }
    if (springInd < numSprings) {
        cachedAnswers[hintInd][springInd] = count;
    }
    return count;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long sum = 0;

    int lineNum = 1;

    while (!feof(f)) {
        
        numHints = 0;

        fscanf(f, "%s ", springs);

        numSprings = strlen(springs);

        for (int i = 1; i < 5; i++) {
            springs[(numSprings+1) * i - 1] = '?';
            for (int j = 0; j < numSprings; j++) {
                springs[j + (numSprings+1) * i] = springs[j];
            }
        }
        numSprings = numSprings * 5 + 4;

        int c = ',';
        while (c == ',') {
            fscanf(f, "%d", &hints[numHints]);
            numHints ++;
            c = fgetc(f);
        }

        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < numHints; j++) {
                hints[j + numHints * i] = hints[j];
            }
        }
        numHints *= 5;

        for (int h = 0; h < numHints; h++) {
            for (int s = 0; s < numSprings; s++) {
                cachedAnswers[h][s] = -1;
            }
        }

        long count = countPossibilities(0, 0);
        printf("%d %ld\n", lineNum, count);
        lineNum ++;
        sum += count;
    }

    printf("%ld\n", sum);
    fclose(f);
}
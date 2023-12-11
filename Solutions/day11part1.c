#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

#define SIZE 140

typedef struct {
    int x, y;
} Coords;

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    Coords galaxies[512];
    int numGalaxies = 0;

    char map[SIZE][SIZE];
    int emptyRows[SIZE] = {0};
    int emptyCols[SIZE] = {0};

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            int character = fgetc(f);
            map[r][c] = character;
        }
        fscanf(f, " ");
    }

    for (int r = 0; r < SIZE; r++) {
        int noGalaxies = 1;

        for (int c = 0; c < SIZE; c++) {
            if (map[r][c] == '#') {
                noGalaxies = 0;
            }
        }

        if (noGalaxies) {
            if (r == 0) {
                emptyRows[r] = 1;
            }
            else {
                emptyRows[r] = emptyRows[r-1] + 1;
            }
        }
        else if (r != 0) {
            emptyRows[r] = emptyRows[r-1];
        }
    }

    for (int c = 0; c < SIZE; c++) {
        int noGalaxies = 1;

        for (int r = 0; r < SIZE; r++) {
            if (map[r][c] == '#') {
                noGalaxies = 0;
            }
        }

        if (noGalaxies) {
            if (c == 0) {
                emptyCols[c] = 1;
            }
            else {
                emptyCols[c] = emptyCols[c-1] + 1;
            }
        }
        else if (c != 0) {
            emptyCols[c] = emptyCols[c-1];
        }
    }

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (map[r][c] == '#') {
                galaxies[numGalaxies] = (Coords){c + emptyCols[c], r + emptyRows[r]};
                numGalaxies ++;
            }
        }
    }

    int sum = 0;

    // find taxicab distance from each galaxy to every other galaxy
    for (int i = 0; i < numGalaxies; i++) {
        for (int j = i+1; j < numGalaxies; j++) {
            int distance = abs(galaxies[i].x - galaxies[j].x) + abs(galaxies[i].y - galaxies[j].y);
            sum += distance;
        }
    }

    printf("%d\n", sum);

    fclose(f);
}
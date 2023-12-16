#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

#define SIZE 110

#define NORTH 0b0001
#define EAST 0b0010
#define SOUTH 0b0100
#define WEST 0b1000

typedef struct {
    int r;
    int c;
    int direction;
} Beam;

char arr[SIZE][SIZE+1];

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int calcLazerStart(int startRow, int startCol, int startDir) {
    Beam beams[512];
    int numBeams = 1;

    beams[0] = (Beam){startRow, startCol, startDir};

    // energized is a bitfield of all directions that have visited the tile
    // we do not process a lazer that is going a direction already seen by that tile
    int energized[SIZE][SIZE] = {0};

    int active = 1;
    while (active) {
        active = 0;
        for (int i = 0; i < numBeams; i++) {
            int r = beams[i].r;
            int c = beams[i].c;
            int direction = beams[i].direction;
            // The equals operator has precedence over the bitwise AND. Why?????
            if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && (energized[r][c] & direction) == 0) {
                active = 1;
                energized[r][c] = energized[r][c] | direction;
                if (arr[r][c] == '/') {
                    if (direction == EAST) {
                        direction = NORTH;
                        r--;
                    }
                    else if (direction == WEST) {
                        direction = SOUTH;
                        r++;
                    }
                    else if (direction == NORTH) {
                        direction = EAST;
                        c++;
                    }
                    else if (direction == SOUTH) {
                        direction = WEST;
                        c--;
                    }
                }
                else if (arr[r][c] == '\\') {
                    if (direction == EAST) {
                        direction = SOUTH;
                        r++;
                    }
                    else if (direction == WEST) {
                        direction = NORTH;
                        r--;
                    }
                    else if (direction == NORTH) {
                        direction = WEST;
                        c--;
                    }
                    else if (direction == SOUTH) {
                        direction = EAST;
                        c++;
                    }
                }
                else if (arr[r][c] == '-' && (direction == NORTH || direction == SOUTH)) {
                    direction = EAST;
                    beams[numBeams] = (Beam){r,c-1,WEST};
                    numBeams ++;
                    assert(numBeams < 512);
                    c++;
                }
                else if (arr[r][c] == '|' && (direction == EAST || direction == WEST)) {
                    direction = NORTH;
                    beams[numBeams] = (Beam){r+1,c,SOUTH};
                    numBeams ++;
                    assert(numBeams < 512);
                    r--;
                }
                else {
                    if (direction == NORTH) {
                        r--;
                    }
                    if (direction == SOUTH) {
                        r++;
                    }
                    if (direction == EAST) {
                        c++;
                    }
                    if (direction == WEST) {
                        c--;
                    }
                }
                beams[i].direction = direction;
                beams[i].r = r;
                beams[i].c = c;
            }
        }
    }


    int count = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (energized[r][c]) {
                count ++;
            }
        }
    }

    return count;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    int maxEnergized = 0;

    for (int r = 0; r < SIZE; r++) {
        fscanf(f, "%s ", arr[r]);
    }

    for (int i = 0; i < SIZE; i++) {
        maxEnergized = max(maxEnergized, calcLazerStart(0, i, SOUTH));
        maxEnergized = max(maxEnergized, calcLazerStart(SIZE-1, i, NORTH));
        maxEnergized = max(maxEnergized, calcLazerStart(i, 0, EAST));
        maxEnergized = max(maxEnergized, calcLazerStart(i, SIZE-1, WEST));
    }

    printf("%d\n", maxEnergized);

    fclose(f);
}
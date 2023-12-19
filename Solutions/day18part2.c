#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"
#define NUM_INSTR 674

typedef struct {
    long x;
    long y;
} Vertex;

typedef struct {
    char dir;
    int length;
} Instr;

long max(long a, long b) {
    if (a > b) {
        return a;
    }
    return b;
}

long min(long a, long b) {
    if (a < b) {
        return a;
    }
    return b;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    Instr plan[NUM_INSTR];

    long curRow = 0;
    long curCol = 0;

    for (int i = 0; i < NUM_INSTR; i++) {
        char fakeDir;
        int fakeLength;
        int dirInd = 0;

        fscanf(f, "%c %d (#%5x%d) ", &fakeDir, &fakeLength, &plan[i].length, &dirInd);

        // plan[i].length = fakeLength;
        // plan[i].dir = fakeDir;

        // yes, you can index a string literal in C for some reason
        plan[i].dir = "RDLU"[dirInd];

        printf("%d: %c %d\n", i, plan[i].dir, plan[i].length);
    }

    // store the vertices of the polygons
    Vertex verts[NUM_INSTR + 1];
    verts[0] = (Vertex){0,0};
    int numVertices = 1;

    int offsetX = 0;
    int offsetY = 0;

    char clockwiseMap[256];
    char counterClockwiseMap[256];
    clockwiseMap['U'] = 'R';
    clockwiseMap['R'] = 'D';
    clockwiseMap['D'] = 'L';
    clockwiseMap['L'] = 'U';

    int isClockWise = 0;

    // this code only works if the first instruction is R and it is going clockwise, which is the case for my input and the test case
    if (clockwiseMap[plan[NUM_INSTR-1].dir] == plan[0].dir) {
        printf("Clockwise!\n");
        isClockWise = 1;
    }
    else {
        printf("Counter clockwise!\n");
        return 1;
    }

    for (int i = 0; i < NUM_INSTR; i++) {
        char dir = plan[i].dir;
        
        char nextDir = plan[(i+1) % NUM_INSTR].dir;
        int length = plan[i].length;

        // change in x and y for the direction
        long dx = 0;
        long dy = 0;

        switch (dir) {
            case 'U':
                dy -= length;
                if (nextDir == clockwiseMap['U']) {
                    offsetY = 0;
                }
                else {
                    offsetY = 1;
                }
                break;
            case 'D':
                dy += length;
                if (nextDir == clockwiseMap['D']) {
                    offsetY = 1;
                }
                else {
                    offsetY = 0;
                }
                break;
            case 'L':
                dx -= length;
                if (nextDir == clockwiseMap['L']) {
                    offsetX = 0;
                }
                else {
                    offsetX = 1;
                }
                break;
            case 'R':
                dx += length;
                if (nextDir == clockwiseMap['R']) {
                    offsetX = 1;
                }
                else {
                    offsetX = 0;
                }
                break;
        }
        long startRow = curRow;

        curRow += dy;
        curCol += dx;
        verts[numVertices] = (Vertex){curCol + offsetX, curRow + offsetY};

        numVertices ++;
    }

    // Algorithm from: https://stackoverflow.com/questions/451426/how-do-i-calculate-the-area-of-a-2d-polygon
    long totalArea = 0;

    for (int i = 0; i < numVertices; i++) {
        int j = (i+1) % numVertices;
        totalArea += verts[i].x * verts[j].y;
        totalArea -= verts[i].y * verts[j].x;
    }

    totalArea /= 2;

    printf("%ld\n", totalArea);

    fclose(f);
}
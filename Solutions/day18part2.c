#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "test.txt"
#define NUM_INSTR 14
#define MAX_EDGES 2048

typedef struct {
    char dir;
    int length;
} Instr;

typedef struct {
    long c;
    long r1;
    long r2;
} VerticalEdge;

int compareEdges(const void* a, const void* b) {
    VerticalEdge* e1 = (VerticalEdge*) a;
    VerticalEdge* e2 = (VerticalEdge*) b;

    return e1->c - e2->c;
}

int compareLongs(const void* a, const void* b) {
    long* l1 = (long*) a;
    long* l2 = (long*) b;
    if (*l1 - *l2 == 0l) {
        return 0;
    }
    if (*l1 - *l2 < 0l) {
        return -1;
    }
    return 1;
}

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

        plan[i].length = fakeLength;
        plan[i].dir = fakeDir;

        // yes, you can index a string literal in C for some reason
        // plan[i].dir = "RDLU"[dirInd];

        printf("%d: %c %d\n", i, plan[i].dir, plan[i].length);
    }

    int numEdges = 0;
    VerticalEdge edges[MAX_EDGES];

    for (int i = 0; i < NUM_INSTR; i++) {
        char dir = plan[i].dir;
        int length = plan[i].length;

        // change in x and y for the direction
        long dx = 0;
        long dy = 0;

        switch (dir) {
            case 'U':
                dy = -length;
                break;
            case 'D':
                dy = length;
                break;
            case 'L':
                dx = -length;
                break;
            case 'R':
                dx = length;
                break;
        }
        long startRow = curRow;

        curRow += dy;
        curCol += dx;

        if (dir == 'U' || dir == 'D') {
            edges[numEdges] = (VerticalEdge){curCol, min(startRow, curRow), max(startRow, curRow)};
            numEdges ++;
            assert(numEdges < MAX_EDGES);
        }
    }

    // optimized raycasting algorithm

    // rows where a vertical edge starts
    long sigRows[MAX_EDGES * 2];
    int numSigRows = 0;

    for (int i = 0; i < numEdges; i++) {
        sigRows[numSigRows] = edges[i].r1;
        numSigRows ++;
        assert(numSigRows < MAX_EDGES * 2);
        sigRows[numSigRows] = edges[i].r2;
        numSigRows ++;
        assert(numSigRows < MAX_EDGES * 2);
    }

    // sort the edges by their columns and the significant rows
    qsort(edges, numEdges, sizeof(VerticalEdge), compareEdges);
    qsort(sigRows, numSigRows, sizeof(long), compareLongs);

    long totalArea = 0;

    // calculate the area of the non significant rows
    for (int i = 0; i < numSigRows; i++) {
        long r = sigRows[i];
        long area = 0;
        int inShape = 0;
        long prevCol = 0;

        for (int j = 0; j < numEdges; j++) {
            if (r >= edges[j].r1 && r < edges[j].r2) {
                if (!inShape) {
                    inShape = 1;
                    prevCol = edges[j].c;
                }
                else {
                    inShape = 0;
                    area += edges[j].c - prevCol + 1;
                }
            }
        }
        assert(area >= 0);
        if (i != numSigRows - 1) {
            if (sigRows[i+1] != sigRows[i]) {
                printf("%ld, %ld\n", area, (sigRows[i+1] - sigRows[i] - 1));
                area *= (sigRows[i+1] - sigRows[i] - 1);
                totalArea += area;
            }
        }
        assert(totalArea >= 0);
    }


    printf("%ld\n", totalArea);

    fclose(f);
}
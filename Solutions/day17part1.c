#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"
#define SIZE 141

#define NORTH 0b0001
#define EAST 0b0010
#define SOUTH 0b0100
#define WEST 0b1000

#define MAX_HEAP_SIZE 10000

typedef struct {
    int r, c;
    int dist;
    int dir;
    int run;
} Node;

Node heap[MAX_HEAP_SIZE] = {0};
int heapSize = 0;

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

// used during debugging, verifies that the heap is a heap
void sanityCheck() {
    for (int i = 1; i < heapSize; i++) {
        assert(heap[i].dist >= heap[(i-1)/2].dist);
    }
}

// min heap for priority queue
void enqueue(Node n) {
    int ind = heapSize;
    heapSize ++;
    assert(heapSize <= MAX_HEAP_SIZE);

    while (ind != 0 && n.dist < heap[(ind-1)/2].dist) {
        heap[ind] = heap[(ind-1)/2];
        ind = (ind-1)/2;
    }
    heap[ind] = n;
}

Node dequeue() {
    if (heapSize == 1) {
        heapSize --;
        return heap[0];
    }

    Node res = heap[0];
    heap[0] = heap[heapSize-1];
    heapSize --;

    int ind = 0;
    int smallest;
    int done = 0;
    while (!done) {
        smallest = ind;
        int left = ind * 2 + 1;
        int right = ind * 2 + 2;
        if (left < heapSize && heap[left].dist < heap[smallest].dist) {
            smallest = left;
        }
        if (right < heapSize && heap[right].dist < heap[smallest].dist) {
            smallest = right;
        }
        if (smallest != ind) {
            Node temp = heap[ind];
            heap[ind] = heap[smallest];
            heap[smallest] = temp;
            ind = smallest;
        }
        else {
            done = 1;
        }
    }
    return res;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char arr[SIZE][SIZE + 1];

    for (int r = 0; r < SIZE; r++) {
        fscanf(f, "%s ", arr[r]);
    }

    int res = -1;

    // stores the minimum run value for every direction for every tile
    int visitedRuns[SIZE][SIZE][4];
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            for (int i = 0; i < 4; i++) {
                visitedRuns[r][c][i] = 4;
            }
        }
    }

    enqueue((Node){0,0,0,0});

    while (heapSize != 0) {
        Node n = dequeue();
        int r = n.r;
        int c = n.c;
        int dist = n.dist;
        int dir = n.dir;
        int run = n.run;

        int oldRun = 4;
        
        for (int i = 0; i < 4; i++) {
            if ((1 << i) == dir) {
                oldRun = visitedRuns[r][c][i];
                visitedRuns[r][c][i] = min(visitedRuns[r][c][i], run);
            }
        }
        
        if (r == SIZE - 1 && c == SIZE - 1) {
            res = dist;
            break;
        }

        if (run < oldRun) {
            // somewhat cursed for loop
            for (int newDir = NORTH; newDir <= WEST; newDir <<= 1) {
                // if the directions are not opposite (I'm having a bit of fun with bitwise operators)
                if ((newDir | dir) != (NORTH | SOUTH) && (newDir | dir) != (EAST | WEST)) {
                    if (dir != newDir) {
                        if (newDir == NORTH && r - 1 >= 0) {
                            enqueue((Node){r-1, c, dist + (arr[r-1][c] - '0'), newDir, 1});
                        }
                        if (newDir == EAST && c + 1 < SIZE) {
                            enqueue((Node){r, c+1, dist + (arr[r][c+1] - '0'), newDir, 1});
                        }
                        if (newDir == SOUTH && r + 1 < SIZE) {
                            enqueue((Node){r+1, c, dist + (arr[r+1][c] - '0'), newDir, 1});
                        }
                        if (newDir == WEST && c - 1 >= 0) {
                            enqueue((Node){r, c-1, dist + (arr[r][c-1] - '0'), newDir, 1});
                        }
                    }
                    else if (run < 3) {
                        if (newDir == NORTH && r - 1 >= 0) {
                            enqueue((Node){r-1, c, dist + (arr[r-1][c] - '0'), newDir, run + 1});
                        }
                        if (newDir == EAST && c + 1 < SIZE) {
                            enqueue((Node){r, c+1, dist + (arr[r][c+1] - '0'), newDir, run + 1});
                        }
                        if (newDir == SOUTH && r + 1 < SIZE) {
                            enqueue((Node){r+1, c, dist + (arr[r+1][c] - '0'), newDir, run + 1});
                        }
                        if (newDir == WEST && c - 1 >= 0) {
                            enqueue((Node){r, c-1, dist + (arr[r][c-1] - '0'), newDir, run + 1});
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", res);

    fclose(f);
}
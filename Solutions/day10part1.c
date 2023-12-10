#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

#define SIZE 140

#define NORTH 0b0001
#define EAST 0b0010
#define SOUTH 0b0100
#define WEST 0b1000

// hardcode the type of pipe the start is
// vertical in my case
#define START NORTH | SOUTH

typedef struct Node Node;

struct Node {
    int r, c;
    Node* next;
};

// bfs queue
Node* front;
Node* back;

void enqueue(int r, int c) {
    if (front == NULL) {
        front = (Node*)calloc(1, sizeof(Node));
        back = front;
        front->r = r;
        front->c = c;
    }
    else {
        Node* newNode = (Node*)calloc(1, sizeof(Node));
        newNode-> r = r;
        newNode->c = c;
        back->next = newNode;
        back = newNode;
    }
}

void dequeue(int* r, int* c) {
    *r = front->r;
    *c = front->c;

    Node* newFront = front->next;
    free(front);
    front = newFront;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    int map[SIZE][SIZE] = {0};
    int distances[SIZE][SIZE] = {0};
    

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            distances[r][c] = -1;
            int character = fgetc(f);
            if (character == '|') {
                map[r][c] = NORTH | SOUTH;
            }
            if (character == '-') {
                map[r][c] = EAST | WEST;
            }
            if (character == 'L') {
                map[r][c] = NORTH | EAST;
            }
            if (character == 'J') {
                map[r][c] = NORTH | WEST;
            }
            if (character == '7') {
                map[r][c] = SOUTH | WEST;
            }
            if (character == 'F') {
                map[r][c] = SOUTH | EAST;
            }
            if (character == '.') {
                map[r][c] = 0;
            }
            if (character == 'S') {
                map[r][c] = START;
                enqueue(r, c);
                distances[r][c] = 0;
            }
        }
        fscanf(f, " ");
    }
    
    while (front) {
        int r, c;

        dequeue(&r, &c);

        int directions = map[r][c];
        if ((directions & NORTH) && r-1 >= 0 && distances[r-1][c] == -1) {
            distances[r-1][c] = distances[r][c] + 1;
            enqueue(r-1,c);
        }
        if ((directions & SOUTH) && r+1 < SIZE && distances[r+1][c] == -1) {
            distances[r+1][c] = distances[r][c] + 1;
            enqueue(r+1,c);
        }
        if ((directions & WEST) && c-1 >= 0 && distances[r][c-1] == -1) {
            distances[r][c-1] = distances[r][c] + 1;
            enqueue(r,c-1);
        }
        if ((directions & EAST) && c+1 < SIZE && distances[r][c+1] == -1) {
            distances[r][c+1] = distances[r][c] + 1;
            enqueue(r,c+1);
        }
    }

    int maxDistance = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (distances[r][c] > maxDistance) {
                maxDistance = distances[r][c];
            }
        }
    }

    printf("%d\n", maxDistance);

    fclose(f);
}
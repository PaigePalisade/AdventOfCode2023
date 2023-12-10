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
#define S_CHAR '|'

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
    char mapc[SIZE][SIZE] = {0};
    int distances[SIZE][SIZE] = {0};
    

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            distances[r][c] = -1;
            int character = fgetc(f);
            mapc[r][c] = character;
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
                mapc[r][c] = S_CHAR;
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

    int count = 0;

    // ray casting algorithm
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (distances[r][c] == -1) {
                int inLoop = 0;
                for (int c2 = 0; c2 < c; c2++) {
                    if (distances[r][c2] != -1 && (mapc[r][c2] == 'L' || mapc[r][c2] == 'J' || mapc[r][c2] == '|')) {
                        inLoop = !inLoop;
                    }
                }
                if (inLoop) {
                    mapc[r][c] = '+';
                    count ++;
                }
                else {
                    mapc[r][c] = '.';
                }
            }
        }
    }

    // loop looks really pretty if we print it like this
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (distances[r][c] != -1) {
                if (mapc[r][c] == 'F') {
                    printf("┌");
                }
                if (mapc[r][c] == '7') {
                    printf("┐");
                }
                if (mapc[r][c] == 'L') {
                    printf("└");
                }
                if (mapc[r][c] == 'J') {
                    printf("┘");
                }
                if (mapc[r][c] == '|') {
                    printf("│");
                }
                if (mapc[r][c] == '-') {
                    printf("─");
                }
            }
            else {
                printf("%c", mapc[r][c]);
            }
        }
        printf("\n");
    }

    printf("%d\n", count);

    fclose(f);
}
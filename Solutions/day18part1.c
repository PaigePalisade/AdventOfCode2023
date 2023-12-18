#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"
#define NUM_INSTR 674

#define NUM_ROWS 1000
#define NUM_COLS 1000

// a value isn't, used, just there so that it is 32 bits
typedef struct {
    unsigned char b, g, r, a;
} Color;

typedef struct {
    char dir;
    int length;
    Color color;
} Instr;

void floodFill(int arr[NUM_ROWS][NUM_COLS], int r, int c) {
    if (r < 0 || r >= NUM_ROWS || c < 0 || c >= NUM_COLS) {
        return;
    }
    arr[r][c] = 1;
    if (!arr[r-1][c]) {
        floodFill(arr, r-1, c);
    }
    if (!arr[r+1][c]) {
        floodFill(arr, r+1, c);
    }
    if (!arr[r][c-1]) {
        floodFill(arr, r, c-1);
    }
    if (!arr[r][c+1]) {
        floodFill(arr, r, c+1);
    }
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    Instr plan[NUM_INSTR];

    int arr[NUM_ROWS][NUM_COLS] = {0};



    int curRow = 0;
    int curCol = 0;

    for (int i = 0; i < NUM_INSTR; i++) {
        fscanf(f, "%c %d (#%x) ", &plan[i].dir, &plan[i].length, &plan[i].color);
    }

    int maxRow = 0;
    int maxCol = 0;
    int minRow = 0;
    int minCol = 0;

    for (int i = 0; i < NUM_INSTR; i++) {
        char dir = plan[i].dir;
        int length = plan[i].length;
        Color color = plan[i].color;

        // change in x and y for the direction
        int dx = 0;
        int dy = 0;

        switch (dir) {
            case 'U':
                dy = -1;
                break;
            case 'D':
                dy = 1;
                break;
            case 'L':
                dx = -1;
                break;
            case 'R':
                dx = 1;
                break;
        }
        for (int j = 0; j < length; j++) {
            curRow += dy;
            curCol += dx;

            if (curRow > maxRow) {
                maxRow = curRow;
            }
            if (curRow < minRow) {
                minRow = curRow;
            }
            if (curCol > maxCol) {
                maxCol = curCol;
            }
            if (curCol < minCol) {
                minCol = curCol;
            }

            arr[curRow + NUM_ROWS/2][curCol + NUM_COLS/2] = 1;
            
        }
    }

    floodFill(arr, 1 + NUM_ROWS/2, 1 + NUM_COLS/2);

    int totalArea = 0;
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            if (arr[r][c]) {
                totalArea ++;
            }
        }
    }

    printf("%d\n", totalArea);

    fclose(f);
}
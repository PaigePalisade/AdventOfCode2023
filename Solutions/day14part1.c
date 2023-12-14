#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

#define SIZE 100

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char arr[SIZE][SIZE];

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            arr[r][c] = fgetc(f);
        }
        fgetc(f);
    }
    printf("\n");

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (arr[r][c] == 'O') {
                arr[r][c] = '.';
                for (int r2 = r; r2 >= 0; r2--) {
                    if (r2 == 0 || arr[r2 - 1][c] == '#' || arr[r2 - 1][c] == 'O') {
                        arr[r2][c] = 'O';
                        break;
                    }
                }
            }
        }
    }

    int sum = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            printf("%c", arr[r][c]);
            if (arr[r][c] == 'O') {
                sum += SIZE - r;
            }
        }
        printf("\n");
    }

    printf("%d\n", sum);

    fclose(f);
}
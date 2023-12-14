#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// hey, did you know C has a built in hash table library, that's pretty wild
#include <search.h>

#define FILE_NAME "input.txt"

#define SIZE 100
#define MAX_ITERATIONS 1000

char arr[SIZE * SIZE + 1];

void printArr() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            printf("%c", arr[r * SIZE + c]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");


    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            arr[r * SIZE + c] = fgetc(f);
        }
        fgetc(f);
    }

    arr[SIZE * SIZE + 1] = '\0';

    hcreate(MAX_ITERATIONS);
    // array storing 0 to MAX_ITERATIONS - 1
    int indexes[MAX_ITERATIONS];

    char* keys[MAX_ITERATIONS];

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        keys[i] = malloc(sizeof(arr));
    }

    int found = 0;

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // north
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (arr[r * SIZE + c] == 'O') {
                    arr[r* SIZE + c] = '.';
                    for (int r2 = r; r2 >= 0; r2--) {
                        if (r2 == 0 || arr[(r2 - 1) * SIZE + c] == '#' || arr[(r2 - 1) * SIZE + c] == 'O') {
                            arr[r2 * SIZE + c] = 'O';
                            break;
                        }
                    }
                }
            }
        }
        // west
        for (int c = 0; c < SIZE; c++) {
            for (int r = 0; r < SIZE; r++) {
                if (arr[r * SIZE + c] == 'O') {
                    arr[r * SIZE + c] = '.';
                    for (int c2 = c; c2 >= 0; c2--) {
                        if (c2 == 0 || arr[r * SIZE + c2 - 1] == '#' || arr[r * SIZE + c2 - 1] == 'O') {
                            arr[r * SIZE + c2] = 'O';
                            break;
                        }
                    }
                }
            }
        }
        // south
        for (int r = SIZE - 1; r >= 0; r--) {
            for (int c = 0; c < SIZE; c++) {
                if (arr[r * SIZE + c] == 'O') {
                    arr[r * SIZE + c] = '.';
                    for (int r2 = r; r2 < SIZE; r2++) {
                        if (r2 == SIZE - 1 || arr[(r2 + 1) * SIZE + c] == '#' || arr[(r2 + 1) * SIZE + c] == 'O') {
                            arr[r2* SIZE + c] = 'O';
                            break;
                        }
                    }
                }
            }
        }
        // east
        for (int c = SIZE - 1; c >= 0; c--) {
            for (int r = 0; r < SIZE; r++) {
                if (arr[r * SIZE + c] == 'O') {
                    arr[r * SIZE + c] = '.';
                    for (int c2 = c; c2 < SIZE; c2++) {
                        if (c2 == SIZE - 1 || arr[r * SIZE + c2 + 1] == '#' || arr[r * SIZE + c2 + 1] == 'O') {
                            arr[r * SIZE + c2] = 'O';
                            break;
                        }
                    }
                }
            }
        }
        printf("index: %d: \n", i);
        printArr();

        indexes[i] = i;
        strcpy(keys[i], arr);

        ENTRY* res = hsearch((ENTRY){keys[i], &indexes[i]}, FIND);
        if (res != NULL) {
            int matchingInd = *(int*)res->data;
            printf("Eureka: %d\n", matchingInd);
            strcpy(arr, keys[(999999999 - i) % (i - matchingInd) + matchingInd]);
            found = 1;
            break;
        }
        hsearch((ENTRY){keys[i], &indexes[i]}, ENTER);
    }

    hdestroy();

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        free(keys[i]);
    }

    if (found) {
        int sum = 0;
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (arr[r * SIZE + c] == 'O') {
                    sum += SIZE - r;
                }
            }
        }
        printf("%d\n", sum);
    }


    fclose(f);
}
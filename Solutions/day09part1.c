#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"
#define NUMS_PER_LINE 21
// #define NUMS_PER_LINE 6

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    assert(f != NULL);

    long sum = 0;
    while (!feof(f)) {
        long arr[512][NUMS_PER_LINE + 1] = {0};
        int length = 0;
        int c = 0;
        while (c != '\n' && !feof(f)) {
            fscanf(f, "%ld ", &arr[0][length]);
            length ++;
            fseek(f, -1, SEEK_CUR);
            c = fgetc(f);
            fscanf(f, " ");
        }
        int numIters = 0;
        for (int i = 1; i < 512; i++) {
            numIters ++;
            int allZeros = 1;
            for (int j = 0; j < length - i; j++) {
                arr[i][j] = arr[i-1][j+1] - arr[i-1][j];
                if (arr[i-1][j+1] - arr[i-1][j] != 0) {
                    allZeros = 0;
                }
            }
            if (allZeros) {
                break;
            }
        }
        for (int i = numIters - 1; i >= 0; i--) {
            arr[i][length-i] = arr[i][length-i-1] + arr[i+1][length-i-1];
        }
        sum += arr[0][length];
    }

    printf("%ld\n", sum);

    fclose(f);
}
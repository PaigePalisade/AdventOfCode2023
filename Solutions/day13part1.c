#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

char arr[64][64];
int numCols;
int numRows;

int rowEquals(int r1, int r2) {
    for (int c = 0; c < numCols; c++) {
        if (arr[r1][c] != arr[r2][c]) {
            return 0;
        }
    }
    return 1;
}

int colEquals(int c1, int c2) {
    for (int r = 0; r < numRows; r++) {
        if (arr[r][c1] != arr[r][c2]) {
            return 0;
        }
    }
    return 1;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int getVerticalMirror() {
    for (int i = 1; i < numCols; i++) {
        int isMirror = 1;
        for (int j = 1; j <= min(i, numCols - i); j++) {
            if (!colEquals(i-j, i+j-1)) {
                isMirror = 0;
                break;
            }
        }
        if (isMirror) {
            return i;
        }
    }
    // no mirror found
    return 0;
}

int getHorizontallMirror() {
    for (int i = 1; i < numRows; i++) {
        int isMirror = 1;
        for (int j = 1; j <= min(i, numRows - i); j++) {
            if (!rowEquals(i-j, i+j-1)) {
                isMirror = 0;
                break;
            }
        }
        if (isMirror) {
            return i;
        }
    }
    // no mirror found
    return 0;
}


int main() {
    FILE* f = fopen(FILE_NAME, "r");

    int sum = 0;

    int c = 0;

    while (c != EOF) {
        numCols = 0;
        numRows = 0;

        c = 0;
        while (c != '\n' && c != EOF) {
            fscanf(f, "%s", arr[numRows]);
            numRows ++;

            fgetc(f);
            c = fgetc(f);
            fseek(f, -1, SEEK_CUR);
        }

        numCols = strlen(arr[0]);

        int mirrorValue = getVerticalMirror();
        if (mirrorValue == 0) {
            mirrorValue = getHorizontallMirror() * 100;
        }

        sum += mirrorValue;

        printf("%d\n", mirrorValue);
    }

    printf("%d\n", sum);

    fclose(f);
}
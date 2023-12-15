#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long sum = 0;
    int hash = 0;

    while (!feof(f)){
        int c = fgetc(f);

        if (c == ',' || c == EOF) {
            printf("%d\n", hash);
            sum += hash;
            hash = 0;
        }

        else {
            hash += c;
            hash *= 17;
            hash %= 256;
        }
    }

    printf("%ld\n", sum);

    fclose(f);
}
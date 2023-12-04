#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUM_WIN 10
#define NUM_HAVE 25
#define NUM_CARDS 199

// #define NUM_WIN 5
// #define NUM_HAVE 8
// #define NUM_CARDS 6

int main() {
    FILE* f = fopen("input.txt", "r");

    int cardNumber;

    int winning[NUM_WIN];
    int have[NUM_HAVE];

    int copies[NUM_CARDS];
    for (int i = 0; i < NUM_CARDS; i++) {
        copies[i] = 1;
    }

    int sum = 0;

    while (!feof(f)) {
        fscanf(f, "Card %d: ", & cardNumber);

        cardNumber --;

        for (int i = 0; i < NUM_WIN; i++) {
            fscanf(f, "%d ", &winning[i]);
        }

        fscanf(f, "| ");

        for (int i = 0; i < NUM_HAVE; i++) {
            fscanf(f, "%d ", &have[i]);
        }

        int score = 0;

        for (int i = 0; i < NUM_WIN; i++) {
            for (int j = 0; j < NUM_HAVE; j++) {
                if (winning[i] == have[j]) {
                    score ++;
                }
            } 
        }
        for (int i = 1; i <= score; i++) {
            copies[cardNumber + i] += copies[cardNumber];
        }
        sum += copies[cardNumber];
    }

    printf("%d\n", sum);

    fclose(f);
}
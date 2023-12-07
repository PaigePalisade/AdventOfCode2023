#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUM_HANDS 1000
#define FILE_NAME "input.txt"

typedef struct {
    char hand[6];
    int bid;
    int type;
} Hand;

int calcValue(char c) {
    if (c == 'A') {
        return 14;
    }
    if (c == 'K') {
        return 13;
    }
    if (c == 'Q') {
        return 12;
    }
    if (c == 'J') {
        return 11;
    }
    if (c == 'T') {
        return 10;
    }
    return c - '0';
}

int comparison(const void* a, const void* b) {
    Hand* h1 = (Hand*)a;
    Hand* h2 = (Hand*)b;

    if (h1->type != h2->type) {
        return h1->type - h2->type;
    }
    else {
        for (int i = 0; i < 5; i++) {
            if (h1->hand[i] != h2->hand[i]) {
                return calcValue(h1->hand[i]) - calcValue(h2->hand[i]);
            }
        }
    }
    return 0;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    Hand hands[NUM_HANDS];

    for (int i = 0; i < NUM_HANDS; i++) {
        fscanf(f, "%s ", hands[i].hand);
        fscanf(f, "%d ", &hands[i].bid);
        int count[256] = {0};
        for (int j = 0; j < 5; j++) {
            count[hands[i].hand[j]] ++;
        }
        int maxCount = 0;
        int maxCountInd = -1;
        int secondMaxCount = 0;
        for (int j = 0; j < 256; j++) {
            if (count[j] > maxCount) {
                maxCount = count[j];
                maxCountInd = j;
            }
        }
        for (int j = 0; j < 256; j++) {
            if (count[j] > secondMaxCount && j != maxCountInd) {
                secondMaxCount = count[j];
            }
        }
        if (maxCount == 5) {
            hands[i].type = 7;
            printf("Five of a kind\n");
        }
        else if (maxCount == 4) {
            hands[i].type = 6;
            printf("Four of a kind\n");
        }
        else if (maxCount == 3 && secondMaxCount == 2) {
            hands[i].type = 5;
            printf("Full house\n");
        }
        else if (maxCount == 3) {
            hands[i].type = 4;
            printf("Three of a kind\n");
        }
        else if (maxCount == 2 && secondMaxCount == 2) {
            hands[i].type = 3;
            printf("Two Pair\n");
        }
        else if (maxCount == 2) {
            hands[i].type = 2;
            printf("One Pair\n");
        }
        else {
            hands[i].type = 1;
            printf("High Card\n");
        }
    }

    qsort(hands, NUM_HANDS, sizeof(Hand), comparison);

    long total = 0;

    for (int i = 0; i < NUM_HANDS; i++) {
        printf("%d %s\n", i+1, hands[i].hand);
        total += (long)hands[i].bid * (long)(i+1);
    }

    printf("%ld\n", total);

    fclose(f);
}
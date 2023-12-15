#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

typedef struct {
    char label[10];
    int focal;
} Lens;

typedef struct {
    Lens lenses[512];
    int length;
} Box;

Box boxes[256];

int hash(char* label) {
    int res = 0;
    int len = strlen(label);
    for (int i = 0; i < len; i++) {
        res += label[i];
        res *= 17;
        res %= 256;
    }
    if (res != 0) {
        printf("%d\n", res);
    }
    return res;
}

void addBox(char* label, int focal) {
    int boxNum = hash(label);
    
    int found = 0;
    for (int i = 0; i < boxes[boxNum].length; i++) {
        if (strcmp(boxes[boxNum].lenses[i].label, label) == 0) {
            found = 1;
            boxes[boxNum].lenses[i].focal = focal;
        }
    }
    if (!found) {
        strcpy(boxes[boxNum].lenses[boxes[boxNum].length].label, label);
        boxes[boxNum].lenses[boxes[boxNum].length].focal = focal;
        boxes[boxNum].length ++;
    }
}

void removeBox(char* label) {
    int boxNum = hash(label);

    int ind = -1;
    for (int i = 0; i < boxes[boxNum].length; i++) {
        if (strcmp(boxes[boxNum].lenses[i].label, label) == 0) {
            ind = i;
            break;
        }
    }
    if (ind != -1) {
        boxes[boxNum].length --;
        for (int i = ind; i < boxes[boxNum].length; i++) {
            boxes[boxNum].lenses[i] = boxes[boxNum].lenses[i+1];
        }
    }
}

void printBoxes() {
    for (int i = 0; i < 256; i++) {
        if (boxes[i].length != 0) {
            printf("Box: %d ", i);
            for (int j = 0; j < boxes[i].length; j++) {
                printf("[%s %d] ", boxes[i].lenses[j].label, boxes[i].lenses[j].focal);
            }
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char label[10];
    int labelLength = 0;

    while (!feof(f)){
        int c = fgetc(f);

        if (c == '=') {
            int focal = fgetc(f) - '0';
            fgetc(f);
            printf("After \"%s=%d\":\n", label, focal);
            addBox(label, focal);
            printBoxes();
            label[0] = '\0';
            labelLength = 0;
        }
        else if (c == '-') {
            fgetc(f);
            printf("After \"%s-\":\n", label);
            removeBox(label);
            printBoxes();
            label[0] = '\0';
            labelLength = 0;
        }
        else {
            label[labelLength] = c;
            labelLength ++;
            label[labelLength] = '\0';
        }
    }

    long sum = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < boxes[i].length; j++) {
            long value = (i+1) * (j+1) * boxes[i].lenses[j].focal;
            sum += value;
        }
    }

    printf("%ld\n", sum);

    fclose(f);
}
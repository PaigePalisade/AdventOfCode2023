#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_NAME "input.txt"

// first day I had to lookup help online, the hint I received was that the answer was guaranteed to be the lcm

typedef struct Node Node;
struct Node {
    int left;
    int right;
};

int base26(char* str) {
    int res = 0;
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            res *= 26;
            res += *str - 'A';
        } 
        str ++;
    }
    return res;
}

int printBase26(int x) {
    char str[4] = {0};
    for (int i = 0; i < 3; i++) {
        str[2 - i] = x % 26 + 'A';
        x /= 26;
    }
    printf("%s\n", str);
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // array of nodes, index is the name converted from base 26

    // 17575 is 26^3 - 1
    Node* arr = (Node*)calloc(17575, sizeof(Node));

    char instructions[512];

    fscanf(f, "%s ", &instructions);

    // indexes of all nodes ending with 'A'
    int indexes[512];
    int ACount = 0;


    while (!feof(f)) {
        char name[10];
        char left[10];
        char right[10];
        fscanf(f, "%s = %s %s ", name, left, right);

        if (name[2] == 'A') {
            indexes[ACount] = base26(name);
            ACount ++;
        }

        arr[base26(name)] = (Node){base26(left), base26(right)};
    }

    int numInstr = strlen(instructions);

    int done = 0;

    int ZCounts[512] = {0};

    for (int i = 0; i < ACount; i++) {
        while (indexes[i] % 26 != 25) {
            if (instructions[ZCounts[i] % numInstr] == 'R') {
                indexes[i] = arr[indexes[i]].right;
            }
            if (instructions[ZCounts[i] % numInstr] == 'L') {
                indexes[i] = arr[indexes[i]].left;
            }
            ZCounts[i] ++;
        }
    }
    
    free(arr);

    printf("Answer is the Least Common Multiple of: ");

    for (int i = 0; i < ACount; i++) {
        printf("%d, ", ZCounts[i]);
    }

    printf("\n");

    fclose(f);
}
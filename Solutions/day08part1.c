#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define FILE_NAME "input.txt"

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

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // array of nodes, index is the name converted from base 26

    // 17575 is 26^3 - 1
    Node* arr = (Node*)calloc(17575, sizeof(Node));

    char instructions[512];

    fscanf(f, "%s ", &instructions);

    while (!feof(f)) {
        char name[10];
        char left[10];
        char right[10];
        fscanf(f, "%s = %s %s ", name, left, right);

        arr[base26(name)] = (Node){base26(left), base26(right)};
    }

    int numInstr = strlen(instructions);

    int index = base26("AAA");

    int count = 0;

    while (index != 17575) {
        if (instructions[count % numInstr] == 'R') {
            index = arr[index].right;
        }
        if (instructions[count % numInstr] == 'L') {
            index = arr[index].left;
        }
        count ++;
    }
    
    free(arr);

    printf("%d\n", count);

    fclose(f);
}
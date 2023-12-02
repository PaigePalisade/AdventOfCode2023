#include <stdio.h>
#include <string.h>

int main() {
    char line[512];

    FILE* f = fopen("input.txt", "r");

    int sum = 0;

    while (!feof(f)) {
        int num = 0;
        fscanf(f, "%s ", line);

        int len = strlen(line);

        for (int i = 0; i < len; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                num += (line[i] - '0') * 10;
                break;
            }
        }
        for (int i = len-1; i >= 0; i--) {
            if (line[i] >= '0' && line[i] <= '9') {
                num += line[i] - '0';
                break;
            }
        }
        sum += num;
    }
    printf("%d\n", sum);
}
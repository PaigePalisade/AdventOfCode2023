#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int max_red = 12;
const int max_green = 13;
const int max_blue = 14;

int main() {
    FILE* f = fopen("input.txt", "r");

    char color[512];
    int number;

    int game;

    int sum = 0;

    while (!feof(f)) {
        fscanf(f, "Game %d: ", &game);

        int possible = 1;

        while (1) {
            fscanf(f, "%d %s ", &number, color);
            int len = strlen(color);
            if (len >= 3 && strncmp("red", color, 3) == 0 && number > max_red) {
                possible = 0;
            }
            if (len >= 5 && strncmp("green", color, 5) == 0 && number > max_green) {
                possible = 0;
            }
            if (len >= 4 && strncmp("blue", color, 4) == 0 && number > max_blue) {
                possible = 0;
            }
            char last_char = color[len-1];
            if (last_char != ',' && last_char != ';') {
                break;
            }
        }
        if (possible) {
            sum += game;
        }
    }
    printf("%d\n", sum);

    fclose(f);
}
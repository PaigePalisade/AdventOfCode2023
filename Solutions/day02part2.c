#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    FILE* f = fopen("input.txt", "r");

    char color[512];
    int number;

    int game;

    int sum = 0;

    while (!feof(f)) {
        fscanf(f, "Game %d: ", &game);
        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;
        while (1) {
            fscanf(f, "%d %s ", &number, color);
            int len = strlen(color);
            if (len >= 3 && strncmp("red", color, 3) == 0) {
                if (number > min_red) {
                    min_red = number;
                }
            }
            if (len >= 5 && strncmp("green", color, 5) == 0) {
                if (number > min_green) {
                    min_green = number;
                }
            }
            if (len >= 4 && strncmp("blue", color, 4) == 0) {
                if (number > min_blue) {
                    min_blue = number;
                }
            }
            char last_char = color[len-1];
            if (last_char != ',' && last_char != ';') {
                break;
            }
        }
        sum += min_red * min_green * min_blue;
    }
    printf("%d\n", sum);

    fclose(f);
}
#include <stdio.h>
#include <string.h>

const char* words[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int checkWord(char* substring, int len) {
    for (int i = 0; i < 9; i++) {
        int wordlen = strlen(words[i]);
        if (len >= wordlen && strncmp(substring, words[i], wordlen) == 0) {
            return i + 1;
        }
    }
    return -1;
}

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
            else {
                int word = checkWord(line + i, len - i);
                if (word != -1) {
                    num += word * 10;
                    break;
                }
            }
        }
        for (int i = len-1; i >= 0; i--) {
            if (line[i] >= '0' && line[i] <= '9') {
                num += line[i] - '0';
                break;
            }
            else {
                int word = checkWord(line + i, len - i);
                if (word != -1) {
                    num += word;
                    break;
                }
            }
        }
        sum += num;
    }
    printf("%d\n", sum);

    fclose(f);
}
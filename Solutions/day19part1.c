#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// using hash tables again
#include <search.h>

#define FILE_NAME "input.txt"
#define NUM_WORKFLOWS 523

typedef struct {
    char component;
    char operator;
    int value;
    char label[5];
} Rule;

typedef struct {
    int numRules;
    Rule rules[10];
} Workflow;

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    hcreate(NUM_WORKFLOWS * 2);

    Workflow workflows[NUM_WORKFLOWS] = {0};
    char labelArr[NUM_WORKFLOWS][5] = {0};

    char* token;

    for (int i = 0; i < NUM_WORKFLOWS; i++) {
        fscanf(f, "%[^{]s", labelArr[i]);
        fgetc(f);

        char delim = ',';
        while (delim != '}') {
            Rule rule = {0};
            char ruleStr[512];
            fscanf(f, "%[^,^}]s", &ruleStr);
            delim = fgetc(f);
            char* labelStart = strrchr(ruleStr, ':');

            if (labelStart != NULL) {
                rule.component = ruleStr[0];
                rule.operator = ruleStr[1];
                rule.value = atoi(ruleStr + 2);
                strcpy(rule.label, labelStart + 1);
            }
            else {
                strcpy(rule.label, ruleStr);
            }

            workflows[i].rules[workflows[i].numRules] = rule;
            workflows[i].numRules ++;
        }
        fscanf(f, " ");
        hsearch((ENTRY){labelArr[i], &workflows[i]}, ENTER);
    }

    int score = 0;

    while (!feof(f)) {
        int p[256] = {0};

        fscanf(f, "{x=%d,m=%d,a=%d,s=%d} ", &p['x'], &p['m'], &p['a'], &p['s']);

        Workflow* workflow = (Workflow*)hsearch((ENTRY){"in", NULL}, FIND)->data;
        printf("in ");

        while (workflow != NULL) {
            for (int i = 0; i < workflow->numRules; i++) {
                Rule rule = workflow->rules[i];
                int valid = 0;
                if (rule.operator == 0) {
                    valid = 1;
                }
                else if (rule.operator == '<' && p[rule.component] < rule.value) {
                    valid = 1;
                }
                else if (rule.operator == '>' && p[rule.component] > rule.value) {
                    valid = 1;
                }
                if (valid) {
                    if (strcmp(rule.label, "A") == 0) {
                        score += p['x'] + p['m'] + p['a'] + p['s'];
                    }
                    printf("-> %s", rule.label);
                    ENTRY* e = hsearch((ENTRY){rule.label, NULL}, FIND);
                    if (e == NULL) {
                        workflow = NULL;
                    }
                    else {
                        workflow = (Workflow*)e->data;
                    }
                    break;
                }
            }
        }
        printf("\n");
    }

    printf("%d\n", score);

    hdestroy();

    fclose(f);
}
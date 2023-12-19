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
    int component;
    char operator;
    int value;
    char label[5];
} Rule;

typedef struct {
    int numRules;
    Rule rules[10];
} Workflow;

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    Range ranges[4];
} PartRange;

long countPossibilities(PartRange p, char* label) {
    if (strcmp(label, "A") == 0) {
        Range* r = p.ranges;
        return (long)(r[0].end-r[0].start+1) * (r[1].end-r[1].start+1) * (r[2].end-r[2].start+1) * (r[3].end-r[3].start+1);
    }
    if (strcmp(label, "R") == 0) {
        return 0;
    }

    Workflow* workflow = (Workflow*)hsearch((ENTRY){label, NULL}, FIND)->data;

    long sum = 0;

    for (int i = 0; i < workflow->numRules; i++) {
        Rule rule = workflow->rules[i];
        if (rule.operator == 0) {
            sum += countPossibilities(p, rule.label);
        }
        else if (rule.operator == '<' && rule.value > p.ranges[rule.component].start) {
            if (rule.value <= p.ranges[rule.component].end) {
                // create a new range full of values less than rule.value
                PartRange newRange = {0};
                memcpy(newRange.ranges, p.ranges, sizeof(newRange.ranges));
                newRange.ranges[rule.component].end = rule.value - 1;
                
                // set p's range to be all the values greater than or equal to rule.value
                p.ranges[rule.component].start = rule.value;

                // count the possibilities at the new label with the new range
                sum += countPossibilities(newRange, rule.label);
            }
            // entire range follows the rule, count possibilities at new label
            else {
                return sum + countPossibilities(p, rule.label);
            }
            
        }
        else if (rule.operator == '>' && rule.value < p.ranges[rule.component].end) {
            if (rule.value >= p.ranges[rule.component].start) {
                // create a new range full of values greater than rule.value
                PartRange newRange = {0};
                memcpy(newRange.ranges, p.ranges, sizeof(newRange.ranges));
                newRange.ranges[rule.component].start = rule.value + 1;
                
                // set p's range to be all the values less than or equal to rule.value
                p.ranges[rule.component].end = rule.value;

                // count the possibilities at the new label with the new range
                sum += countPossibilities(newRange, rule.label);
            }
            // entire range follows the rule, count possibilities at new label
            else {
                return sum + countPossibilities(p, rule.label);
            }
        }
    }
    return sum;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    hcreate(NUM_WORKFLOWS * 2);

    Workflow workflows[NUM_WORKFLOWS] = {0};
    char labelArr[NUM_WORKFLOWS][5] = {0};

    char* token;

    int letterLookup[256];
    letterLookup['x'] = 0;
    letterLookup['m'] = 1;
    letterLookup['a'] = 2;
    letterLookup['s'] = 3;

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
                rule.component = letterLookup[ruleStr[0]];
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

    PartRange p;
    for (int i = 0; i < 4; i++) {
        p.ranges[i] = (Range){1,4000};
    }

    long sum = countPossibilities(p, "in");

    printf("%ld\n", sum);

    hdestroy();

    fclose(f);
}
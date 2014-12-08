#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char * str_src;
bool result;

#define MAXLEN 65535

bool unique_char(char * str) {
    if (NULL == str || 0 == strlen(str)) {
        return false;
    }
    
    short * count = (short *) calloc(1 << sizeof(char) * 8, sizeof(short));
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char ch = str[i];
        if (count[ch] > 0) {
            free(count);
            return false;
        }
        else {
            count[ch] += 1;
        }
    }
    
    free(count);
    return true;
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        str_src = (char *) malloc(MAXLEN * sizeof(char));
        if (NULL != fgets(str_src, MAXLEN, fp)) {
            int len = strlen(str_src);
            if (len >= 2) {
                char * tmpe = (str_src + (len - 1) * sizeof(char));
                while (('\"' != *(tmpe)) && (tmpe > str_src)) {
                    tmpe--;
                }
                *(tmpe) = '\0';

                char * tmps = str_src;
                while (('\"' != *(tmps)) && (tmps < tmpe)) {
                    tmps++;
                }
                if ('\"' == *(tmps)) {
                    str_src = tmps + 1;
                }

                fclose(fp);
                return 0;
            }
        }
    }
    return 2;
}

int data_output(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "w"))) {
        printf("failed to write '%s'.\n", filename);
        return 1;
    }
    else {
        fprintf(fp, "%s", result ? "true" : "false");
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        result = unique_char(str_src);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

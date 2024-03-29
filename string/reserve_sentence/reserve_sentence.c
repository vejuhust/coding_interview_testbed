#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * str_src;
char * str_dest;

#define MAXLEN 65535

char * reserve_string(char * str, int len) {
    int mid = len >> 1;
    char tmp;
    for (int i = 0; i < mid; i++) {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
    return str;
}

char * reserve_sentence(char * str) {
    if (NULL == str || 0 == strlen(str)) {
        return str;
    }
    int len = strlen(str);
    reserve_string(str, len);

    int flag = 0, pos = 0;
    for (int p = 0; p < len; p++) {
        if (' ' == str[p]) {
            if (1 == flag) {
                reserve_string(str + pos, p - pos);
                flag = 0;
            }
        }
        else if (0 == flag) {
            pos = p;
            flag = 1;
        }
    }
    if (1 == flag) {
        reserve_string(str + pos, len - pos);
    }

    return str;
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
                char * tmpe = (str_src + len - 1);
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
        //fprintf(fp, "%d\n", strlen(str_dest));
        fprintf(fp, "\"%s\"", str_dest);
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        str_dest = reserve_sentence(str_src);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

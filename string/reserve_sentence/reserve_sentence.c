#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * str_src;
char * str_dest;

#define MAXLEN 65535

char * reserve_sentence(char * ss) {
    return ss;
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

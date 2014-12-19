#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 16384
#define swap(x,y) { long tmp; tmp = (x); (x) = (y); (y) = tmp; }

long data [MAXLEN];
int  length = 0;

void shell_sort(long * data, int len_data) {
    int h = 1;
    while (h < len_data / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        for (int i = h; i < len_data; i++) {
            for (int j = i; j >= h && data[j - h] > data[j]; j -= h)  {
                swap(data[j], data[j - h]);
            }
        }
        h /= 3;
    }
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        fscanf(fp, "%d", &length);
        for (int i = 0; i < length; i++) {
            fscanf(fp, "%ld", &data[i]);
        }
        fclose(fp);
        return 0;
    }
}

int data_output(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "w"))) {
        printf("failed to write '%s'.\n", filename);
        return 1;
    }
    else {
        if (0 >= length) {
            fprintf(fp, " ");
        }
        else {
            for (int i = 0; i < length; i++) {
                fprintf(fp, "%ld ", data[i]);
            }
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        shell_sort(data, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

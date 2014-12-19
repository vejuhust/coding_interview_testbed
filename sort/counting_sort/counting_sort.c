#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 16384

long data [MAXLEN];
int  length = 0;

void counting_sort(long * data, int len_data) {
    if (len_data <= 1) {
        return;
    }
    
    long low = LONG_MAX;
    long high = LONG_MIN;
    for (int i = 0; i < len_data; i++) {
        low = data[i] < low ? data[i] : low;
        high = data[i] > high ? data[i] : high;
    }
    
    int len_count = high - low + 1;
    int * count = (int *) calloc(len_count, sizeof(int));
    for (int i = 0; i < len_data; i++) {
        count[data[i] - low]++;
    }
    for (int i = 1; i < len_count; i++) {
        count[i] += count[i - 1];
    }
    
    long * tmp = (long *) calloc(len_data, sizeof(long));
    for (int i = len_data - 1; i >=0; i--) {
        tmp[--count[data[i] - low]] = data[i];
    }
    for (int i = 0; i < len_data; i++) {
        data[i] = tmp[i];
    }
    
    free(count);
    free(tmp);
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
        counting_sort(data, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

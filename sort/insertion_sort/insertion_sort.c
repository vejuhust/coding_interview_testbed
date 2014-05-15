#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


#define MAXLEN 16384

long data [MAXLEN];
int  length = 0;

void insertion_sort(long * data, int len_data) {
    for (int i = 1; i < len_data; i++) {
        for (int j = i; j > 0 && data[j - 1] > data[j]; j--)  {
            long tmp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = tmp;
        }
    }
}

void selection_sort(long * data, int len_data) {
    for (int i = 0; i < len_data; i++) {
        int  min = i;
        for (int j = i + 1; j < len_data; j++)  {
            min = data[j] < data[min] ? j : min;
        }
        
        long tmp = data[i];
        data[i] = data[min];
        data[min] = tmp;
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
        insertion_sort(data, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

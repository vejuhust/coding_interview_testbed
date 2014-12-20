#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 16384

long data [MAXLEN];
int  length = 0;

void merge(long * data, long * aux, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    
    for (int k = low; k <= high; k++) {
        aux[k] = data[k];
    }
    
    for (int k = low; k <= high; k++) {
        if (i > mid) {
            data[k] = aux[j++];
        }
        else if (j > high) {
            data[k] = aux[i++];
        }
        else if (aux[i] > aux[j]) {
            data[k] = aux[j++];
        }
        else {
            data[k] = aux[i++];
        }
    }
}

void sort(long * data, long * aux, int low, int high) {
    if (low >= high) {
        return;
    }
    
    int mid = (low + high) / 2;
    sort(data, aux, low, mid);
    sort(data, aux, mid + 1, high);

    if (data[mid] > data[mid + 1]) {
        merge(data, aux, low, mid, high);
    }
}

void merge_sort(long * data, int length) {
    long * aux = (long *) calloc(length, sizeof(long));
    sort(data, aux, 0, length - 1);
    free(aux);
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
        merge_sort(data, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

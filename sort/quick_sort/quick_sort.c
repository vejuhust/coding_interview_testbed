#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 16384
#define swap(x,y) { long tmp; tmp = (x); (x) = (y); (y) = tmp; }

long data [MAXLEN];
int  length = 0;

void quicksort(long * data, int low, int high) {
    long x = data[(low + high) >> 1];
    int i = low;
    int j = high;

    do {
        while (data[i] < x) {
            i++;
        }
        while (x < data[j]) {
            j--;
        }

        if (i <= j) {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (low < j) {
        quicksort(data, low, j);
    }
    if (i < high) {
        quicksort(data, i, high);
    }
}

void quick_sort(long * data, int len_data) {
    quicksort(data, 0, len_data - 1);
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
        quick_sort(data, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

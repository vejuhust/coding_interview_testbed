#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 16384
#define swap(a, x, y) { long tmp; tmp = (a)[(x)]; (a)[(x)] = (a)[(y)]; (a)[(y)] = tmp; }

long data [MAXLEN];
int  length = 0;

void swim(long * data, int k) {
    while (k > 1 && data[k / 2] < data[k]) {
        swap(data, k / 2, k);
        k /= 2;
    }
}

void sink(long * data, int length, int k) {
    while (2 * k <= length) {
        int j = 2 * k;
        if (j < length && data[j] < data[j + 1]) {
            j++;
        }
        if (data[k] >= data[j]) {
            break;
        }
        else {
            swap(data, k, j);
            k = j;
        }
    }
}

void heap_sort(long * data, int length) {
    int n = length;
    for (int k = n / 2; k >= 1; k--) {
        sink(data, n, k);
    }
    while (n > 1) {
        swap(data, n, 1);
        sink(data, --n, 1);
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
        for (int i = 1; i <= length; i++) {
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
            for (int i = 1; i <= length; i++) {
                fprintf(fp, "%ld ", data[i]);
            }
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        heap_sort(data, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define MAXLEN 16384
#define swap(x,y) { long tmp; tmp = (x); (x) = (y); (y) = tmp; }

long data [MAXLEN];
int  length = 0;

int randint(int low, int high) {
   static bool flag = true;
   if (flag) {
       srand(time(NULL));
       flag = false;
   }
   return rand() % (high - low + 1) + low;
}

void shuffle(long * data, int length) {
    for (int i = 0; i < length; i++) {
        int j = randint(i, length - 1);
        swap(data[i], data[j]);
    }
}

void quick_sort(long * data, int low, int high) {
    long x = data[(low + high) / 2];
    int i = low, j = high;

    do {
        for (; data[i] < x; i++);
        for (; x < data[j]; j--);

        if (i <= j) {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (low < j) {
        quick_sort(data, low, j);
    }
    if (i < high) {
        quick_sort(data, i, high);
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
        shuffle(data, length);
        quick_sort(data, 0, length - 1);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

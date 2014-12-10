#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

int matrix [MAXLEN][MAXLEN];
int len_mat;

void rotate_matrix(int a[MAXLEN][MAXLEN], int len) {
    if (len <= 1) {
        return;
    }
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        if (0 != fscanf(fp, "%d", &len_mat)) {
            for (int i = 0; i < len_mat; i++) {
                for (int j = 0; j < len_mat; j++) {
                    fscanf(fp, "%d", &(matrix[i][j]));
                }
            }
            fclose(fp);
            return 0;
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
        if (0 == len_mat) {
            fprintf(fp, " ");
        }
        else {
            for (int i = 0; i < len_mat; i++) {
                for (int j = 0; j < len_mat; j++) {
                    fprintf(fp, "%d ", matrix[i][j]);
                }
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        rotate_matrix(matrix, len_mat);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

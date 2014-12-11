#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

int matrix [MAXLEN][MAXLEN];
int len_row;
int len_col;

void set_row_col(int a[MAXLEN][MAXLEN], int len_row, int len_col) {
    if (len_row < 1 || len_col < 1) {
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
        if (0 != fscanf(fp, "%d%d", &len_row, &len_col)) {
            for (int i = 0; i < len_row; i++) {
                for (int j = 0; j < len_col; j++) {
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
        if (len_row < 1 || len_col < 1) {
            fprintf(fp, " ");
        }
        else {
            for (int i = 0; i < len_row; i++) {
                for (int j = 0; j < len_col; j++) {
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
        set_row_col(matrix, len_row, len_col);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

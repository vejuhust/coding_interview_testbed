#include <stdio.h>

long long num_a;
long long num_b;
long long result;

long long plus(long long a, long long b) {
    return a + b;
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        fscanf(fp, "%lld%lld", &num_a, &num_b);
        fclose(fp);
    }
    return 0;
}

int data_output(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "w"))) {
        printf("failed to write '%s'.\n", filename);
        return 1;
    }
    else {
        fprintf(fp, "%lld", result);
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        result = plus(num_a, num_b);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

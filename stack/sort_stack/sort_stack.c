#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 1024

typedef struct _stack {
    int  top;
    long data [MAXLEN];
} stack;

stack src = { .top = -1 };
stack tmp = { .top = -1 };

bool stack_isempty(stack * src) {
    return src->top < 0;
}

void stack_push(stack * src, long value) {
    src->top = stack_isempty(src) ? 0 : src->top + 1;
    src->data[src->top] = value;
}

long stack_pop(stack * src) {
    return stack_isempty(src) ? LONG_MIN : src->data[src->top--];
}

long stack_peek(stack * src) {
    return stack_isempty(src) ? LONG_MIN : src->data[src->top];
}

void sort_stack(stack * src, stack * tmp) {
    while (true) {
        long max = LONG_MIN;
        int count = 0;
        while (!stack_isempty(src)) {
            long value = stack_pop(src);
            stack_push(tmp, value);
            
            if (value > max) {
                max = value;
            }
            count++;
        }
        
        if (0 == count) {
            break;
        }
        
        bool flag = true;
        for (int i = 0; i < count; i++) {
            long value = stack_pop(tmp);
            if (flag && value == max) {
                flag = false;
            }
            else {
                stack_push(src, value);
            }
        }
        stack_push(tmp, max);
    }
    
    while (!stack_isempty(tmp)) {
        stack_push(src, stack_pop(tmp));
    }
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        int len;
        fscanf(fp, "%d", &len);
        for (int i = 0; i < len; i++) {
            long value;
            fscanf(fp, "%ld", &value);
            stack_push(&src, value);
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
        if (stack_isempty(&src)) {
            fprintf(fp, " ");
        }
        else {
            while (!stack_isempty(&src)) {
                fprintf(fp, "%ld ", stack_pop(&src));
            }
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        sort_stack(&src, &tmp);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

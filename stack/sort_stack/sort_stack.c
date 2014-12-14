#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


#define LINKED 1

#ifdef LINKED

typedef struct _node {
    long value;
    struct _node * next;
} node;

typedef struct _stack {
    node * data;
} stack;

stack src = { .data = NULL };
stack tmp = { .data = NULL };

bool stack_isempty(stack * src) {
    return NULL == src->data;
}

void stack_push(stack * src, long value) {
    node * tmp = (node *) calloc(1, sizeof(node));
    tmp->next = NULL;
    tmp->value = value;
    
    if (stack_isempty(src)) {
        src->data = tmp;    
    }
    else {
        tmp->next = src->data;
        src->data = tmp;
    }
}

long stack_pop(stack * src) {
    long value;
    if (stack_isempty(src)) {
        value = LONG_MIN; 
    }
    else {
        node * tmp = src->data;
        src->data = src->data->next;
        value = tmp->value;
        free(tmp);
    }
    
    return value;
}

long stack_peek(stack * src) {
    return stack_isempty(src) ? LONG_MIN : src->data->value;
}

#else

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

#endif

void sort_stack(stack * src, stack * tmp) {
    while (!stack_isempty(src)) {
        long value = stack_pop(src);
        while (!stack_isempty(tmp) && stack_peek(tmp) < value) {
            stack_push(src, stack_pop(tmp));
        }
        stack_push(tmp, value);
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

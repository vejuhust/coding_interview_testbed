#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _node {
    long value;
    struct _node * next;
} node;

node * head = NULL;
node * result = NULL;
int k = 0;

node * last_kth(node * head, int k) {
    if (NULL == head || k < 1) {
        return NULL;
    }
    
    node * p1 = head;
    node * p2 = head;
    
    for (int i = 1; i < k; i++) {
        p2 = p2->next;
        if (NULL == p2) {
            return NULL;
        }
    }
    
    while (NULL != p2->next) {
        p2 = p2->next;
        p1 = p1->next;
    }
    
    return p1;
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        int len = 0;
        if (0 != fscanf(fp, "%d%d", &len, &k)) {
            node * current = NULL;
            for (int i = 0; i < len; i++) {
                node * tmp = (node *) calloc(1, sizeof(node));
                fscanf(fp, "%ld", &(tmp->value));
                tmp->next = NULL;
                if (NULL == head) {
                    head = tmp;
                    current = tmp;
                }
                else {
                    current->next = tmp;
                    current = tmp;
                }
            }
            fclose(fp);
            return 0;
        }
        else {
            fclose(fp);
            return 2;
        }
    }
}

int data_output(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "w"))) {
        printf("failed to write '%s'.\n", filename);
        return 1;
    }
    else {
        if (NULL == result) {
            fprintf(fp, " ");
        }
        else {
            fprintf(fp, "%ld", result->value);
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        result = last_kth(head, k);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

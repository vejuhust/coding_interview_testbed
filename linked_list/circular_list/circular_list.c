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

node * find_joint(node * head) {
    node ** flag = (node **) calloc(1024, sizeof(node *));
    node * ptr = head;
    int count = 0;
    while (NULL != ptr) {
        for (int i = 0; i < count; i++) {
            if (flag[i] == ptr) {
                free(flag);
                return ptr;
            }
        }
        flag[count++] = ptr;
        ptr = ptr->next;
    }
    
    return ptr;
}

int data_input(char * filename) {
    FILE * fp;
    if (NULL == (fp = fopen(filename, "r"))) {
        printf("failed to read '%s'.\n", filename);
        return 1;
    }
    else {
        int len = 0;
        int target = 0;
        if (0 != fscanf(fp, "%d%d", &len, &target)) {
            node * current = NULL;
            node * joint = NULL;
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
                if (target == current->value) {
                    joint = current;
                }
            }
            if (joint && current) {
                current->next = joint;
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
        result = find_joint(head);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

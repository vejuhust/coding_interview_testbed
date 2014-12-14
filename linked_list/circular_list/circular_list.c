#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SOLUTION find_joint1

typedef struct _node {
    long value;
    struct _node * next;
} node;

node * head = NULL;
node * result = NULL;

node * find_joint2(node * head) {
    node * p1 = head;
    node * p2 = head;
    
    while (NULL != p2 && NULL != p2->next) {
        p1 = p1->next;
        p2 = p2->next->next;
        if (p1 == p2) {
            break;
        }
    }
    
    if (NULL == p2 || NULL == p2->next) {
        return NULL;
    }
    
    p1 = head;
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return p1;
}

#define HASH_PRIME 1543

typedef struct _hash {
    node * value;
    struct _hash * next;
} hash;

void hash_insert(hash ** table, node * target) {
    int addr = (int)target % HASH_PRIME;
    hash * node = (hash *) calloc(1, sizeof(hash));
    node->value = target;
    node->next = NULL;
    if (NULL == table[addr]) {
        table[addr] = node;
    }
    else {
        hash * tmp = table[addr];
        while (NULL != tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
}

bool hash_exist(hash ** table, node * target) {
    int addr = (int)target % HASH_PRIME;
    if (NULL != table[addr]) {
        hash * tmp = table[addr];
        while (NULL != tmp) {
            if (tmp->value == target) {
                return true;
            }
            tmp = tmp->next;
        }
    }
    return false;
}

node * find_joint1(node * head) {
    hash ** table = (hash **) calloc(HASH_PRIME, sizeof(hash *));
    node * ptr = head;
    while (NULL != ptr) {
        if (hash_exist(table, ptr)) {
            free(table);
            return ptr;
        }
        hash_insert(table, ptr);
        ptr = ptr->next;
    }
    
    free(table);
    return ptr;
}

node * find_joint0(node * head) {
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
        result = SOLUTION(head);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

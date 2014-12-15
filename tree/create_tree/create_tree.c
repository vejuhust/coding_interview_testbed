#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 1024

typedef struct _tree {
    long            value;
    struct _tree  * left;
    struct _tree  * right;
} tree;

tree * root = NULL;
int length = 0;

long preorder   [MAXLEN];
long inorder    [MAXLEN];

void traversal_preorder(tree * root) {
    if (NULL == root) {
        return;
    }
    printf("%ld ", root->value);
    traversal_preorder(root->left);
    traversal_preorder(root->right);
}

void traversal_inorder(tree * root) {
    if (NULL == root) {
        return;
    }
    traversal_inorder(root->left);
    printf("%ld ", root->value);
    traversal_inorder(root->right);
}

void traversal_postorder(tree * root) {
    if (NULL == root) {
        return;
    }
    traversal_postorder(root->left);
    traversal_postorder(root->right);
    printf("%ld ", root->value);
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
            fscanf(fp, "%ld", &(preorder[i]));
        }
        for (int i = 0; i < length; i++) {
            fscanf(fp, "%ld", &(inorder[i]));
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
        if (NULL == root) {
            fprintf(fp, " ");
        }
        else {
            fprintf(fp, "%ld", root->value);
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

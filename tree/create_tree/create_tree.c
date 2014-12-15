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

tree * create_tree(long * preorder, long * inorder, int length) {
    if (NULL == preorder || NULL == inorder || 0 >= length) {
        return NULL;
    }
    
    int pos = -1;
    for (int i = 0; i < length; i++) {
        if (preorder[0] == inorder[i]) {
            pos = i;
            break;
        }
    }
    if (0 > pos) {
        return NULL;
    }
    
    int len_left = pos;
    int len_right = length - pos - 1;
    tree * root = (tree *) calloc(1, sizeof(tree));
    root->value = preorder[0];
    root->left = create_tree(preorder + 1, inorder, len_left);
    root->right = create_tree(preorder + 1 + len_left, inorder + len_left + 1, len_right);
    
    return root;
}

void traversal_preorder(FILE * fp, tree * root) {
    if (NULL == root) {
        return;
    }
    fprintf(fp, "%ld ", root->value);
    traversal_preorder(fp, root->left);
    traversal_preorder(fp, root->right);
}

void traversal_inorder(FILE * fp, tree * root) {
    if (NULL == root) {
        return;
    }
    traversal_inorder(fp, root->left);
    fprintf(fp, "%ld ", root->value);
    traversal_inorder(fp, root->right);
}

void traversal_postorder(FILE * fp, tree * root) {
    if (NULL == root) {
        return;
    }
    traversal_postorder(fp, root->left);
    traversal_postorder(fp, root->right);
    fprintf(fp, "%ld ", root->value);
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
            traversal_postorder(fp, root);
        }
        fclose(fp);
    }
    return 0;
}

int main() {
    if (0 == data_input("input.txt")) {
        root = create_tree(preorder, inorder, length);
        if (0 == data_output("output.txt")) {
            return 0;
        }
    }
    return 1;
}

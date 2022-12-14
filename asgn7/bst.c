#include "node.h"
#include "bst.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
uint64_t branches;
Node *bst_create(void) {
    return NULL;
}
static int max(int x, int y) {
    return x > y ? x : y; //helper function for height and size
}
uint32_t bst_height(Node *root) {
    if (root) { //recursively finds height of bst
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}
uint32_t bst_size(Node *root) { //recursively finds size of bst
    if (root) {
        return 1 + bst_size(root->left) + bst_size(root->right);
    }
    return 0;
}
Node *bst_find(Node *root, char *oldspeak) { //returns the node according to the oldspeak
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches += 1;
            return bst_find(root->left, oldspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            branches += 1;
            return bst_find(root->right, oldspeak);
        }
    }
    return root;
}
Node *bst_insert(
    Node *root, char *oldspeak, char *newspeak) { //adds node based on alphabetical ordering
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches += 1;
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            branches += 1;
            root->right = bst_insert(root->right, oldspeak, newspeak);
        } else if (strcmp(root->oldspeak, oldspeak) == 0) {
            return root;
        }
        return root;
    }

    return node_create(oldspeak, newspeak);
}
void bst_print(Node *root) { //prints out bst in order

    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}
void bst_delete(Node **root) { //recursively postorder deletes nodes
    if (*root) {

        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
}

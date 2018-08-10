/**
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's sum is the max in the tree.
 * Note: the values of the nodes are in (0,255).
 * Author: Liangxiao Xin
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Create a Tree for test.
 */
struct TreeNode* CreateTree(){
    struct TreeNode *node;
    int x;
    printf("Enter data(-1 for no data):");
    scanf("%d", &x);

    if (x==-1)
        return NULL;

    node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = x;

    printf("Enter left child of %d:\n", x);
    node->left=CreateTree();

    printf("Enter right child of %d:\n", x);
    node->right=CreateTree();

    return node;
}

/**
 * Delete the tree
 * Param node: the node needs to be deleted.
 */
void DeleteTree(struct TreeNode* node){
    if (!node) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    printf("Delete node %d\n", node->val);
    free(node);
}

/**
 * Do DFS to search the path with max sum.
 * The numbers of paths *returnSize are returned as an array of arrays of size.
 * The numbers of nodes in all paths *columnSizes are returned as the sizes of the arrays.
 * The root-to-leave paths **res are returned as matrix.
 * The max sum of path maxSum is returned as an integer.
 */
void DFS(struct TreeNode* node, int sum, int* column, int size, int** columnSizes, int* returnSize, int** res, int* maxSum){
    if (!node) return;
    if (sum+node->val>=*maxSum && !node->left && !node->right){
        printf("Find new max sum: %d\n", sum+node->val);
        if (sum+node->val > *maxSum){
            for (int i=0; i<*returnSize; i++){
                free(res[i]);
            }
            *returnSize=0;
            *maxSum = sum+node->val;
        }
        (*columnSizes)[*returnSize] = size+1;
        res[*returnSize] = (int*)malloc((size+1)*sizeof(int));
        for (int i=0; i<size; i++)
            res[*returnSize][i] = column[i];
        res[*returnSize][size] = node->val;

        for (int i=0; i<(*columnSizes)[*returnSize]; i++){
            printf("%d->", res[*returnSize][i]);
        }
        printf("NULL\n");

        (*returnSize)++;
        return;
    }
    int newcolumn[size+1];
    for (int i=0; i<size; i++)
        newcolumn[i] = column[i];
    newcolumn[size] = node->val;
    DFS(node->left, sum+node->val, newcolumn, size+1, columnSizes, returnSize, res, maxSum);
    DFS(node->right, sum+node->val, newcolumn, size+1, columnSizes, returnSize, res, maxSum);
}

/**
 * Given a tree, search the path with max sum
 * Param root : the tree needs to be searched.
 * The numbers of paths *returnSize are returned as an array of arrays of size.
 * The numbers of nodes in all paths *columnSizes are returned as the sizes of the arrays.
 * The root-to-leave paths **res are returned as matrix.
 *
 * Return maxSum: the max sum is returned as an integer.
 */
int** pathSum(struct TreeNode* root, int** columnSizes, int* returnSize, int* maxSum) {
    if (!root) return NULL;
    int** res;
    int sum = 0;
    res = (int**)malloc(10000*sizeof(int*));
    *returnSize = 0;
    *columnSizes = (int*)malloc(10000*sizeof(int));
    DFS(root, sum, NULL, 0, columnSizes, returnSize, res, maxSum);
    *columnSizes = (int*)realloc(*columnSizes, (*returnSize)*sizeof(int));
    printf("path search done!\n");
    return res;
}

/**
 * Test for the search of tree path with max sum.
 * For example:
 * Please enter
 * 1 2 4 -1 -1 5 9 -1 -1 -1 6 10 -1 -1 -1
 * to create a tree.
 * and the result is:
 *
 * Created Tree!
 * Find new max sum: 7
 * 1->2->4->NULL
 * Find new max sum: 17
 * 1->2->5->9->NULL
 * Find new max sum: 17
 * 1->6->10->NULL
 * path search done!
 * max sum: 17, find 2 paths
 * 1->2->5->9->NULL
 * 1->6->10->NULL
 * Delete node 4
 * Delete node 9
 * Delete node 5
 * Delete node 2
 * Delete node 10
 * Delete node 6
 * Delete node 1
 */
int main() {
    struct TreeNode *root;
    int* max_sum = (int*)malloc(sizeof(int));
    int** columnSizes = (int**)malloc(sizeof(int*));
    int* returnSize = (int*)malloc(sizeof(int));

    *max_sum = 0;
    *returnSize = 0;


    root = CreateTree();
    printf("Created Tree!\n");

    int** res = pathSum(root, columnSizes, returnSize, max_sum);

    printf("max sum: %d, find %d paths\n", *max_sum, *returnSize);

    for (int i=0; i<*returnSize; i++){
        for (int j=0; j<((*columnSizes)[i]); j++){
            printf("%d->", res[i][j]);
        }
        printf("NULL\n");
    }

    DeleteTree(root);
    return 0;
}
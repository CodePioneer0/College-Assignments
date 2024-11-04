#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parent;
} treenode;
treenode *createNode(int data, treenode *parent){
    treenode *newNode = (treenode *)malloc(sizeof(treenode));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->parent = parent;
    return newNode;
}
int findIndex(int a[], int n, int key)
{
    for (int i = 0; i < n; i++){
        if (a[i] == key) return i;
    }
}
treenode *getTreeInPre(int preorder[], int sizePre, int preStart, int preEnd, int inorder[], int sizeIn, int inStart, int inEnd){
    if (preStart > preEnd || inStart > inEnd) return NULL;
    treenode *root = createNode(preorder[preStart], root);
    int inRoot = findIndex(inorder, sizeIn, root->data);
    int x = inRoot - inStart;
    root->lchild = getTreeInPre(preorder, sizePre, preStart + 1, preStart + x, inorder, sizeIn, inStart, inRoot - 1);
    root->rchild = getTreeInPre(preorder, sizePre, preStart + x + 1, preEnd, inorder, sizeIn, inRoot + 1, inEnd);
    return root;
}

treenode *getTreeInPost(int inorder[], int inSize, int inStart, int inEnd, int postorder[], int postSize, int postStart, int postEnd){
    if (inStart > inEnd || postStart > postEnd) return NULL;
    treenode *root = createNode(postorder[postEnd], root);
    int inRoot = findIndex(inorder, inSize, root->data);
    int x = inRoot - inStart;
    root->lchild = getTreeInPost(inorder,inSize, inStart,inRoot - 1, postorder, postSize, postStart, postStart + x - 1);
    root->rchild = getTreeInPost(inorder, inSize, inRoot + 1, inEnd, postorder, postSize, postStart + x, postEnd - 1);
    return root;
}
int preorder(treenode *t){
    if (t == NULL)
        return 0;

    printf("%d ", t->data);
    preorder(t->lchild);
    preorder(t->rchild);
    return 1;
}
int inorder(treenode *t){
    if (t == NULL)
        return 0;

    inorder(t->lchild);
    printf("%d ", t->data);
    inorder(t->rchild);
    return 1;
}
int postorder(treenode *t){
    if (t == NULL)
        return 0;

    postorder(t->lchild);
    postorder(t->rchild);
    printf("%d ", t->data);
    return 1;
}
int main(){
    treenode *root = NULL;
    int pre[] = {3, 9, 20, 15, 7};
    int in[] = {9, 3, 15, 20, 7};
    int post[] = {9, 15, 7, 20, 3};
    int n = 5;
    root = getTreeInPost(in, n, 0, 4, post, n, 0, 4);
    // preorder(root);
    // printf("\n");
    postorder(root);
    printf("\n");
}
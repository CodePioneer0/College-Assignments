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

treenode *insertNode(treenode *t, int val){
    if (t == NULL){
        return createNode(val, t);
    }
    treenode *temp = t;
    while (1){
        if (temp->data <= val){
            if (temp->rchild != NULL) temp = temp->rchild;
            else{
                temp->rchild = createNode(val, temp);
                break;
            }
        }
        else{
            if (temp->lchild != NULL) temp = temp->lchild;
            else{
                temp->lchild = createNode(val, temp);
                break;
            }
        }
    }
    return t;
}



int isEmpty(treenode *t){
    if (t == NULL)
        return 1;
    return 0;
}
int getCount(treenode *t){
    if (t == NULL)
    {
        return 0;
    }
    int left = getCount(t->lchild);
    int right = getCount(t->rchild);
    return 1 + left + right;
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




int main()
{
    treenode *root = NULL;
    root = insertNode(root,6);
    root = insertNode(root,5);
    root = insertNode(root,7);
    root = insertNode(root,8);
    root = insertNode(root,4);
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    printf("Nodes : %d",getCount(root));
    printf("\n");
    if(isEmpty(root)) printf("Yes Empty\n");
    else printf("Not Empty\n");
    return 0;
    
}
